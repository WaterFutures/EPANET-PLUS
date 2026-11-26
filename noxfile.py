import nox


@nox.session(python=["3.10", "3.11", "3.12", "3.13", "3.14", "3.15"])
def test(session):
    session.install(".")
    session.install("-rREQUIREMENTS-DEV.txt")

    session.run("pytest", "tests/")
