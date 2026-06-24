from setuptools import setup
from setuptools.command.build_ext import build_ext


class build_ext_with_numpy(build_ext):
    def build_extensions(self):
        import numpy

        numpy_include = numpy.get_include()
        for ext in self.extensions:
            ext.include_dirs.append(numpy_include)

        super().build_extensions()


setup(cmdclass={"build_ext": build_ext_with_numpy})
