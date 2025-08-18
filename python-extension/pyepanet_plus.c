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

    int err = ENopenfrombuffer(inpBuffer, inpFile, rptFile, outFile);

    return PyTuple_Pack(1, PyLong_FromLong(err));
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

    int err = EN_openfrombuffer(ph, inpBuffer, inpFile, rptFile, outFile);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}
