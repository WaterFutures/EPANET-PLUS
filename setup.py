import os
import sys
import shutil
import subprocess
from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext


INCLUDE_DIRS = [
    "epanet-src/include",
    "epanet-src/",
    "epanet-msx-src/include",
    "epanet-msx-src/",
    "python-extension",
    "epanet_plus/include",
    "epanet-src/util",
]

SOURCES = [
    "python-extension/pyepanet.c",
    "python-extension/pyepanet2.c",
    "python-extension/pyepanetmsx.c",
    "python-extension/pyepanet_plus.c",
    "python-extension/ext.c",
    "epanet_plus/epanet_plus.c",
    "epanet-src/epanet2.c",
    "epanet-src/hydcoeffs.c",
    "epanet-src/inpfile.c",
    "epanet-src/quality.c",
    "epanet-src/rules.c",
    "epanet-src/epanet.c",
    "epanet-src/hydraul.c",
    "epanet-src/input1.c",
    "epanet-src/mempool.c",
    "epanet-src/qualreact.c",
    "epanet-src/smatrix.c",
    "epanet-src/genmmd.c",
    "epanet-src/hydsolver.c",
    "epanet-src/input2.c",
    "epanet-src/output.c",
    "epanet-src/qualroute.c",
    "epanet-src/hash.c",
    "epanet-src/hydstatus.c",
    "epanet-src/input3.c",
    "epanet-src/project.c",
    "epanet-src/report.c",
    "epanet-msx-src/hash.c",
    "epanet-src/flowbalance.c",
    "epanet-src/leakage.c",
    "epanet-src/validate.c",
    "epanet-src/util/filemanager.c",
    "epanet-src/util/errormanager.c",
    "epanet-src/util/cstr_helper.c",
    "epanet-msx-src/msxcompiler.c",
    "epanet-msx-src/msxfuncs.c",
    "epanet-msx-src/msxqual.c",
    "epanet-msx-src/msxutils.c",
    "epanet-msx-src/smatrix.c",
    "epanet-msx-src/mathexpr.c",
    "epanet-msx-src/msxdispersion.c",
    "epanet-msx-src/msxinp.c",
    "epanet-msx-src/msxrpt.c",
    "epanet-msx-src/newton.c",
    "epanet-msx-src/mempool.c",
    "epanet-msx-src/msxerr.c",
    "epanet-msx-src/msxout.c",
    "epanet-msx-src/msxtank.c",
    "epanet-msx-src/rk5.c",
    "epanet-msx-src/msxchem.c",
    "epanet-msx-src/msxfile.c",
    "epanet-msx-src/msxproj.c",
    "epanet-msx-src/msxtoolkit.c",
    "epanet-msx-src/ros2.c",
]

def get_libomp_prefix() -> str | None:
    prefix = os.environ.get("LIBOMP_PREFIX")
    if prefix:
        return prefix

    brew = shutil.which("brew")
    if brew:
        try:
            return subprocess.check_output(
                [brew, "--prefix", "libomp"],
                text=True,
            ).strip()
        except subprocess.CalledProcessError:
            pass

    return None


def get_openmp_config() -> dict[str, list[str]]:
    if sys.platform == "darwin":
        prefix = get_libomp_prefix()
        if not prefix:
            raise RuntimeError(
                "OpenMP runtime `libomp` not found on macOS. "
                "Install it with `brew install libomp` and set "
                "`LIBOMP_PREFIX=$(brew --prefix libomp)`."
            )

        return {
            "include_dirs": [f"{prefix}/include"],
            "extra_compile_args": ["-Xpreprocessor", "-fopenmp"],
            "extra_link_args": [
                f"-L{prefix}/lib",
                f"-Wl,-rpath,{prefix}/lib",
                "-lomp",
            ],
        }

    if sys.platform.startswith("linux"):
        return {
            "include_dirs": [],
            "extra_compile_args": ["-fopenmp"],
            "extra_link_args": ["-fopenmp"],
        }

    if sys.platform == "win32":
        return {
            "include_dirs": [],
            "extra_compile_args": ["/openmp"],
            "extra_link_args": [],
        }

    return {
        "include_dirs": [],
        "extra_compile_args": [],
        "extra_link_args": [],
    }


omp = get_openmp_config()


extension = Extension(
    name="epanet",
    include_dirs=INCLUDE_DIRS + omp["include_dirs"],
    sources=SOURCES,
    extra_compile_args=omp["extra_compile_args"],
    extra_link_args=omp["extra_link_args"],
)


class build_ext_with_numpy(build_ext):
    def build_extensions(self):
        import numpy

        numpy_include = numpy.get_include()
        for ext in self.extensions:
            ext.include_dirs.append(numpy_include)

        super().build_extensions()


setup(ext_modules=[extension], cmdclass={"build_ext": build_ext_with_numpy})
