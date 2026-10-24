import os
import numpy as np 
from sympy import symbols
import textwrap

from epanet_plus import msx_parser

def test_parse_constants():
    name, value = msx_parser.parse_constants("COEFFICIENT K1 0.5")

    assert name == "K1"
    assert value == 0.5

def test_parse_terms():
    name, expression = msx_parser.parse_terms("T1 K1 * 2", {"K1": 0.5})

    assert name == "T1"
    assert expression == "0.5 * 2"

def test_parse_equation():
    sym_map = {"A": symbols("A")}

    name, rate = msx_parser.parse_equation(
        "RATE A -K1*A",
        {"K1": 2.0},
        {},
        sym_map,
        {}
    )

    result = rate([3.0], 1.0, 1.0, 1.0)

    assert name == "A"
    assert callable(rate)
    assert np.isclose(float(result), -6.0)

def test_parse_msx(tmp_path):
    msx_content = textwrap.dedent("""
        [SPECIES]
        BULK A
        WALL B

        [COEFFICIENTS]
        COEFFICIENT K1 0.5

        [TERMS]
        T1 K1 * 2

        [PIPES]
        RATE A -K1*A

        [QUALITY]
        GLOBAL A 0.2

        [END]
    """).strip()

    msx_file = tmp_path / "test.msx"
    msx_file.write_text(msx_content)
    result = msx_parser.parse_msx(str(msx_file))

    assert result["species"] == ["A", "B"]
    assert result["constants"]["K1"] == 0.5
    assert result["terms"]["T1"] == "0.5 * 2"
    assert "A" in result["rates"]
    assert result["initial_conditions"]["A"] == 0.2
    assert result["species_types"]["A"] == "BULK"
    assert result["species_types"]["B"] == "WALL"