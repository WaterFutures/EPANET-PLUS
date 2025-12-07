#include <Python.h>
#include "epanet2_2.h"
#include "types.h"





PyObject* method_EN_createproject(PyObject* self, PyObject* Py_UNUSED(args))
{
    EN_Project ph;
    int err = EN_createproject(&ph);
 
    return Py_BuildValue("(iK)", err, (uintptr_t)&(*ph));
}

PyObject* method_EN_deleteproject(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    if(!PyArg_ParseTuple(args, "K", &ptr)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_deleteproject(ph));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_init(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    char* rptFile = NULL;
    char* outFile = NULL;
    int unitsType, headLossType;

    if(!PyArg_ParseTuple(args, "Kssii", &ptr, &rptFile, &outFile, &unitsType, &headLossType)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_init(ph, rptFile, outFile, unitsType, headLossType));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_open(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    char* inpFile = NULL;
    char* rptFile = NULL;
    char* outFile = NULL;

    if(!PyArg_ParseTuple(args, "Ksss", &ptr, &inpFile, &rptFile, &outFile)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_open(ph, inpFile, rptFile, outFile));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_openX(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    char* inpFile = NULL;
    char* rptFile = NULL;
    char* outFile = NULL;

    if(!PyArg_ParseTuple(args, "Ksss", &ptr, &inpFile, &rptFile, &outFile)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_openX(ph, inpFile, rptFile, outFile));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_gettitle(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    if(!PyArg_ParseTuple(args, "K", &ptr)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    char out_line1[TITLELEN + 1];
    char out_line2[TITLELEN + 1];
    char out_line3[TITLELEN + 1];
    PyObject* err = PyLong_FromLong(EN_gettitle(ph, &out_line1[0], &out_line2[0], &out_line3[0]));
    PyObject* pyOutLine1 = PyUnicode_FromString(&out_line1[0]);
    PyObject* pyOutLine2 = PyUnicode_FromString(&out_line2[0]);
    PyObject* pyOutLine3 = PyUnicode_FromString(&out_line3[0]);


    PyObject* r = PyTuple_Pack(4, err, pyOutLine1, pyOutLine2, pyOutLine3);
    Py_DECREF(err);
    Py_DECREF(pyOutLine1);
    Py_DECREF(pyOutLine2);
    Py_DECREF(pyOutLine3);

    return r;
}

PyObject* method_EN_settitle(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    char* line1 = NULL;
    char* line2 = NULL;
    char* line3 = NULL;
    if(!PyArg_ParseTuple(args, "Ksss", &ptr, &line1, &line2, &line3)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_settitle(ph, line1, line2, line3));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_getcomment(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int object, index;
    if(!PyArg_ParseTuple(args, "Kii", &ptr, &object, &index)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    char out_comment[MAXLINE + 1];
    PyObject* err = PyLong_FromLong(EN_getcomment(ph, object, index, &out_comment[0]));
    PyObject* pyOutComment = PyUnicode_FromString(&out_comment[0]);

    PyObject* r = PyTuple_Pack(2, err, pyOutComment);
    Py_DECREF(err);
    Py_DECREF(pyOutComment);

    return r;
}

PyObject* method_EN_setcomment(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int object, index;
    char* comment = NULL;
    if(!PyArg_ParseTuple(args, "Kiis", &ptr, &object, &index, &comment)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_setcomment(ph, object, index, comment));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_getcount(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int object;
    if(!PyArg_ParseTuple(args, "Ki", &ptr, &object)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int count;
    PyObject* err = PyLong_FromLong(EN_getcount(ph, object, &count));
    PyObject* pyCount = PyLong_FromLong(count);

    PyObject* r = PyTuple_Pack(2, err, pyCount);
    Py_DECREF(err);
    Py_DECREF(pyCount);

    return r;
}

PyObject* method_EN_saveinpfile(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    char* filename = NULL;
    if(!PyArg_ParseTuple(args, "Ks", &ptr, &filename)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;  

    PyObject* err = PyLong_FromLong(EN_saveinpfile(ph, filename));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_close(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    if(!PyArg_ParseTuple(args, "K", &ptr)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_close(ph));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_solveH(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    if(!PyArg_ParseTuple(args, "K", &ptr)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_solveH(ph));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_usehydfile(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    char* filename = NULL;
    if(!PyArg_ParseTuple(args, "Ks", &ptr, &filename)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_usehydfile(ph, filename));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_openH(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    if(!PyArg_ParseTuple(args, "K", &ptr)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_openH(ph));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_initH(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int initFlag;
    if(!PyArg_ParseTuple(args, "Ki", &ptr, &initFlag)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_initH(ph, initFlag));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_runH(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    if(!PyArg_ParseTuple(args, "K", &ptr)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    long currentTime;
    PyObject* err = PyLong_FromLong(EN_runH(ph, &currentTime));
    PyObject* pyCurrentTime = PyLong_FromLong(currentTime);

    PyObject* r = PyTuple_Pack(2, err, pyCurrentTime);
    Py_DECREF(err);
    Py_DECREF(pyCurrentTime);

    return r;
}

PyObject* method_EN_nextH(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    if(!PyArg_ParseTuple(args, "K", &ptr)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    long tStep;
    PyObject* err = PyLong_FromLong(EN_nextH(ph, &tStep));
    PyObject* pyTStep = PyLong_FromLong(tStep);

    PyObject* r = PyTuple_Pack(2, err, pyTStep);
    Py_DECREF(err);
    Py_DECREF(pyTStep);

    return r;
}

PyObject* method_EN_saveH(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    if(!PyArg_ParseTuple(args, "K", &ptr)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_saveH(ph));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_savehydfile(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    char* filename = NULL;
    if(!PyArg_ParseTuple(args, "Ks", &ptr, &filename)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_savehydfile(ph, filename));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_closeH(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    if(!PyArg_ParseTuple(args, "K", &ptr)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_closeH(ph));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_solveQ(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    if(!PyArg_ParseTuple(args, "K", &ptr)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_solveQ(ph));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_openQ(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    if(!PyArg_ParseTuple(args, "K", &ptr)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_openQ(ph));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_initQ(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int saveFlag;
    if(!PyArg_ParseTuple(args, "Ki", &ptr, &saveFlag)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_initQ(ph, saveFlag));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_runQ(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    if(!PyArg_ParseTuple(args, "K", &ptr)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    long currentTime;
    PyObject* err = PyLong_FromLong(EN_runQ(ph, &currentTime));
    PyObject* pyCurrentTime = PyLong_FromLong(currentTime);

    PyObject* r = PyTuple_Pack(2, err, pyCurrentTime);
    Py_DECREF(err);
    Py_DECREF(pyCurrentTime);

    return r;
}

PyObject* method_EN_nextQ(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    if(!PyArg_ParseTuple(args, "K", &ptr)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    long tStep;
    PyObject* err = PyLong_FromLong(EN_nextQ(ph, &tStep));
    PyObject* pyTStep = PyLong_FromLong(tStep);

    PyObject* r = PyTuple_Pack(2, err, pyTStep);
    Py_DECREF(err);
    Py_DECREF(pyTStep);

    return r;
}

PyObject* method_EN_stepQ(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    if(!PyArg_ParseTuple(args, "K", &ptr)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    long timeLeft;
    PyObject* err = PyLong_FromLong(EN_stepQ(ph, &timeLeft));
    PyObject* pyTimeLeft = PyLong_FromLong(timeLeft);

    PyObject* r = PyTuple_Pack(2, err, pyTimeLeft);
    Py_DECREF(err);
    Py_DECREF(pyTimeLeft);

    return r;
}

PyObject* method_EN_closeQ(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    if(!PyArg_ParseTuple(args, "K", &ptr)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_closeQ(ph));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_writeline(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    char* line = NULL;
    if(!PyArg_ParseTuple(args, "Ks", &ptr, &line)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_writeline(ph, line));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_report(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    if(!PyArg_ParseTuple(args, "K", &ptr)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_report(ph));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_copyreport(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    char* filename = NULL;
    if(!PyArg_ParseTuple(args, "K", &ptr, &filename)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_copyreport(ph, filename));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_clearreport(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    if(!PyArg_ParseTuple(args, "K", &ptr)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_clearreport(ph));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_resetreport(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    if(!PyArg_ParseTuple(args, "K", &ptr)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_resetreport(ph));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_setreport(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    char* format = NULL;
    if(!PyArg_ParseTuple(args, "Ks", &ptr, &format)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_setreport(ph, format));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_setstatusreport(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int level;
    if(!PyArg_ParseTuple(args, "Ki", &ptr, &level)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_setstatusreport(ph, level));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_getversion(PyObject* self, PyObject* args)
{
    int version;
    PyObject* err = PyLong_FromLong(EN_getversion(&version));
    PyObject* pyVersion = PyLong_FromLong(version);

    PyObject* r = PyTuple_Pack(2, err, pyVersion);
    Py_DECREF(err);
    Py_DECREF(pyVersion);

    return r;
}

PyObject* method_EN_geterror(PyObject* self, PyObject* args)
{
    int errcode;
    if(!PyArg_ParseTuple(args, "i", &errcode)) {
        return NULL;
    }
    
    char out_errmsg[MAXMSG + 1];
    PyObject* err = PyLong_FromLong(EN_geterror(errcode, &out_errmsg[0], MAXMSG + 1));
    PyObject* pyOutErrmsg = PyUnicode_FromString(&out_errmsg[0]);

    PyObject* r = PyTuple_Pack(2, err, pyOutErrmsg);
    Py_DECREF(err);
    Py_DECREF(pyOutErrmsg);

    return r;
}

PyObject* method_EN_getstatistic(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int type;
    if(!PyArg_ParseTuple(args, "Kii", &ptr, &type)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    double value;
    PyObject* err = PyLong_FromLong(EN_getstatistic(ph, type, &value));
    PyObject* pyValue = PyFloat_FromDouble(value);

    PyObject* r = PyTuple_Pack(2, err, pyValue);
    Py_DECREF(err);
    Py_DECREF(pyValue);

    return r;
}

PyObject* method_EN_getresultindex(PyObject* self, PyObject* args)
{
    int type, index, value;
    uintptr_t ptr;
    if(!PyArg_ParseTuple(args, "Kii", &ptr, &type, &index)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_getresultindex(ph, type, index, &value));
    PyObject* pyValue = PyLong_FromLong(value);

    PyObject* r = PyTuple_Pack(2, err, pyValue);
    Py_DECREF(err);
    Py_DECREF(pyValue);

    return r;
}

PyObject* method_EN_getoption(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int option;
    if(!PyArg_ParseTuple(args, "Ki", &ptr, &option)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    double value;
    PyObject* err = PyLong_FromLong(EN_getoption(ph, option, &value));
    PyObject* pyValue = PyFloat_FromDouble(value);

    PyObject* r = PyTuple_Pack(2, err, pyValue);
    Py_DECREF(err);
    Py_DECREF(pyValue);

    return r;
}

PyObject* method_EN_setoption(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int option;
    double value;
    if(!PyArg_ParseTuple(args, "Kid", &ptr, &option, &value)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_setoption(ph, option, value));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_getflowunits(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    if(!PyArg_ParseTuple(args, "K", &ptr)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int units;
    PyObject* err = PyLong_FromLong(EN_getflowunits(ph, &units));
    PyObject* pyUnits = PyLong_FromLong(units);

    PyObject* r = PyTuple_Pack(2, err, pyUnits);
    Py_DECREF(err);
    Py_DECREF(pyUnits);

    return r;
}

PyObject* method_EN_setflowunits(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int units;
    if(!PyArg_ParseTuple(args, "Ki", &ptr, &units)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_setflowunits(ph, units));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_gettimeparam(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int param;
    if(!PyArg_ParseTuple(args, "Ki", &ptr, &param)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    long value;
    PyObject* err = PyLong_FromLong(EN_gettimeparam(ph, param, &value));
    PyObject* pyValue = PyLong_FromLong(value);

    PyObject* r = PyTuple_Pack(2, err, pyValue);
    Py_DECREF(err);
    Py_DECREF(pyValue);

    return r;
}

PyObject* method_EN_settimeparam(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int param;
    long value;
    if(!PyArg_ParseTuple(args, "Kil", &ptr, &param, &value)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_settimeparam(ph, param, value));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_getqualinfo(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    if(!PyArg_ParseTuple(args, "K", &ptr)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int qualType, traceNode;
    char out_chemName[MAXID + 1];
    char out_chemUnits[MAXID + 1];
    PyObject* err = PyLong_FromLong(EN_getqualinfo(ph, &qualType, &out_chemName[0], &out_chemUnits[0], &traceNode));
    PyObject* pyQualType = PyLong_FromLong(qualType);
    PyObject* pyChemName = PyUnicode_FromString(&out_chemName[0]);
    PyObject* pyChemUnits = PyUnicode_FromString(&out_chemUnits[0]);
    PyObject* pyTraceNode = PyLong_FromLong(traceNode);

    PyObject* r = PyTuple_Pack(5, err, pyQualType, pyChemName, pyChemUnits, pyTraceNode);
    Py_DECREF(err);
    Py_DECREF(pyQualType);
    Py_DECREF(pyChemName);
    Py_DECREF(pyChemUnits);
    Py_DECREF(pyTraceNode);

    return r;
}

PyObject* method_EN_getqualtype(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    if(!PyArg_ParseTuple(args, "K", &ptr)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;
    
    int qualType, traceNode;
    PyObject* err = PyLong_FromLong(EN_getqualtype(ph, &qualType, &traceNode));
    PyObject* pyQualType = PyLong_FromLong(qualType);
    PyObject* pyTraceNode = PyLong_FromLong(traceNode);

    PyObject* r = PyTuple_Pack(3, err, pyQualType, pyTraceNode);
    Py_DECREF(err);
    Py_DECREF(pyQualType);
    Py_DECREF(pyTraceNode);

    return r;
}

PyObject* method_EN_setqualtype(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int qualType;
    char* chemName = NULL;
    char* chemUnits = NULL;
    char* traceNode = NULL;
    if(!PyArg_ParseTuple(args, "Kisss", &ptr, &qualType, &chemName, &chemUnits, &traceNode)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_setqualtype(ph, qualType, chemName, chemUnits, traceNode));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_addnode(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    char* id = NULL;
    int nodeType;
    if(!PyArg_ParseTuple(args, "Ksi", &ptr, &id, &nodeType)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int index;
    PyObject* err = PyLong_FromLong(EN_addnode(ph, id, nodeType, &index));
    PyObject* pyIndex = PyLong_FromLong(index);

    PyObject* r = PyTuple_Pack(2, err, pyIndex);
    Py_DECREF(err);
    Py_DECREF(pyIndex);

    return r;
}

PyObject* method_EN_deletenode(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index, actionCode;
    if(!PyArg_ParseTuple(args, "Kii", &ptr, &index, &actionCode)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_deletenode(ph, index, actionCode));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_getnodeindex(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    char* id = NULL;
    if(!PyArg_ParseTuple(args, "Ks", &ptr, &id)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int index;
    PyObject* err = PyLong_FromLong(EN_getnodeindex(ph, id, &index));
    PyObject* pyIndex = PyLong_FromLong(index);

    PyObject* r = PyTuple_Pack(2, err, pyIndex);
    Py_DECREF(err);
    Py_DECREF(pyIndex);

    return r;
}

PyObject* method_EN_getnodeid(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index;
    if(!PyArg_ParseTuple(args, "Ki", &ptr, &index)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    char out_id[MAXID + 1];
    PyObject* err = PyLong_FromLong(EN_getnodeid(ph, index, &out_id[0]));
    PyObject* pyOutId = PyUnicode_FromString(&out_id[0]);

    PyObject* r = PyTuple_Pack(2, err, pyOutId);
    Py_DECREF(err);
    Py_DECREF(pyOutId);

    return r;
}

PyObject* method_EN_setnodeid(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index;
    char* newid = NULL;
    if(!PyArg_ParseTuple(args, "Kis", &ptr, &index, &newid)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_setnodeid(ph, index, newid));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_getnodetype(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index;
    if(!PyArg_ParseTuple(args, "Ki", &ptr, &index)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int nodeType;
    PyObject* err = PyLong_FromLong(EN_getnodetype(ph, index, &nodeType));
    PyObject* pyNodeType = PyLong_FromLong(nodeType);

    PyObject* r = PyTuple_Pack(2, err, pyNodeType);
    Py_DECREF(err);
    Py_DECREF(pyNodeType);

    return r;
}

PyObject* method_EN_getnodevalue(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index, property;
    if(!PyArg_ParseTuple(args, "Kii", &ptr, &index, &property)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    double value;
    PyObject* err = PyLong_FromLong(EN_getnodevalue(ph, index, property, &value));
    PyObject* pyValue = PyFloat_FromDouble(value);

    PyObject* r = PyTuple_Pack(2, err, pyValue);
    Py_DECREF(err);
    Py_DECREF(pyValue);

    return r;
}

PyObject* method_EN_setnodevalue(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index, property;
    double value;
    if(!PyArg_ParseTuple(args, "Kiid", &ptr, &index, &property, &value)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_setnodevalue(ph, index, property, value));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_setjuncdata(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index;
    double elev, dmnd;
    char* dmndpat = NULL;
    if(!PyArg_ParseTuple(args, "Kidds", &ptr, &index, &elev, &dmnd, &dmndpat)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_setjuncdata(ph, index, elev, dmnd, dmndpat));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_settankdata(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index;
    double elev, initlvl, minlvl, maxlvl, diam, minvol;
    char* volcurve = NULL;
    if(!PyArg_ParseTuple(args, "Kidddddds", &ptr, &index, &elev, &initlvl, &minlvl, &maxlvl, &diam, &minvol, &volcurve)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_settankdata(ph, index, elev, initlvl, minlvl, maxlvl, diam, minvol, volcurve));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_getcoord(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index;
    if(!PyArg_ParseTuple(args, "Ki", &ptr, &index)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;
    
    double x, y;
    PyObject* err = PyLong_FromLong(EN_getcoord(ph, index, &x, &y));
    PyObject* pyX = PyFloat_FromDouble(x);
    PyObject* pyY = PyFloat_FromDouble(y);

    PyObject* r = PyTuple_Pack(3, err, pyX, pyY);
    Py_DECREF(err);
    Py_DECREF(pyX);
    Py_DECREF(pyY);

    return r;
}

PyObject* method_EN_setcoord(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index;
    double x, y;
    if(!PyArg_ParseTuple(args, "Kidd", &ptr, &index, &x, &y)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_setcoord(ph, index, x, y));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_getdemandmodel(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    if(!PyArg_ParseTuple(args, "K", &ptr)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int type;
    double pmin, preq, pexp;
    PyObject* err = PyLong_FromLong(EN_getdemandmodel(ph, &type, &pmin, &preq, &pexp));
    PyObject* pyType = PyLong_FromLong(type);
    PyObject* pyPMin = PyFloat_FromDouble(pmin);
    PyObject* pyPReq = PyFloat_FromDouble(preq);
    PyObject* pyPExp = PyFloat_FromDouble(pexp);

    PyObject* r = PyTuple_Pack(5, err, pyType, pyPMin, pyPReq, pyPExp);
    Py_DECREF(err);
    Py_DECREF(pyType);
    Py_DECREF(pyPMin);
    Py_DECREF(pyPReq);
    Py_DECREF(pyPExp);

    return r;
}

PyObject* method_EN_setdemandmodel(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int type;
    double pmin, preq, pexp;
    if(!PyArg_ParseTuple(args, "Kiddd", &ptr, &type, &pmin, &preq, &pexp)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_setdemandmodel(ph, type, pmin, preq, pexp));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_adddemand(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int nodeIndex;
    double baseDemand;
    char* demandPattern = NULL;
    char* demandName = NULL;
    if(!PyArg_ParseTuple(args, "Kidss", &ptr, &nodeIndex, &baseDemand, &demandPattern, &demandName)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_adddemand(ph, nodeIndex, baseDemand, demandPattern, demandName));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_deletedemand(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int nodeIndex, demandIndex;
    if(!PyArg_ParseTuple(args, "Kii", &ptr, &nodeIndex, &demandIndex)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_deletedemand(ph, nodeIndex, demandIndex));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_getdemandindex(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int nodeIndex;
    char* demandName = NULL;
    if(!PyArg_ParseTuple(args, "Ki", &ptr, &nodeIndex, &demandName)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int demandIndex;
    PyObject* err = PyLong_FromLong(EN_getdemandindex(ph, nodeIndex, demandName, &demandIndex));
    PyObject* pyDemandIndex = PyLong_FromLong(demandIndex);

    PyObject* r = PyTuple_Pack(2, err, pyDemandIndex);
    Py_DECREF(err);
    Py_DECREF(pyDemandIndex);

    return r;
}

PyObject* method_EN_getnumdemands(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int nodeIndex;
    if(!PyArg_ParseTuple(args, "Ki", &ptr, &nodeIndex)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int numDemands;
    PyObject* err = PyLong_FromLong(EN_getnumdemands(ph, nodeIndex, &numDemands));
    PyObject* pyNumDemands = PyLong_FromLong(numDemands);

    PyObject* r = PyTuple_Pack(2, err, pyNumDemands);
    Py_DECREF(err);
    Py_DECREF(pyNumDemands);

    return r;
}

PyObject* method_EN_getbasedemand(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int nodeIndex, demandIndex;
    if(!PyArg_ParseTuple(args, "Kii", &ptr, &nodeIndex, &demandIndex)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    double baseDemand;
    PyObject* err = PyLong_FromLong(EN_getbasedemand(ph, nodeIndex, demandIndex, &baseDemand));
    PyObject* pyBaseDemand = PyFloat_FromDouble(baseDemand);

    PyObject* r = PyTuple_Pack(2, err, pyBaseDemand);
    Py_DECREF(err);
    Py_DECREF(pyBaseDemand);

    return r;
}

PyObject* method_EN_setbasedemand(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int nodeIndex, demandIndex;
    double baseDemand;
    if(!PyArg_ParseTuple(args, "Kiid", &ptr, &nodeIndex, &demandIndex, &baseDemand)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_setbasedemand(ph, nodeIndex, demandIndex, baseDemand));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_getdemandpattern(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int nodeIndex, demandIndex;
    if(!PyArg_ParseTuple(args, "Kii", &ptr, &nodeIndex, &demandIndex)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int patIndex;
    PyObject* err = PyLong_FromLong(EN_getdemandpattern(ph, nodeIndex, demandIndex, &patIndex));
    PyObject* pyPatIndex = PyLong_FromLong(patIndex);

    PyObject* r = PyTuple_Pack(2, err, pyPatIndex);
    Py_DECREF(err);
    Py_DECREF(pyPatIndex);

    return r;
}

PyObject* method_EN_setdemandpattern(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int nodeIndex, demandIndex, patIndex;
    if(!PyArg_ParseTuple(args, "Kiii", &ptr, &nodeIndex, &demandIndex, &patIndex)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_setdemandpattern(ph, nodeIndex, demandIndex, patIndex));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_getdemandname(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int nodeIndex, demandIndex;
    if(!PyArg_ParseTuple(args, "Kii", &ptr, &nodeIndex, &demandIndex)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    char out_demandName[MAXID + 1];
    PyObject* err = PyLong_FromLong(EN_getdemandname(ph, nodeIndex, demandIndex, &out_demandName[0]));
    PyObject* pyOutDemandName = PyUnicode_FromString(&out_demandName[0]);

    PyObject* r = PyTuple_Pack(2, err, pyOutDemandName);
    Py_DECREF(err);
    Py_DECREF(pyOutDemandName);

    return r;
}

PyObject* method_EN_setdemandname(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int nodeIndex, demandIndex;
    char* demandName = NULL;
    if(!PyArg_ParseTuple(args, "Kiis", &ptr, &nodeIndex, &demandIndex, &demandName)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_setdemandname(ph, nodeIndex, demandIndex, demandName));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_addlink(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    char* id = NULL;
    int linkType;
    char* fromNode = NULL;
    char* toNode = NULL;
    if(!PyArg_ParseTuple(args, "Ksiss", &ptr, &id, &linkType, &fromNode, &toNode)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int index;
    PyObject* err = PyLong_FromLong(EN_addlink(ph, id, linkType, fromNode, toNode, &index));
    PyObject* pyIndex = PyLong_FromLong(index);

    PyObject* r = PyTuple_Pack(2, err, pyIndex);
    Py_DECREF(err);
    Py_DECREF(pyIndex);

    return r;
}

PyObject* method_EN_deletelink(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index, actionCode;
    if(!PyArg_ParseTuple(args, "Kii", &ptr, &index, &actionCode)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_deletelink(ph, index, actionCode));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_getlinkindex(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    char* id = NULL;
    if(!PyArg_ParseTuple(args, "Ks", &ptr, &id)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int index;
    PyObject* err = PyLong_FromLong(EN_getlinkindex(ph, id, &index));
    PyObject* pyIndex = PyLong_FromLong(index);

    PyObject* r = PyTuple_Pack(2, err, pyIndex);
    Py_DECREF(err);
    Py_DECREF(pyIndex);

    return r;
}

PyObject* method_EN_getlinkid(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index;
    if(!PyArg_ParseTuple(args, "Ki", &ptr, &index)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    char out_id[MAXID + 1];
    PyObject* err = PyLong_FromLong(EN_getlinkid(ph, index, &out_id[0]));
    PyObject* pyOutId = PyUnicode_FromString(&out_id[0]);

    PyObject* r = PyTuple_Pack(2, err, pyOutId);
    Py_DECREF(err);
    Py_DECREF(pyOutId);

    return r;
}

PyObject* method_EN_setlinkid(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index;
    char* newid = NULL;
    if(!PyArg_ParseTuple(args, "Kis", &ptr, &index, &newid)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_setlinkid(ph, index, newid));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_getlinktype(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index;
    if(!PyArg_ParseTuple(args, "Ki", &ptr, &index)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int linkType;
    PyObject* err = PyLong_FromLong(EN_getlinktype(ph, index, &linkType));
    PyObject* pyLinkType = PyLong_FromLong(linkType);

    PyObject* r = PyTuple_Pack(2, err, pyLinkType);
    Py_DECREF(err);
    Py_DECREF(pyLinkType);

    return r;
}

PyObject* method_EN_setlinktype(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int inout_index, linkType, actionCode;
    if(!PyArg_ParseTuple(args, "Kiii", &ptr, &inout_index, &linkType, &actionCode)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_setlinktype(ph, &inout_index, linkType, actionCode));
    PyObject* pyInoutIndex = PyLong_FromLong(inout_index);

    PyObject* r = PyTuple_Pack(2, err, pyInoutIndex);
    Py_DECREF(err);
    Py_DECREF(pyInoutIndex);

    return r;
}

PyObject* method_EN_getlinknodes(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index;
    if(!PyArg_ParseTuple(args, "Ki", &ptr, &index)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int node1, node2;
    PyObject* err = PyLong_FromLong(EN_getlinknodes(ph, index, &node1, &node2));
    PyObject* pyNode1 = PyLong_FromLong(node1);
    PyObject* pyNode2 = PyLong_FromLong(node2);

    PyObject* r = PyTuple_Pack(3, err, pyNode1, pyNode2);
    Py_DECREF(err);
    Py_DECREF(pyNode1);
    Py_DECREF(pyNode2);

    return r;
}

PyObject* method_EN_setlinknodes(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index, node1, node2;
    if(!PyArg_ParseTuple(args, "Kiii", &ptr, &index, &node1, &node2)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_setlinknodes(ph, index, node1, node2));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_getlinkvalue(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index, property;
    if(!PyArg_ParseTuple(args, "Kii", &ptr, &index, &property)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    double value;
    PyObject* err = PyLong_FromLong(EN_getlinkvalue(ph, index, property, &value));
    PyObject* pyValue = PyFloat_FromDouble(value);

    PyObject* r = PyTuple_Pack(2, err, pyValue);
    Py_DECREF(err);
    Py_DECREF(pyValue);

    return r;
}

PyObject* method_EN_setlinkvalue(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index, property;
    double value;
    if(!PyArg_ParseTuple(args, "Kiid", &ptr, &index, &property, &value)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_setlinkvalue(ph, index, property, value));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_setpipedata(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index;
    double length, diam, rough, mloss;
    if(!PyArg_ParseTuple(args, "Kidddd", &ptr, &index, &length, &diam, &rough, &mloss)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_setpipedata(ph, index, length, diam, rough, mloss));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_getvertexcount(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index;
    if(!PyArg_ParseTuple(args, "Ki", &ptr, &index)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int count;
    PyObject* err = PyLong_FromLong(EN_getvertexcount(ph, index, &count));
    PyObject* pyCount = PyLong_FromLong(count);

    PyObject* r = PyTuple_Pack(2, err, pyCount);
    Py_DECREF(err);
    Py_DECREF(pyCount);

    return r;
}

PyObject* method_EN_getvertex(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index, vertex;
    if(!PyArg_ParseTuple(args, "Kii", &ptr, &index, &vertex)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    double x, y;
    PyObject* err = PyLong_FromLong(EN_getvertex(ph, index, vertex, &x, &y));
    PyObject* pyX = PyFloat_FromDouble(x);
    PyObject* pyY = PyFloat_FromDouble(y);

    PyObject* r = PyTuple_Pack(3, err, pyX, pyY);
    Py_DECREF(err);
    Py_DECREF(pyX);
    Py_DECREF(pyY);

    return r;
}

PyObject* method_EN_setvertices(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index;
    double* x = NULL;
    double* y = NULL;
    int count;
    if(!PyArg_ParseTuple(args, "KiOOi", &ptr, &index, &x, &y, &count)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    double* xRaw = (double*) malloc(sizeof(double) * count);
    double* yRaw = (double*) malloc(sizeof(double) * count);

    for(int i=0; i != count; i++) {
        xRaw[i] = PyFloat_AsDouble(PyList_GET_ITEM(x, i));
        yRaw[i] = PyFloat_AsDouble(PyList_GET_ITEM(y, i));
    }

    PyObject* err = PyLong_FromLong(EN_setvertices(ph, index, xRaw, yRaw, count));
    free(xRaw);
    free(yRaw);

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_getpumptype(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int linkIndex;
    if(!PyArg_ParseTuple(args, "Ki", &ptr, &linkIndex)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int pumpType;
    PyObject* err = PyLong_FromLong(EN_getpumptype(ph, linkIndex, &pumpType));
    PyObject* pyPumpType = PyLong_FromLong(pumpType);

    PyObject* r = PyTuple_Pack(2, err, pyPumpType);
    Py_DECREF(err);
    Py_DECREF(pyPumpType);

    return r;
}

PyObject* method_EN_getheadcurveindex(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int linkIndex;
    if(!PyArg_ParseTuple(args, "Ki", &ptr, &linkIndex)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int curveIndex;
    PyObject* err = PyLong_FromLong(EN_getheadcurveindex(ph, linkIndex, &curveIndex));
    PyObject* pyCurveIndex = PyLong_FromLong(curveIndex);

    PyObject* r = PyTuple_Pack(2, err, pyCurveIndex);
    Py_DECREF(err);
    Py_DECREF(pyCurveIndex);

    return r;
}

PyObject* method_EN_setheadcurveindex(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int linkIndex, curveIndex;
    if(!PyArg_ParseTuple(args, "Ki", &ptr, &linkIndex, &curveIndex)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_setheadcurveindex(ph, linkIndex, curveIndex));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_addpattern(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    char* id = NULL;
    if(!PyArg_ParseTuple(args, "Ks", &ptr, &id)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_addpattern(ph, id));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_deletepattern(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index;
    if(!PyArg_ParseTuple(args, "Ki", &ptr, &index)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_deletepattern(ph, index));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_getpatternindex(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    char* id = NULL;
    if(!PyArg_ParseTuple(args, "Ks", &ptr, &id)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int index;
    PyObject* err = PyLong_FromLong(EN_getpatternindex(ph, id, &index));
    PyObject* pyIndex = PyLong_FromLong(index);

    PyObject* r = PyTuple_Pack(2, err, pyIndex);
    Py_DECREF(err);
    Py_DECREF(pyIndex);

    return r;
}

PyObject* method_EN_getpatternid(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index;
    if(!PyArg_ParseTuple(args, "Ki", &ptr, &index)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    char out_id[MAXID + 1];
    PyObject* err = PyLong_FromLong(EN_getpatternid(ph, index, &out_id[0]));
    PyObject* pyOutId = PyUnicode_FromString(&out_id[0]);

    PyObject* r = PyTuple_Pack(2, err, pyOutId);
    Py_DECREF(err);
    Py_DECREF(pyOutId);

    return r;
}

PyObject* method_EN_setpatternid(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index;
    char* id = NULL;
    if(!PyArg_ParseTuple(args, "Kis", &ptr, &index, &id)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_setpatternid(ph, index, id));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_getpatternlen(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index;
    if(!PyArg_ParseTuple(args, "Ki", &ptr, &index)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int len;
    PyObject* err = PyLong_FromLong(EN_getpatternlen(ph, index, &len));
    PyObject* pyLen = PyLong_FromLong(len);

    PyObject* r = PyTuple_Pack(2, err, pyLen);
    Py_DECREF(err);
    Py_DECREF(pyLen);

    return r;
}

PyObject* method_EN_getpatternvalue(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index, period;
    if(!PyArg_ParseTuple(args, "Kii", &ptr, &index, &period)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    double value;
    PyObject* err = PyLong_FromLong(EN_getpatternvalue(ph, index, period, &value));
    PyObject* pyValue = PyFloat_FromDouble(value);

    PyObject* r = PyTuple_Pack(2, err, pyValue);
    Py_DECREF(err);
    Py_DECREF(pyValue);

    return r;
}

PyObject* method_EN_setpatternvalue(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index, period;
    double value;
    if(!PyArg_ParseTuple(args, "Kiid", &ptr, &index, &period, &value)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_setpatternvalue(ph, index, period, value));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_getaveragepatternvalue(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index;
    if(!PyArg_ParseTuple(args, "Ki", &ptr, &index)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    double value;
    PyObject* err = PyLong_FromLong(EN_getaveragepatternvalue(ph, index, &value));
    PyObject* pyValue = PyFloat_FromDouble(value);

    PyObject* r = PyTuple_Pack(2, err, pyValue);
    Py_DECREF(err);
    Py_DECREF(pyValue);

    return r;
}

PyObject* method_EN_setpattern(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index;
    PyObject* values = NULL;
    int len;
    if(!PyArg_ParseTuple(args, "KiOi", &ptr, &index, &values, &len)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int numValues = PyList_Size(values);
    double* valuesRaw = (double*) malloc(sizeof(double) * numValues);
    for(int i=0; i != numValues; i++) {
        valuesRaw[i] = PyFloat_AsDouble(PyList_GET_ITEM(values, i));
    }

    PyObject* err = PyLong_FromLong(EN_setpattern(ph, index, valuesRaw, len));
    free(valuesRaw);

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_addcurve(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    char* id = NULL;
    if(!PyArg_ParseTuple(args, "Ks", &ptr, &id)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_addcurve(ph, id));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_deletecurve(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index;
    if(!PyArg_ParseTuple(args, "Ki", &ptr, &index)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_deletecurve(ph, index));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_getcurveindex(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    char* id = NULL;
    if(!PyArg_ParseTuple(args, "Ks", &ptr, &id)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int index;
    PyObject* err = PyLong_FromLong(EN_getcurveindex(ph, id, &index));
    PyObject* pyIndex = PyLong_FromLong(index);

    PyObject* r = PyTuple_Pack(2, err, pyIndex);
    Py_DECREF(err);
    Py_DECREF(pyIndex);

    return r;
}

PyObject* method_EN_getcurveid(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index;
    if(!PyArg_ParseTuple(args, "Ki", &ptr, &index)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    char out_id[MAXID + 1];
    PyObject* err = PyLong_FromLong(EN_getcurveid(ph, index, &out_id[0]));
    PyObject* pyOutId = PyUnicode_FromString(&out_id[0]);

    PyObject* r = PyTuple_Pack(2, err, pyOutId);
    Py_DECREF(err);
    Py_DECREF(pyOutId);

    return r;
}

PyObject* method_EN_setcurveid(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index;
    char* id = NULL;
    if(!PyArg_ParseTuple(args, "Kis", &ptr, &index, &id)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_setcurveid(ph, index, id));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_getcurvelen(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index;
    if(!PyArg_ParseTuple(args, "Ki", &ptr, &index)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int len;
    PyObject* err = PyLong_FromLong(EN_getcurvelen(ph, index, &len));
    PyObject* pyLen = PyLong_FromLong(len);

    PyObject* r = PyTuple_Pack(2, err, pyLen);
    Py_DECREF(err);
    Py_DECREF(pyLen);

    return r;
}

PyObject* method_EN_getcurvetype(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index;
    if(!PyArg_ParseTuple(args, "Ki", &ptr, &index)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int type;
    PyObject* err = PyLong_FromLong(EN_getcurvetype(ph, index, &type));
    PyObject* pyType = PyLong_FromLong(type);

    PyObject* r = PyTuple_Pack(2, err, pyType);
    Py_DECREF(err);
    Py_DECREF(pyType);

    return r;
}

PyObject* method_EN_getcurvevalue(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int curveIndex, pointIndex;
    if(!PyArg_ParseTuple(args, "Kii", &ptr, &curveIndex, &pointIndex)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    double x, y;
    PyObject* err = PyLong_FromLong(EN_getcurvevalue(ph, curveIndex, pointIndex, &x, &y));
    PyObject* pyX = PyFloat_FromDouble(x);
    PyObject* pyY = PyFloat_FromDouble(y);

    PyObject* r = PyTuple_Pack(3, err, pyX, pyY);
    Py_DECREF(err);
    Py_DECREF(pyX);
    Py_DECREF(pyY);

    return r;
}

PyObject* method_EN_setcurvevalue(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int curveIndex, pointIndex;
    double x, y;
    if(!PyArg_ParseTuple(args, "Kiidd", &ptr, &curveIndex, &pointIndex, &x, &y)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_setcurvevalue(ph, curveIndex, pointIndex, x, y));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_getcurve(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index;
    if(!PyArg_ParseTuple(args, "Ki", &ptr, &index)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int len;
    int errcode = EN_getcurvelen(ph, index, &len);
    if(errcode != 0) {
        PyObject* err = PyLong_FromLong(errcode);
        PyObject* r = PyTuple_Pack(1, err);
        Py_DECREF(err);

        return r;
    }

    char out_id[MAXID + 1];
    int nPoints;
    double* xValues = (double*) PyMem_Calloc(len, sizeof(double));
    double* yValues = (double*) PyMem_Calloc(len, sizeof(double));
    PyObject* err = PyLong_FromLong(EN_getcurve(ph, index, &out_id[0], &nPoints, xValues, yValues));

    PyObject* xValuesList = PyList_New(nPoints);
    PyObject* yValuesList = PyList_New(nPoints);

    for(int i=0; i != nPoints; i++) {
        PyList_SetItem(xValuesList, i, PyFloat_FromDouble(xValues[i]));
        PyList_SetItem(yValuesList, i, PyFloat_FromDouble(yValues[i]));
    }

    PyMem_Free(xValues);
    PyMem_Free(yValues);

    PyObject* r = PyTuple_Pack(3, err, xValuesList, yValuesList);
    Py_DECREF(xValuesList);
    Py_DECREF(yValuesList);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_setcurve(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index, nPoints;
    PyObject* xValues = NULL;
    PyObject* yValues = NULL;
    if(!PyArg_ParseTuple(args, "KiOOi", &ptr, &index, &xValues, &yValues, &nPoints)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    double* xValuesRaw = (double*) malloc(sizeof(double) * nPoints);
    double* yValuesRaw = (double*) malloc(sizeof(double) * nPoints);

    for(int i=0; i != nPoints; i++) {
        xValuesRaw[i] = PyFloat_AsDouble(PyList_GET_ITEM(xValues, i));
        yValuesRaw[i] = PyFloat_AsDouble(PyList_GET_ITEM(yValues, i));
    }

    PyObject* err = PyLong_FromLong(EN_setcurve(ph, index, xValuesRaw, yValuesRaw, nPoints));
    free(xValuesRaw);
    free(yValuesRaw);

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_addcontrol(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int type, linkIndex, nodeIndex;
    double setting, level;
    if(!PyArg_ParseTuple(args, "Kiidid", &ptr, &type, &linkIndex, &setting, &nodeIndex, &level)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int index;
    PyObject* err = PyLong_FromLong(EN_addcontrol(ph, type, linkIndex, setting, nodeIndex, level, &index));
    PyObject* pyIndex = PyLong_FromLong(index);

    PyObject* r = PyTuple_Pack(2, err, pyIndex);
    Py_DECREF(err);
    Py_DECREF(pyIndex);

    return r;
}

PyObject* method_EN_deletecontrol(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index;
    if(!PyArg_ParseTuple(args, "Ki", &ptr, &index)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_deletecontrol(ph, index));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_getcontrol(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index;
    if(!PyArg_ParseTuple(args, "Ki", &ptr, &index)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int type, linkIndex, nodeIndex;
    double setting, level;
    PyObject* err = PyLong_FromLong(EN_getcontrol(ph, index, &type, &linkIndex, &setting, &nodeIndex, &level));
    PyObject* pyType = PyLong_FromLong(type);
    PyObject* pyLinkIndex = PyLong_FromLong(linkIndex);
    PyObject* pySetting = PyFloat_FromDouble(setting);
    PyObject* pyNodeIndex = PyLong_FromLong(nodeIndex);
    PyObject* pyLevel = PyFloat_FromDouble(level);

    PyObject* r = PyTuple_Pack(6, err, pyType, pyLinkIndex, pySetting, pyNodeIndex, pyLevel);
    Py_DECREF(err);
    Py_DECREF(pyType);
    Py_DECREF(pyLinkIndex);
    Py_DECREF(pySetting);
    Py_DECREF(pyNodeIndex);
    Py_DECREF(pyLevel);

    return r;
}

PyObject* method_EN_setcontrol(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index, type, linkIndex, nodeIndex;
    double setting, level;
    if(!PyArg_ParseTuple(args, "Kiiidid", &ptr, &index, &type, &linkIndex, &setting, &nodeIndex, &level)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_setcontrol(ph, index, type, linkIndex, setting, nodeIndex, level));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_addrule(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    char* rule = NULL;
    if(!PyArg_ParseTuple(args, "Ks", &ptr, &rule)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_addrule(ph, rule));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_deleterule(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index;
    if(!PyArg_ParseTuple(args, "Ki", &ptr, &index)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_deleterule(ph, index));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_getrule(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index;
    if(!PyArg_ParseTuple(args, "Ki", &ptr, &index)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int nPremises, nThenActions, nElseActions;
    double priority;
    PyObject* err = PyLong_FromLong(EN_getrule(ph, index, &nPremises, &nThenActions, &nElseActions, &priority));
    PyObject* pyNPremises = PyLong_FromLong(nPremises);
    PyObject* pyNThenActions = PyLong_FromLong(nThenActions);
    PyObject* pyNElseActions = PyLong_FromLong(nElseActions);
    PyObject* pyPriority = PyFloat_FromDouble(priority);

    PyObject* r = PyTuple_Pack(5, err, pyNPremises, pyNThenActions, pyNElseActions, pyPriority);
    Py_DECREF(err);
    Py_DECREF(pyNPremises);
    Py_DECREF(pyNThenActions);
    Py_DECREF(pyNElseActions);
    Py_DECREF(pyPriority);

    return r;
}

PyObject* method_EN_getruleID(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index;
    if(!PyArg_ParseTuple(args, "Ki", &ptr, &index)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    char out_id[MAXID + 1];
    PyObject* err = PyLong_FromLong(EN_getruleID(ph, index, &out_id[0]));
    PyObject* pyOutId = PyUnicode_FromString(&out_id[0]);

    PyObject* r =  PyTuple_Pack(2, err, pyOutId);
    Py_DECREF(err);
    Py_DECREF(pyOutId);

    return r;
}

PyObject* method_EN_getpremise(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int ruleIndex, premiseIndex;
    if(!PyArg_ParseTuple(args, "Kii", &ptr, &ruleIndex, &premiseIndex)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int logop, object, objIndex, variable, relop, status;
    double value;
    PyObject* err = PyLong_FromLong(EN_getpremise(ph, ruleIndex, premiseIndex, &logop, &object, &objIndex, &variable, &relop, &status, &value));
    PyObject* pyLogop = PyLong_FromLong(logop);
    PyObject* pyObject = PyLong_FromLong(object);
    PyObject* pyObjIndex = PyLong_FromLong(objIndex);
    PyObject* pyVariable = PyLong_FromLong(variable);
    PyObject* pyRelop = PyLong_FromLong(relop);
    PyObject* pyStatus = PyLong_FromLong(status);
    PyObject* pyValue = PyFloat_FromDouble(value);

    PyObject* r = PyTuple_Pack(8, err, pyLogop, pyObject, pyObjIndex, pyVariable, pyRelop, pyStatus, pyValue);
    Py_DECREF(err);
    Py_DECREF(pyLogop);
    Py_DECREF(pyObject);
    Py_DECREF(pyObjIndex);
    Py_DECREF(pyVariable);
    Py_DECREF(pyRelop);
    Py_DECREF(pyStatus);
    Py_DECREF(pyValue);

    return r;
}

PyObject* method_EN_setpremise(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int ruleIndex, premiseIndex, logop, object, objIndex, variable, relop, status;
    double value;
    if(!PyArg_ParseTuple(args, "Kiiiiiiiid", &ptr, &ruleIndex, &premiseIndex, &logop, &object, &objIndex, &variable, &relop, &status, &value)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_setpremise(ph, ruleIndex, premiseIndex, logop, object, objIndex, variable, relop, status, value));

    PyObject* r =  PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_setpremiseindex(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int ruleIndex, premiseIndex, objIndex;
    if(!PyArg_ParseTuple(args, "Kiii", &ptr, &ruleIndex, &premiseIndex, &objIndex)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_setpremiseindex(ph, ruleIndex, premiseIndex, objIndex));

    PyObject* r =  PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_setpremisestatus(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int ruleIndex, premiseIndex, status;
    if(!PyArg_ParseTuple(args, "Kiii", &ptr, &ruleIndex, &premiseIndex, &status)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_setpremisestatus(ph, ruleIndex, premiseIndex, status));

    PyObject* r =  PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_setpremisevalue(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int ruleIndex, premiseIndex;
    double value;
    if(!PyArg_ParseTuple(args, "Kii", &ptr, &ruleIndex, &premiseIndex, &value)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_setpremisevalue(ph, ruleIndex, premiseIndex, value));

    PyObject* r =  PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_getthenaction(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int ruleIndex, actionIndex;
    if(!PyArg_ParseTuple(args, "Kii", &ptr, &ruleIndex, &actionIndex)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int linkIndex, status;
    double setting;
    PyObject* err = PyLong_FromLong(EN_getthenaction(ph, ruleIndex, actionIndex, &linkIndex, &status, &setting));
    PyObject* pyLinkIndex = PyLong_FromLong(linkIndex);
    PyObject* pyStatus = PyLong_FromLong(status);
    PyObject* pySetting = PyLong_FromLong(setting);

    PyObject* r = PyTuple_Pack(4, err, pyLinkIndex, pyStatus, pySetting);
    Py_DECREF(err);
    Py_DECREF(pyLinkIndex);
    Py_DECREF(pyStatus);
    Py_DECREF(pySetting);

    return r;
}

PyObject* method_EN_setthenaction(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int ruleIndex, actionIndex, linkIndex, status;
    double setting;
    if(!PyArg_ParseTuple(args, "Kiiiid", &ptr, &ruleIndex, &actionIndex, &linkIndex, &status, &setting)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_setthenaction(ph, ruleIndex, actionIndex, linkIndex, status, setting));

    PyObject* r =  PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_getelseaction(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int ruleIndex, actionIndex;
    if(!PyArg_ParseTuple(args, "Kii", &ptr, &ruleIndex, &actionIndex)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int linkIndex, status;
    double setting;
    PyObject* err = PyLong_FromLong(EN_getelseaction(ph, ruleIndex, actionIndex, &linkIndex, &status, &setting));
    PyObject* pyLinkIndex = PyLong_FromLong(linkIndex);
    PyObject* pyStatus = PyLong_FromLong(status);
    PyObject* pySetting = PyFloat_FromDouble(setting);

    PyObject* r = PyTuple_Pack(4, err, pyLinkIndex, pyStatus, pySetting);
    Py_DECREF(err);
    Py_DECREF(pyLinkIndex);
    Py_DECREF(pyStatus);
    Py_DECREF(pySetting);

    return r;
}

PyObject* method_EN_setelseaction(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int ruleIndex, actionIndex, linkIndex, status;
    double setting;
    if(!PyArg_ParseTuple(args, "Kiiiid", &ptr, &ruleIndex, &actionIndex, &linkIndex, &status, &setting)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_setelseaction(ph, ruleIndex, actionIndex, linkIndex, status, setting));

    PyObject* r =  PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_setrulepriority(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index;
    double priority;
    if(!PyArg_ParseTuple(args, "Kid", &ptr, &index, &priority)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_setrulepriority(ph, index, priority));

    PyObject* r =  PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_gettag(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int object, index;
    if(!PyArg_ParseTuple(args, "Kii", &ptr, &object, &index)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    char tag[MAXID + 1];
    PyObject* err = PyLong_FromLong(EN_gettag(ph, object, index, &tag[0]));
    PyObject* pyTag = PyUnicode_FromString(&tag[0]);

    PyObject* r =  PyTuple_Pack(2, err, pyTag);
    Py_DECREF(err);
    Py_DECREF(pyTag);

    return r;
}

PyObject* method_EN_settag(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int object, index;
    char* tag = NULL;
    if(!PyArg_ParseTuple(args, "Kiis", &ptr, &object, &index, &tag)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_settag(ph, object, index, tag));

    PyObject* r =  PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_timetonextevent(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    if(!PyArg_ParseTuple(args, "K", &ptr)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int eventType, elemIndex;
    long duration;
    PyObject* err = PyLong_FromLong(EN_timetonextevent(ph, &eventType, &duration, &elemIndex));
    PyObject* pyEventType = PyLong_FromLong(eventType);
    PyObject* pyDuration = PyLong_FromLong(duration);
    PyObject* pyElemIndex = PyLong_FromLong(elemIndex);

    PyObject* r = PyTuple_Pack(4, err, pyEventType, pyDuration, pyElemIndex);
    Py_DECREF(err);
    Py_DECREF(pyEventType);
    Py_DECREF(pyDuration);
    Py_DECREF(pyElemIndex);

    return r;
}

PyObject* method_EN_getnodevalues(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int property;
    if(!PyArg_ParseTuple(args, "Ki", &ptr, &property)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int numNodes;
    int errcode = EN_getcount(ph, EN_NODECOUNT, &numNodes);
    if(errcode != 0) {
        PyObject* err = PyLong_FromLong(errcode);
        PyObject* r = PyTuple_Pack(1, err);
        Py_DECREF(err);

        return r;
    }

    double* values = (double*) malloc(sizeof(double) * numNodes);
    PyObject* err = PyLong_FromLong(EN_getnodevalues(ph, property, values));

    PyObject* valuesList = PyList_New(numNodes);
    for(int i=0; i != numNodes; i++) {
        PyList_SET_ITEM(valuesList, i, PyFloat_FromDouble(values[i]));
    }

    free(values);

    PyObject* r = PyTuple_Pack(2, err, valuesList);
    Py_DECREF(valuesList);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_getlinkvalues(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int property;
    if(!PyArg_ParseTuple(args, "Ki", &ptr, &property)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int numLinks;
    int errcode = EN_getcount(ph, EN_LINKCOUNT, &numLinks);
    if(errcode != 0) {
        PyObject* err = PyLong_FromLong(errcode);
        PyObject* r = PyTuple_Pack(1, err);
        Py_DECREF(err);

        return r;
    }

    double* value = (double*) malloc(sizeof(double) * numLinks);
    PyObject* err = PyLong_FromLong(EN_getlinkvalues(ph, property, value));

    PyObject* valuesList = PyList_New(numLinks);
    for(int i=0; i != numLinks; i++) {
        PyList_SET_ITEM(valuesList, i, PyFloat_FromDouble(value[i]));
    }

    free(value);

    PyObject* r = PyTuple_Pack(2, err, valuesList);
    Py_DECREF(valuesList);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_setvertex(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index, vertex;
    double x, y;
    if(!PyArg_ParseTuple(args, "Kiidd", &ptr, &index, &vertex, &x, &y)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_setvertex(ph, index, vertex, x, y));

    PyObject* r =  PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_loadpatternfile(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    char* filename = NULL;
    char* id = NULL;
    if(!PyArg_ParseTuple(args, "Kss", &ptr, &filename, &id)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_loadpatternfile(ph, filename, id));

    PyObject* r =  PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_setcurvetype(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index, type;
    if(!PyArg_ParseTuple(args, "Kii", &ptr, &index, &type)) {
        return NULL;
    }    
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_setcurvetype(ph, index, type));

    PyObject* r =  PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_getcontrolenabled(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index;
    if(!PyArg_ParseTuple(args, "Ki", &ptr, &index)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int out_enabled;
    PyObject* err = PyLong_FromLong(EN_getcontrolenabled(ph, index, &out_enabled));
    PyObject* pyOutEnabled = PyLong_FromLong(out_enabled);

    PyObject* r =  PyTuple_Pack(2, err, pyOutEnabled);
    Py_DECREF(err);
    Py_DECREF(pyOutEnabled);

    return r;
}

PyObject* method_EN_setcontrolenabled(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index, enabled;
    if(!PyArg_ParseTuple(args, "Kii", &ptr, &index, &enabled)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_setcontrolenabled(ph, index, enabled));

    PyObject* r =  PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_EN_getruleenabled(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index;
    if(!PyArg_ParseTuple(args, "Ki", &ptr, &index)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int out_enabled;
    PyObject* err = PyLong_FromLong(EN_getruleenabled(ph, index, &out_enabled));
    PyObject* pyOutEnabled = PyLong_FromLong(out_enabled);

    PyObject* r = PyTuple_Pack(2, err, pyOutEnabled);
    Py_DECREF(err);
    Py_DECREF(pyOutEnabled);

    return r;
}

PyObject* method_EN_setruleenabled(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index, enabled;
    if(!PyArg_ParseTuple(args, "Kii", &ptr, &index, &enabled)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    PyObject* err = PyLong_FromLong(EN_setruleenabled(ph, index, enabled));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}
