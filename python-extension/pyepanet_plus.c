#include <Python.h>
#include "epanet_plus.h"


PyObject* method_ENopenfrombuffer(PyObject* self, PyObject* args)
{
    char* inpBuffer = NULL;
    char* inpFile = NULL;
    char* rptFile = NULL;
    char* outFile = NULL;

    if(!PyArg_ParseTuple(args, "ssss", &inpBuffer, &inpFile, &rptFile, &outFile)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENopenfrombuffer(inpBuffer, inpFile, rptFile, outFile));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_openfrombuffer(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    char* inpBuffer = NULL;
    char* inpFile = NULL;
    char* rptFile = NULL;
    char* outFile = NULL;

    if(!PyArg_ParseTuple(args, "Kssss", &ptr, &inpBuffer, &inpFile, &rptFile, &outFile)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_openfrombuffer(ph, inpBuffer, inpFile, rptFile, outFile));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}
