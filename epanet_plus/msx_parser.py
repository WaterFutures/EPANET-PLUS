""" 
This module contains a Python parser for EPANET-MSX functions. 
"""
import re
import sympy
from sympy import symbols, lambdify
from sympy.parsing.sympy_parser import parse_expr, standard_transformations, convert_xor
from typing import Any 



MSX_FUNCTIONS = {
    "STEP": lambda x: sympy.Heaviside(x, 0),
    "EXP": sympy.exp,
    # "LN": sympy.log,
    # "LOG": lambda x: sympy.log(x, 10),
    # "SQRT": sympy.sqrt,
    # "ABS": sympy.Abs,
    # "SIN": sympy.sin,
    # "COS": sympy.cos,
    # "TAN": sympy.tan,
}

def parse_equation(equation_str: str, constants: dict[str, float], terms: dict[str, str], 
                   sym_map: dict[str, Any], sym_variables: dict[str, Any]) -> tuple[str, Any]:
    """
    Parses a single equation string and substitutes constants.

    Parameters
    ----------
    equation_str : `str`
    constants : `dict[str, float]`
    terms : `doct[str, str]`
    sym_map : `dict[str, Any]`
    sym_variables : `dict[str, Any]`

    Returns
    -------
    tuple[str, Any]
        A tuple containing the species name and the generated rate equation
        function.

    """
    reynolds = symbols('Re')
    flow_velocity = symbols('U')
    diameter = symbols('D')
    surface_per_vol = symbols('Av')
    # surface_per_vol is substituted with 4/D
    fn_args = [reynolds, flow_velocity, diameter] 


    parts = re.split(r'\s+', equation_str, maxsplit=2)
    # Reynolds number
    assert len(parts) == 3
    species_name = parts[1]
    expr_str = parts[2]
    for _ in range(3): 
        for expr_name, expr_body in terms.items():
            expr_str = re.sub(rf'\b{expr_name}\b', f"({expr_body})", expr_str, flags=re.IGNORECASE)
    # Substitute the numeric constants into the text expression string
    for const_name, const_val in constants.items():
        # Use regex boundaries to avoid partial matching (e.g., K1 vs K10)
        expr_str = re.sub(rf'\b{const_name}\b', str(const_val), expr_str, flags=re.IGNORECASE)
        
    sym = {**sym_map, **sym_variables}
    # Convert text expression to a SymPy symbolic object
    sym_expr = parse_expr(
        expr_str, 
        transformations=standard_transformations + (convert_xor,),
        local_dict={
            **MSX_FUNCTIONS,
            **sym
        }
    )

    # convert surface per volume to 4/D but MSX uses liters for volume, so we multiply by 1000 to convert from m^3 to liters.
    sym_expr = sym_expr.subs(surface_per_vol, 4 / (1000 * diameter)) 
    # Lambdify converts the symbolic expression into a Python function
    # It accepts the species as a vector/list matching the species_list order
    rate_equation = lambdify([sym_map.values(), *sym_variables.values(), *fn_args], sym_expr, modules='numpy')
    #print(lambdastr((tuple(sym_map.values()), *sym_variables.values(), *fn_args), sym_expr))
    
    
    return species_name, rate_equation


def parse_constants(constant_str : str) -> tuple [str, float]:
    """
    Parse a constant definition. 

    Parameters
    ----------
    constant_str : `str`

    Returns 
    -------
    tuple [str, float]
        A tuple containing the constant name and its numerical value.
    """
    parts = re.split(r'\s+', constant_str)[1:]
    assert len(parts) >= 2
    name = parts[0]
    value = float(parts[1])
    return name, value

def parse_terms(term_str : str, constants : dict[str, float]) -> tuple [str, str]:
    """
    Parse a term definition and substitute constants. 

    Parameters
    ----------
    term_str : `str`
    constants : `dict[str, float]`
    
    Returns
    -------
    tuple[str, str]
        A tuple containing the term name and the processed expression
        string with all constants substituted.
    """
    parts = re.split(r'\s+', term_str, maxsplit=1)
    assert len(parts) == 2
    expr_name = parts[0]
    expr_body = parts[1]
    # Substitute constants into the expression body early
    for const_name, const_val in constants.items():
        expr_body = re.sub(rf'\b{const_name}\b', str(const_val), expr_body, flags=re.IGNORECASE)
    return expr_name, expr_body

def parse_msx(msx_file : str, variables : list[str] = []) -> dict[str, Any]:
    """
    Parses raw MSX text blocks and creates executable Python functions.

    Parameters
    ----------
    msx_file : `str`
    variables : `list[str]`, optional

    Returns
    -------
    dict[str, Any]
        Dictionary containing species information, compiled rate and
        equilibrium equations, constants, terms, initial conditions,
        and species types.

    """
    with open(msx_file, "r") as f:
        msx_content = f.read()
    
    species_list = []
    species_types = {}
    const_section = re.search(r'\[SPECIES\]\n(.*?)(?=\n\[)', msx_content, re.DOTALL | re.IGNORECASE)
    if const_section:
        for line in const_section.group(1).split('\n'):
            line = line.split(';')[0].strip() # Strip comments
            if line:
                species_type, species_name = re.split(r'\s+', line)[:2]
                species_list.append(species_name)
                species_types[species_name] = species_type
    
    # We keep the order of species as BULK first, then WALL, to simplify simulator code.
    species_list = (
        [ s for s in species_types if species_types[s] == 'BULK' ] 
        + 
        [ s for s in species_types if species_types[s] == 'WALL' ]
    ) 

    # 1. Parse constants into a dictionary
    constants = {}
    const_section = re.search(r'\[COEFFICIENTS\]\n(.*?)(?=\n\[)', msx_content, re.DOTALL | re.IGNORECASE)
    if const_section:
        for line in const_section.group(1).split('\n'):
            line = line.split(';')[0].strip() # Strip comments
            if line:
                name, value = parse_constants(line)
                if name in variables:
                    continue  # Skip if the constant is overridden by variables
                constants[name] = value

    terms = {}
    expr_section = re.search(r'\[TERMS\]\n(.*?)(?=\n\[)', msx_content, re.DOTALL | re.IGNORECASE)
    if expr_section:
        for line in expr_section.group(1).split('\n'):
            line = line.split(';')[0].strip()
            if line:
                term_name, term_eq = parse_terms(line, constants)
                terms[term_name] = term_eq

    # 2. Setup standard MSX variables as SymPy Symbols
    # Add any species or parameters your file tracks
    # species_list = ['NH2CL', 'NH3', 'NH4', 'H', 'TOC', 'HOCL', 'OCL', 'NHCL2', 'I']
    sym_map = {name: symbols(name) for name in species_list}
    sym_variables = {name: symbols(name) for name in variables}
    
    # 3. Parse and compile the rates
    compiled_rates = {}
    compiled_equil = {}
    rate_section = re.search(r'\[PIPES?\]\n(.*?)(?=\n\[|\[END\]|$)', msx_content, re.DOTALL | re.IGNORECASE)
    if rate_section:
        for line in rate_section.group(1).split('\n'):
            line = line.split(';')[0].strip()
            if line.upper().startswith('RATE'):
                # Split line into: "RATE", "SPECIES_NAME", "MATHEMATICAL_EXPRESSION"
                species_name, fn = parse_equation(line, constants, terms, sym_map, sym_variables)
                compiled_rates[species_name] = fn
            if line.upper().startswith('EQUIL'):
                # Split line into: "RATE", "SPECIES_NAME", "MATHEMATICAL_EXPRESSION"
                species_name, fn = parse_equation(line, constants, terms, sym_map, sym_variables)
                compiled_equil[species_name] = fn
    
    initial_conditions = {}
    init_section = re.search(r'\[QUALITY\]\n(.*?)(?=\n\[|\[END\]|$)', msx_content, re.DOTALL | re.IGNORECASE)
    if init_section:
        for line in init_section.group(1).split('\n'):
            line = line.split(';')[0].strip()
            if line.startswith('NODE'):
                parts = re.split(r'\s+', line)[1:]
                species_name = parts[1]
                initial_value = float(parts[2])
                initial_conditions[species_name] = initial_value
            elif line.startswith('GLOBAL'):
                parts = re.split(r'\s+', line)[1:]
                species_name = parts[0]
                initial_value = float(parts[1])
                initial_conditions[species_name] = initial_value
    

    return {
        'species' : species_list,
        'rates' : compiled_rates, 
        'equilibria' : compiled_equil, 
        'constants' : constants, 
        'terms' : terms, 
        'initial_conditions' : initial_conditions,
        'species_types' : species_types
    }