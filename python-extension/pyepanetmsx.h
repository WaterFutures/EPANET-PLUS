#include <Python.h>


PyObject* method_MSXENopen(PyObject* self, PyObject* args);
PyObject* method_MSXopen(PyObject* self, PyObject* args);
PyObject* method_MSXsolveH(PyObject* self, PyObject* Py_UNUSED(args));
PyObject* method_MSXusehydfile(PyObject* self, PyObject* args);
PyObject* method_MSXsolveQ(PyObject* self, PyObject* Py_UNUSED(args));
PyObject* method_MSXinit(PyObject* self, PyObject* args);
PyObject* method_MSXstep(PyObject* self, PyObject* args);
PyObject* method_MSXsaveoutfile(PyObject* self, PyObject* args);
PyObject* method_MSXsavemsxfile(PyObject* self, PyObject* args);
PyObject* method_MSXreport(PyObject* self, PyObject* Py_UNUSED(args));
PyObject* method_MSXclose(PyObject* self, PyObject* Py_UNUSED(args));
PyObject* method_MSXENclose(PyObject* self, PyObject* Py_UNUSED(args));
PyObject* method_MSXgetindex(PyObject* self, PyObject* args);
PyObject* method_MSXgetIDlen(PyObject* self, PyObject* args);
PyObject* method_MSXgetID(PyObject* self, PyObject* args);
PyObject* method_MSXgetcount(PyObject* self, PyObject* args);
PyObject* method_MSXgetspecies(PyObject* self, PyObject* args);
PyObject* method_MSXgetconstant(PyObject* self, PyObject* args);
PyObject* method_MSXgetparameter(PyObject* self, PyObject* args);
PyObject* method_MSXgetsource(PyObject* self, PyObject* args);
PyObject* method_MSXgetpatternlen(PyObject* self, PyObject* args);
PyObject* method_MSXgetpatternvalue(PyObject* self, PyObject* args);
PyObject* method_MSXgetinitqual(PyObject* self, PyObject* args);
PyObject* method_MSXgetqual(PyObject* self, PyObject* args);
PyObject* method_MSXgeterror(PyObject* self, PyObject* args);
PyObject* method_MSXsetconstant(PyObject* self, PyObject* args);
PyObject* method_MSXsetparameter(PyObject* self, PyObject* args);
PyObject* method_MSXsetinitqual(PyObject* self, PyObject* args);
PyObject* method_MSXsetsource(PyObject* self, PyObject* args);
PyObject* method_MSXsetpatternvalue(PyObject* self, PyObject* args);
PyObject* method_MSXsetpattern(PyObject* self, PyObject* args);
PyObject* method_MSXaddpattern(PyObject* self, PyObject* args);
