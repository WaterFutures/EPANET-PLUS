#include <Python.h>
#include "epanetmsx.h"
#include "msxtypes.h"

#define   MAXID     31       // Max. # characters in ID name


PyObject* method_MSXENopen(PyObject* self, PyObject* args)
{
    char *inpFile, *rptFile, *outFile = NULL;

    if(!PyArg_ParseTuple(args, "sss", &inpFile, &rptFile, &outFile)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(MSXENopen(inpFile, rptFile, outFile));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_MSXopen(PyObject* self, PyObject* args)
{
    char* fname = NULL;
    if(!PyArg_ParseTuple(args, "s", &fname)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(MSXopen(fname));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_MSXsolveH(PyObject* self, PyObject* Py_UNUSED(args))
{
    PyObject* err = PyLong_FromLong(MSXsolveH());

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_MSXusehydfile(PyObject* self, PyObject* args)
{
    char* fname = NULL;
    if(!PyArg_ParseTuple(args, "s", &fname)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(MSXusehydfile(fname));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_MSXsolveQ(PyObject* self, PyObject* Py_UNUSED(args))
{
    PyObject* err = PyLong_FromLong(MSXsolveQ());

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_MSXinit(PyObject* self, PyObject* args)
{
    int saveFlag;
    if(!PyArg_ParseTuple(args, "i", &saveFlag)) {
        return NULL;
    }   

    PyObject* err = PyLong_FromLong(MSXinit(saveFlag));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_MSXstep(PyObject* self, PyObject* args)
{
    double t, tleft;
    PyObject* err = PyLong_FromLong(MSXstep(&t, &tleft));
    PyObject* pyT = PyFloat_FromDouble(t);
    PyObject* pyTLeft = PyFloat_FromDouble(tleft);

    PyObject* r = PyTuple_Pack(3, err, pyT, pyTLeft);
    Py_DECREF(err);
    Py_DECREF(pyT);
    Py_DECREF(pyTLeft);

    return r;
}

PyObject* method_MSXsaveoutfile(PyObject* self, PyObject* args)
{
    char* fname = NULL;
    if(!PyArg_ParseTuple(args, "s", &fname)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(MSXsaveoutfile(fname));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_MSXsavemsxfile(PyObject* self, PyObject* args)
{
    char* fname = NULL;
    if(!PyArg_ParseTuple(args, "s", &fname)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(MSXsavemsxfile(fname));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_MSXreport(PyObject* self, PyObject* Py_UNUSED(args))
{
    PyObject* err = PyLong_FromLong(MSXreport());

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_MSXclose(PyObject* self, PyObject* Py_UNUSED(args))
{
    PyObject* err = PyLong_FromLong(MSXclose());

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_MSXENclose(PyObject* self, PyObject* Py_UNUSED(args))
{
    PyObject* err = PyLong_FromLong(MSXENclose());

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_MSXgetindex(PyObject* self, PyObject* args)
{
    int type, index;
    char* id = NULL;

    if(!PyArg_ParseTuple(args, "is", &type, &id)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(MSXgetindex(type, id, &index));
    PyObject* pyIndex = PyLong_FromLong(index);

    PyObject* r = PyTuple_Pack(2, err, pyIndex);
    Py_DECREF(err);
    Py_DECREF(pyIndex);

    return r;
}

PyObject* method_MSXgetIDlen(PyObject* self, PyObject* args)
{
    int type, index, len;
    if(!PyArg_ParseTuple(args, "ii", &type, &index)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(MSXgetIDlen(type, index, &len));
    PyObject* pyLen = PyLong_FromLong(len);

    PyObject* r = PyTuple_Pack(2, err, pyLen);
    Py_DECREF(err);
    Py_DECREF(pyLen);

    return r;
}

PyObject* method_MSXgetID(PyObject* self, PyObject* args)
{
    int type, index;
    if(!PyArg_ParseTuple(args, "ii", &type, &index)) {
        return NULL;
    }

    char id[MAXID + 1]; // TODO: MSXgetIDlen
    PyObject* err = PyLong_FromLong(MSXgetID(type, index, &id[0], MAXID));
    PyObject* pyId = PyUnicode_FromString(&id[0]);

    PyObject* r = PyTuple_Pack(2, err, pyId);
    Py_DECREF(err);
    Py_DECREF(pyId);

    return r;
}

PyObject* method_MSXgetcount(PyObject* self, PyObject* args)
{
    int type, count;
    if(!PyArg_ParseTuple(args, "i", &type)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(MSXgetcount(type, &count));
    PyObject* pyCount = PyLong_FromLong(count);

    PyObject* r =  PyTuple_Pack(2, err, pyCount);
    Py_DECREF(err);
    Py_DECREF(pyCount);

    return r;
}

PyObject* method_MSXgetspecies(PyObject* self, PyObject* args)
{
    int index, type;
    char units[MAXUNITS];
    double aTol, rTol;

    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(MSXgetspecies(index, &type, &units[0], &aTol, &rTol));
    PyObject* pyType = PyLong_FromLong(type);
    PyObject* pyUnits = PyUnicode_FromString(&units[0]);
    PyObject* pyATol = PyFloat_FromDouble(aTol);
    PyObject* pyRTol = PyFloat_FromDouble(rTol);

    PyObject* r = PyTuple_Pack(5, err, pyType, pyUnits, pyATol, pyRTol);
    Py_DECREF(err);
    Py_DECREF(pyType);
    Py_DECREF(pyUnits);
    Py_DECREF(pyATol);
    Py_DECREF(pyRTol);

    return r;
}

PyObject* method_MSXgetconstant(PyObject* self, PyObject* args)
{
    int index;
    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }

    double value;
    PyObject* err = PyLong_FromLong(MSXgetconstant(index, &value));
    PyObject* pyValue = PyFloat_FromDouble(value);

    PyObject* r = PyTuple_Pack(2, err, pyValue);
    Py_DECREF(err);
    Py_DECREF(pyValue);

    return r;
}

PyObject* method_MSXgetparameter(PyObject* self, PyObject* args)
{
    int type, index, param;
    if(!PyArg_ParseTuple(args, "iii", &type, &index, &param)) {
        return NULL;
    }

    double value;
    PyObject* err = PyLong_FromLong(MSXgetparameter(type, index, param, &value));
    PyObject* pyValue = PyFloat_FromDouble(value);

    PyObject* r = PyTuple_Pack(2, err, pyValue);
    Py_DECREF(err);
    Py_DECREF(pyValue);

    return r;
}

PyObject* method_MSXgetsource(PyObject* self, PyObject* args)
{
    int node, species;
    if(!PyArg_ParseTuple(args, "ii", &node, &species)) {
        return NULL;
    }

    int type, pat;
    double level;
    PyObject* err = PyLong_FromLong(MSXgetsource(node, species, &type, &level, &pat));
    PyObject* pyType = PyLong_FromLong(type);
    PyObject* pyLevel = PyFloat_FromDouble(level);
    PyObject* pyPat = PyLong_FromLong(pat);

    PyObject* r =  PyTuple_Pack(4, err, pyType, pyLevel, pyPat);
    Py_DECREF(err);
    Py_DECREF(pyType);
    Py_DECREF(pyLevel);
    Py_DECREF(pyPat);

    return r;
}

PyObject* method_MSXgetpatternlen(PyObject* self, PyObject* args)
{
    int pat, len;
    if(!PyArg_ParseTuple(args, "i", &pat)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(MSXgetpatternlen(pat, &len));
    PyObject* pyLen = PyLong_FromLong(len);

    PyObject* r = PyTuple_Pack(2, err, pyLen);
    Py_DECREF(err);
    Py_DECREF(pyLen);

    return r;
}

PyObject* method_MSXgetpatternvalue(PyObject* self, PyObject* args)
{
    int pat, period;
    if(!PyArg_ParseTuple(args, "ii", &pat, &period)) {
        return NULL;
    }   

    double value;
    PyObject* err = PyLong_FromLong(MSXgetpatternvalue(pat, period, &value));
    PyObject* pyValue = PyFloat_FromDouble(value);

    PyObject* r = PyTuple_Pack(2, err, pyValue);
    Py_DECREF(err);
    Py_DECREF(pyValue);

    return r;
}

PyObject* method_MSXgetinitqual(PyObject* self, PyObject* args)
{
    int type, index, species;
    if(!PyArg_ParseTuple(args, "iii", &type, &index, &species)) {
        return NULL;
    }    

    double value;
    PyObject* err = PyLong_FromLong(MSXgetinitqual(type, index, species, &value));
    PyObject* pyValue = PyFloat_FromDouble(value);

    PyObject* r = PyTuple_Pack(2, err, pyValue);
    Py_DECREF(err);
    Py_DECREF(pyValue);

    return r;
}

PyObject* method_MSXgetqual(PyObject* self, PyObject* args)
{
    int type, index, species;
    if(!PyArg_ParseTuple(args, "iii", &type, &index, &species)) {
        return NULL;
    }

    double value;
    PyObject* err = PyLong_FromLong(MSXgetqual(type, index, species, &value));
    PyObject* pyValue = PyFloat_FromDouble(value);

    PyObject* r = PyTuple_Pack(2, err, pyValue);
    Py_DECREF(err);
    Py_DECREF(pyValue);

    return r;
}

PyObject* method_MSXgeterror(PyObject* self, PyObject* args)
{
    int code;
    if(!PyArg_ParseTuple(args, "i", &code)) {
        return NULL;
    }
    
    char msg[MAXLINE + 1];
    PyObject* err = PyLong_FromLong(MSXgeterror(code, &msg[0], MAXLINE));
    PyObject* pyMsg = PyUnicode_FromString(&msg[0]);

    PyObject* r = PyTuple_Pack(2, err, pyMsg);
    Py_DECREF(err);
    Py_DECREF(pyMsg);

    return r;
}

PyObject* method_MSXsetconstant(PyObject* self, PyObject* args)
{
    int index;
    double value;
    if(!PyArg_ParseTuple(args, "id", &index, &value)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(MSXsetconstant(index, value));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_MSXsetparameter(PyObject* self, PyObject* args)
{
    int type, index, param;
    double value;
    if(!PyArg_ParseTuple(args, "iiid", &type, &index, &param, &value)) {
        return NULL;
    } 

    PyObject* err = PyLong_FromLong(MSXsetparameter(type, index, param, value));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_MSXsetinitqual(PyObject* self, PyObject* args)
{
    int type, index, species;
    double value;
    if(!PyArg_ParseTuple(args, "iiid", &type, &index, &species, &value)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(MSXsetinitqual(type, index, species, value));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_MSXsetsource(PyObject* self, PyObject* args)
{
    int node, species, type, pat;
    double level;
    if(!PyArg_ParseTuple(args, "iiidi", &node, &species, &type, &level, &pat)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(MSXsetsource(node, species, type, level, pat));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_MSXsetpatternvalue(PyObject* self, PyObject* args)
{
    int pat, period;
    double value;
    if(!PyArg_ParseTuple(args, "iid", &pat, &period, &value)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(MSXsetpatternvalue(pat, period, value));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_MSXsetpattern(PyObject* self, PyObject* args)
{
    int pat, len;
    PyListObject* mult = NULL;
    if(!PyArg_ParseTuple(args, "iOi", &pat, &mult, &len)) {
        return NULL;
    }

    double* multRaw = (double*) malloc(sizeof(double) * len);
    for(int i=0; i != len; i++) {
        multRaw[i] = PyFloat_AsDouble(PyList_GET_ITEM(mult, i));
    }

    PyObject* err = PyLong_FromLong(MSXsetpattern(pat, multRaw, len));
    free(multRaw);

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_MSXaddpattern(PyObject* self, PyObject* args)
{
    char* id = NULL;
    if(!PyArg_ParseTuple(args, "s", &id)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(MSXaddpattern(id));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}
