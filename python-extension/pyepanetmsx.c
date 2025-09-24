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

    int err = MSXENopen(inpFile, rptFile, outFile);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_MSXopen(PyObject* self, PyObject* args)
{
    char* fname = NULL;
    if(!PyArg_ParseTuple(args, "s", &fname)) {
        return NULL;
    }

    int err = MSXopen(fname);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_MSXsolveH(PyObject* self, PyObject* Py_UNUSED(args))
{
    int err = MSXsolveH();

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_MSXusehydfile(PyObject* self, PyObject* args)
{
    char* fname = NULL;
    if(!PyArg_ParseTuple(args, "s", &fname)) {
        return NULL;
    }

    int err = MSXusehydfile(fname);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_MSXsolveQ(PyObject* self, PyObject* Py_UNUSED(args))
{
    int err = MSXsolveQ();

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_MSXinit(PyObject* self, PyObject* args)
{
    int saveFlag;
    if(!PyArg_ParseTuple(args, "i", &saveFlag)) {
        return NULL;
    }   

    int err = MSXinit(saveFlag);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_MSXstep(PyObject* self, PyObject* args)
{
    double t, tleft;
    int err = MSXstep(&t, &tleft);

    return Py_BuildValue("(idd)", err, t, tleft);
}

PyObject* method_MSXsaveoutfile(PyObject* self, PyObject* args)
{
    char* fname = NULL;
    if(!PyArg_ParseTuple(args, "s", &fname)) {
        return NULL;
    }

    int err = MSXsaveoutfile(fname);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_MSXsavemsxfile(PyObject* self, PyObject* args)
{
    char* fname = NULL;
    if(!PyArg_ParseTuple(args, "s", &fname)) {
        return NULL;
    }

    int err = MSXsavemsxfile(fname);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_MSXreport(PyObject* self, PyObject* Py_UNUSED(args))
{
    int err = MSXreport();

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_MSXclose(PyObject* self, PyObject* Py_UNUSED(args))
{
    int err = MSXclose();

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_MSXENclose(PyObject* self, PyObject* Py_UNUSED(args))
{
    int err = MSXENclose();

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_MSXgetindex(PyObject* self, PyObject* args)
{
    int type, index;
    char* id = NULL;

    if(!PyArg_ParseTuple(args, "is", &type, &id)) {
        return NULL;
    }

    int err = MSXgetindex(type, id, &index);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(index));
}

PyObject* method_MSXgetIDlen(PyObject* self, PyObject* args)
{
    int type, index, len;
    if(!PyArg_ParseTuple(args, "ii", &type, &index)) {
        return NULL;
    }

    int err = MSXgetIDlen(type, index, &len);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(len));
}

PyObject* method_MSXgetID(PyObject* self, PyObject* args)
{
    int type, index;
    if(!PyArg_ParseTuple(args, "ii", &type, &index)) {
        return NULL;
    }

    char id[MAXID + 1]; // TODO: MSXgetIDlen
    int err = MSXgetID(type, index, &id[0], MAXID);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyUnicode_FromString(&id[0]));
}

PyObject* method_MSXgetcount(PyObject* self, PyObject* args)
{
    int type, count;
    if(!PyArg_ParseTuple(args, "i", &type)) {
        return NULL;
    }

    int err = MSXgetcount(type, &count);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(count));
}

PyObject* method_MSXgetspecies(PyObject* self, PyObject* args)
{
    int index, type;
    char units[MAXUNITS];
    double aTol, rTol;

    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }

    int err = MSXgetspecies(index, &type, &units[0], &aTol, &rTol);

    return PyTuple_Pack(5, PyLong_FromLong(err), PyLong_FromLong(type), PyUnicode_FromString(&units[0]), PyFloat_FromDouble(aTol), PyFloat_FromDouble(rTol));
}

PyObject* method_MSXgetconstant(PyObject* self, PyObject* args)
{
    int index;
    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }

    double value;
    int err = MSXgetconstant(index, &value);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyFloat_FromDouble(value));
}

PyObject* method_MSXgetparameter(PyObject* self, PyObject* args)
{
    int type, index, param;
    if(!PyArg_ParseTuple(args, "iii", &type, &index, &param)) {
        return NULL;
    }

    double value;
    int err = MSXgetparameter(type, index, param, &value);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyFloat_FromDouble(value));
}

PyObject* method_MSXgetsource(PyObject* self, PyObject* args)
{
    int node, species;
    if(!PyArg_ParseTuple(args, "ii", &node, &species)) {
        return NULL;
    }

    int type, pat;
    double level;
    int err = MSXgetsource(node, species, &type, &level, &pat);

    return PyTuple_Pack(4, PyLong_FromLong(err), PyLong_FromLong(type), PyFloat_FromDouble(level), PyLong_FromLong(pat));
}

PyObject* method_MSXgetpatternlen(PyObject* self, PyObject* args)
{
    int pat, len;
    if(!PyArg_ParseTuple(args, "i", &pat)) {
        return NULL;
    }

    int err = MSXgetpatternlen(pat, &len);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(len));
}

PyObject* method_MSXgetpatternvalue(PyObject* self, PyObject* args)
{
    int pat, period;
    if(!PyArg_ParseTuple(args, "ii", &pat, &period)) {
        return NULL;
    }   

    double value;
    int err = MSXgetpatternvalue(pat, period, &value);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyFloat_FromDouble(value));
}

PyObject* method_MSXgetinitqual(PyObject* self, PyObject* args)
{
    int type, index, species;
    if(!PyArg_ParseTuple(args, "iii", &type, &index, &species)) {
        return NULL;
    }    

    double value;
    int err = MSXgetinitqual(type, index, species, &value);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyFloat_FromDouble(value));
}

PyObject* method_MSXgetqual(PyObject* self, PyObject* args)
{
    int type, index, species;
    if(!PyArg_ParseTuple(args, "iii", &type, &index, &species)) {
        return NULL;
    }

    double value;
    int err = MSXgetqual(type, index, species, &value);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyFloat_FromDouble(value));
}

PyObject* method_MSXgeterror(PyObject* self, PyObject* args)
{
    int code;
    if(!PyArg_ParseTuple(args, "i", &code)) {
        return NULL;
    }
    
    char msg[MAXLINE + 1];
    int err = MSXgeterror(code, &msg[0], MAXLINE);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyUnicode_FromString(&msg[0]));
}

PyObject* method_MSXsetconstant(PyObject* self, PyObject* args)
{
    int index;
    double value;
    if(!PyArg_ParseTuple(args, "id", &index, &value)) {
        return NULL;
    }

    int err = MSXsetconstant(index, value);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_MSXsetparameter(PyObject* self, PyObject* args)
{
    int type, index, param;
    double value;
    if(!PyArg_ParseTuple(args, "iiid", &type, &index, &param, &value)) {
        return NULL;
    } 

    int err = MSXsetparameter(type, index, param, value);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_MSXsetinitqual(PyObject* self, PyObject* args)
{
    int type, index, species;
    double value;
    if(!PyArg_ParseTuple(args, "iiid", &type, &index, &species, &value)) {
        return NULL;
    }

    int err = MSXsetinitqual(type, index, species, value);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_MSXsetsource(PyObject* self, PyObject* args)
{
    int node, species, type, pat;
    double level;
    if(!PyArg_ParseTuple(args, "iiidi", &node, &species, &type, &level, &pat)) {
        return NULL;
    }

    int err = MSXsetsource(node, species, type, level, pat);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_MSXsetpatternvalue(PyObject* self, PyObject* args)
{
    int pat, period;
    double value;
    if(!PyArg_ParseTuple(args, "iid", &pat, &period, &value)) {
        return NULL;
    }

    int err = MSXsetpatternvalue(pat, period, value);

    return PyTuple_Pack(1, PyLong_FromLong(err));
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

    int err = MSXsetpattern(pat, multRaw, len);
    free(multRaw);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_MSXaddpattern(PyObject* self, PyObject* args)
{
    char* id = NULL;
    if(!PyArg_ParseTuple(args, "s", &id)) {
        return NULL;
    }

    int err = MSXaddpattern(id);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}
