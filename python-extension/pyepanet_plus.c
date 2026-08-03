#include <Python.h>
#include "epanet_plus.h"
#include "types.h"


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

extern Project* ENgetdefaultproject();
PyObject* method_ENgettmpfiles(PyObject* self, PyObject* args)
{
    EN_Project ph = (EN_Project) ENgetdefaultproject();

    PyObject* pyTmpHydFname = PyUnicode_FromString(&ph->TmpHydFname[0]);
    PyObject* pyTmpOutFname = PyUnicode_FromString(&ph->TmpOutFname[0]);
    PyObject* pyTmpStatFname = PyUnicode_FromString(&ph->TmpStatFname[0]);

    PyObject* err = PyLong_FromLong(0);
    PyObject* r = PyTuple_Pack(4, err, pyTmpHydFname, pyTmpOutFname, pyTmpStatFname);
    Py_DECREF(err);
    Py_DECREF(pyTmpHydFname);
    Py_DECREF(pyTmpOutFname);
    Py_DECREF(pyTmpStatFname);

    return r;
}

PyObject* method_EN_gettmpfiles(PyObject* self, PyObject* args)
{
    uintptr_t ptr;

    if(!PyArg_ParseTuple(args, "K", &ptr)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* pyTmpHydFname = PyUnicode_FromString(&ph->TmpHydFname[0]);
    PyObject* pyTmpOutFname = PyUnicode_FromString(&ph->TmpOutFname[0]);
    PyObject* pyTmpStatFname = PyUnicode_FromString(&ph->TmpStatFname[0]);

    PyObject* err = PyLong_FromLong(0);
    PyObject* r = PyTuple_Pack(4, err, pyTmpHydFname, pyTmpOutFname, pyTmpStatFname);
    Py_DECREF(err);
    Py_DECREF(pyTmpHydFname);
    Py_DECREF(pyTmpOutFname);
    Py_DECREF(pyTmpStatFname);

    return r;
}