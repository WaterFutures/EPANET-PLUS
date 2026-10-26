"""
Basic example demonstrating the EPANET-MSX parser functions.
"""
from sympy import symbols

from epanet_plus import msx_parser

if __name__ == "__main__":

    # Parse a constant definition
    name, value = msx_parser.parse_constants("COEFFICIENT K1 0.5")
    print(f"Constant: {name} = {value}")


    # Parse a term and substitute constants
    name, expression = msx_parser.parse_terms("T1 K1 * 2", {"K1": 0.5})
    print(f"Term: {name} = {expression}")

    # Parse and evaluate a rate equation
    sym_map = {"A": symbols("A")}
    species, rate = msx_parser.parse_equation(
        "RATE A -K1*A",
        {"K1": 2.0},
        {},
        sym_map,
        {},
    )
    result = rate([3.0], 1.0, 1.0, 1.0)
    print(f"Rate equation for {species}: {result}")

    # Parse a complete MSX file
    msx_data = msx_parser.parse_msx("net2-cl2.msx")

    print(f"Species: {msx_data['species']}")
    print(f"Constants: {msx_data['constants']}")
    print(f"Terms: {msx_data['terms']}")
    print(f"Rate equations: {list(msx_data['rates'].keys())}")
    print(f"Equilibrium equations: {list(msx_data['equilibria'].keys())}")
    print(f"Initial conditions: {msx_data['initial_conditions']}")
