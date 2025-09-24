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

    int err = EN_deleteproject(ph);

    return PyTuple_Pack(1, PyLong_FromLong(err));
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

    int err = EN_init(ph, rptFile, outFile, unitsType, headLossType);

    return PyTuple_Pack(1, PyLong_FromLong(err));
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

    int err = EN_open(ph, inpFile, rptFile, outFile);

    return PyTuple_Pack(1, PyLong_FromLong(err));
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
    int err = EN_gettitle(ph, &out_line1[0], &out_line2[0], &out_line3[0]);

    return Py_BuildValue("(isss)", err, out_line1, &out_line2, &out_line3);
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

    int err = EN_settitle(ph, line1, line2, line3);

    return PyTuple_Pack(1, PyLong_FromLong(err));
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
    int err = EN_getcomment(ph, object, index, &out_comment[0]);

    return Py_BuildValue("(is)", err, out_comment);
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

    int err = EN_setcomment(ph, object, index, comment);

    return PyTuple_Pack(1, PyLong_FromLong(err));
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
    int err = EN_getcount(ph, object, &count);

    return Py_BuildValue("(ii)", err, count);
}

PyObject* method_EN_saveinpfile(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    char* filename = NULL;
    if(!PyArg_ParseTuple(args, "Ks", &ptr, &filename)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;  

    int err = EN_saveinpfile(ph, filename);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_EN_close(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    if(!PyArg_ParseTuple(args, "K", &ptr)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int err = EN_close(ph);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_EN_solveH(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    if(!PyArg_ParseTuple(args, "K", &ptr)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int err = EN_solveH(ph);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_EN_usehydfile(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    char* filename = NULL;
    if(!PyArg_ParseTuple(args, "Ks", &ptr, &filename)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int err = EN_usehydfile(ph, filename);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_EN_openH(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    if(!PyArg_ParseTuple(args, "K", &ptr)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int err = EN_openH(ph);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_EN_initH(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int initFlag;
    if(!PyArg_ParseTuple(args, "Ki", &ptr, &initFlag)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int err = EN_initH(ph, initFlag);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_EN_runH(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    if(!PyArg_ParseTuple(args, "K", &ptr)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    long currentTime;
    int err = EN_runH(ph, &currentTime);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(currentTime));
}

PyObject* method_EN_nextH(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    if(!PyArg_ParseTuple(args, "K", &ptr)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    long tStep;
    int err = EN_nextH(ph, &tStep);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(tStep));
}

PyObject* method_EN_saveH(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    if(!PyArg_ParseTuple(args, "K", &ptr)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int err = EN_saveH(ph);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_EN_savehydfile(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    char* filename = NULL;
    if(!PyArg_ParseTuple(args, "Ks", &ptr, &filename)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int err = EN_savehydfile(ph, filename);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_EN_closeH(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    if(!PyArg_ParseTuple(args, "K", &ptr)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int err = EN_closeH(ph);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_EN_solveQ(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    if(!PyArg_ParseTuple(args, "K", &ptr)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int err = EN_solveQ(ph);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_EN_openQ(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    if(!PyArg_ParseTuple(args, "K", &ptr)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int err = EN_openQ(ph);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_EN_initQ(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int saveFlag;
    if(!PyArg_ParseTuple(args, "Ki", &ptr, &saveFlag)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int err = EN_initQ(ph, saveFlag);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_EN_runQ(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    if(!PyArg_ParseTuple(args, "K", &ptr)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    long currentTime;
    int err = EN_runQ(ph, &currentTime);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(currentTime));
}

PyObject* method_EN_nextQ(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    if(!PyArg_ParseTuple(args, "K", &ptr)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    long tStep;
    int err = EN_nextQ(ph, &tStep);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(tStep));
}

PyObject* method_EN_stepQ(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    if(!PyArg_ParseTuple(args, "K", &ptr)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    long timeLeft;
    int err = EN_stepQ(ph, &timeLeft);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(timeLeft));
}

PyObject* method_EN_closeQ(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    if(!PyArg_ParseTuple(args, "K", &ptr)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int err = EN_closeQ(ph);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_EN_writeline(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    char* line = NULL;
    if(!PyArg_ParseTuple(args, "Ks", &ptr, &line)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int err = EN_writeline(ph, line);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_EN_report(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    if(!PyArg_ParseTuple(args, "K", &ptr)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int err = EN_report(ph);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_EN_copyreport(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    char* filename = NULL;
    if(!PyArg_ParseTuple(args, "K", &ptr, &filename)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int err = EN_copyreport(ph, filename);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_EN_clearreport(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    if(!PyArg_ParseTuple(args, "K", &ptr)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int err = EN_clearreport(ph);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_EN_resetreport(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    if(!PyArg_ParseTuple(args, "K", &ptr)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int err = EN_resetreport(ph);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_EN_setreport(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    char* format = NULL;
    if(!PyArg_ParseTuple(args, "Ks", &ptr, &format)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int err = EN_setreport(ph, format);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_EN_setstatusreport(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int level;
    if(!PyArg_ParseTuple(args, "Ki", &ptr, &level)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int err = EN_setstatusreport(ph, level);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_EN_getversion(PyObject* self, PyObject* args)
{
    int version;
    int err = EN_getversion(&version);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(version));
}

PyObject* method_EN_geterror(PyObject* self, PyObject* args)
{
    int errcode;
    if(!PyArg_ParseTuple(args, "i", &errcode)) {
        return NULL;
    }
    
    char out_errmsg[MAXMSG + 1];
    int err = EN_geterror(errcode, &out_errmsg[0], MAXMSG + 1);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyUnicode_FromString(&out_errmsg[0]));
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
    int err = EN_getstatistic(ph, type, &value);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyFloat_FromDouble(value));
}

PyObject* method_EN_getresultindex(PyObject* self, PyObject* args)
{
    int type, index, value;
    uintptr_t ptr;
    if(!PyArg_ParseTuple(args, "Kii", &ptr, &type, &index)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int err = EN_getresultindex(ph, type, index, &value);

    return Py_BuildValue("(ii)", err, value);
    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(value));
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
    int err = EN_getoption(ph, option, &value);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyFloat_FromDouble(value));
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

    int err = EN_setoption(ph, option, value);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_EN_getflowunits(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    if(!PyArg_ParseTuple(args, "K", &ptr)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int units;
    int err = EN_getflowunits(ph, &units);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(units));
}

PyObject* method_EN_setflowunits(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int units;
    if(!PyArg_ParseTuple(args, "Ki", &ptr, &units)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int err = EN_setflowunits(ph, units);

    return PyTuple_Pack(1, PyLong_FromLong(err));
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
    int err = EN_gettimeparam(ph, param, &value);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(value));
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

    int err = EN_settimeparam(ph, param, value);

    return PyTuple_Pack(1, PyLong_FromLong(err));
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
    int err = EN_getqualinfo(ph, &qualType, &out_chemName[0], &out_chemUnits[0], &traceNode);

    return PyTuple_Pack(5, PyLong_FromLong(err), PyLong_FromLong(qualType), PyUnicode_FromString(&out_chemName[0]), PyUnicode_FromString(&out_chemUnits[0]), PyLong_FromLong(traceNode));
}

PyObject* method_EN_getqualtype(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    if(!PyArg_ParseTuple(args, "K", &ptr)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;
    
    int qualType, traceNode;
    int err = EN_getqualtype(ph, &qualType, &traceNode);

    return PyTuple_Pack(3, PyLong_FromLong(err), PyLong_FromLong(qualType), PyLong_FromLong(traceNode));
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

    int err = EN_setqualtype(ph, qualType, chemName, chemUnits, traceNode);

    return PyTuple_Pack(1, PyLong_FromLong(err));
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
    int err = EN_addnode(ph, id, nodeType, &index);

    return Py_BuildValue("(ii)", err, index);
    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(index));
}

PyObject* method_EN_deletenode(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index, actionCode;
    if(!PyArg_ParseTuple(args, "Kii", &ptr, &index, &actionCode)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int err = EN_deletenode(ph, index, actionCode);

    return PyTuple_Pack(1, PyLong_FromLong(err));
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
    int err = EN_getnodeindex(ph, id, &index);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(index));
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
    int err = EN_getnodeid(ph, index, &out_id[0]);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyUnicode_FromString(&out_id[0]));
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

    int err = EN_setnodeid(ph, index, newid);

    return PyTuple_Pack(1, PyLong_FromLong(err));
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
    int err = EN_getnodetype(ph, index, &nodeType);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(nodeType));
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
    int err = EN_getnodevalue(ph, index, property, &value);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyFloat_FromDouble(value));
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

    int err = EN_setnodevalue(ph, index, property, value);

    return PyTuple_Pack(1, PyLong_FromLong(err));
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

    int err = EN_setjuncdata(ph, index, elev, dmnd, dmndpat);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_EN_settankdata(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index;
    double elev, initlvl, minlvl, maxlvl, diam, minvol;
    char* volcurve = NULL;
    if(!PyArg_ParseTuple(args, "Kiddddds", &ptr, &index, &elev, &initlvl, &minlvl, &maxlvl, &diam, &minvol, &volcurve)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int err = EN_settankdata(ph, index, elev, initlvl, minlvl, maxlvl, diam, minvol, volcurve);

    return PyTuple_Pack(1, PyLong_FromLong(err));
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
    int err = EN_getcoord(ph, index, &x, &y);

    return PyTuple_Pack(3, PyLong_FromLong(err), PyFloat_FromDouble(x), PyFloat_FromDouble(y));
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

    int err = EN_setcoord(ph, index, x, y);

    return PyTuple_Pack(1, PyLong_FromLong(err));
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
    int err = EN_getdemandmodel(ph, &type, &pmin, &preq, &pexp);

    return PyTuple_Pack(5, PyLong_FromLong(err), PyLong_FromLong(type), PyFloat_FromDouble(pmin), PyFloat_FromDouble(preq), PyFloat_FromDouble(pexp));
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

    int err = EN_setdemandmodel(ph, type, pmin, preq, pexp);

    return PyTuple_Pack(1, PyLong_FromLong(err));
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

    int err = EN_adddemand(ph, nodeIndex, baseDemand, demandPattern, demandName);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_EN_deletedemand(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int nodeIndex, demandIndex;
    if(!PyArg_ParseTuple(args, "Kii", &ptr, &nodeIndex, &demandIndex)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int err = EN_deletedemand(ph, nodeIndex, demandIndex);

    return PyTuple_Pack(1, PyLong_FromLong(err));
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
    int err = EN_getdemandindex(ph, nodeIndex, demandName, &demandIndex);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(demandIndex));
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
    int err = EN_getnumdemands(ph, nodeIndex, &numDemands);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(numDemands));
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
    int err = EN_getbasedemand(ph, nodeIndex, demandIndex, &baseDemand);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyFloat_FromDouble(baseDemand));
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

    int err = EN_setbasedemand(ph, nodeIndex, demandIndex, baseDemand);

    return PyTuple_Pack(1, PyLong_FromLong(err));
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
    int err = EN_getdemandpattern(ph, nodeIndex, demandIndex, &patIndex);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(patIndex));
}

PyObject* method_EN_setdemandpattern(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int nodeIndex, demandIndex, patIndex;
    if(!PyArg_ParseTuple(args, "Kiii", &ptr, &nodeIndex, &demandIndex, &patIndex)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int err = EN_setdemandpattern(ph, nodeIndex, demandIndex, patIndex);

    return PyTuple_Pack(1, PyLong_FromLong(err));
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
    int err = EN_getdemandname(ph, nodeIndex, demandIndex, &out_demandName[0]);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyUnicode_FromString(&out_demandName[0]));
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

    int err = EN_setdemandname(ph, nodeIndex, demandIndex, demandName);

    return PyTuple_Pack(1, PyLong_FromLong(err));
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
    int err = EN_addlink(ph, id, linkType, fromNode, toNode, &index);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(index));
}

PyObject* method_EN_deletelink(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index, actionCode;
    if(!PyArg_ParseTuple(args, "Kii", &ptr, &index, &actionCode)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int err = EN_deletelink(ph, index, actionCode);

    return PyTuple_Pack(1, PyLong_FromLong(err));
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
    int err = EN_getlinkindex(ph, id, &index);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(index));
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
    int err = EN_getlinkid(ph, index, &out_id[0]);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyUnicode_FromString(&out_id[0]));
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

    int err = EN_setlinkid(ph, index, newid);

    return PyTuple_Pack(1, PyLong_FromLong(err));
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
    int err = EN_getlinktype(ph, index, &linkType);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(linkType));
}

PyObject* method_EN_setlinktype(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int inout_index, linkType, actionCode;
    if(!PyArg_ParseTuple(args, "Kiii", &ptr, &inout_index, &linkType, &actionCode)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int err = EN_setlinktype(ph, &inout_index, linkType, actionCode);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(inout_index));
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
    int err = EN_getlinknodes(ph, index, &node1, &node2);

    return PyTuple_Pack(3, PyLong_FromLong(err), PyLong_FromLong(node1), PyLong_FromLong(node2));
}

PyObject* method_EN_setlinknodes(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index, node1, node2;
    if(!PyArg_ParseTuple(args, "Kiii", &ptr, &index, &node1, &node2)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int err = EN_setlinknodes(ph, index, node1, node2);

    return PyTuple_Pack(1, PyLong_FromLong(err));
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
    int err = EN_getlinkvalue(ph, index, property, &value);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyFloat_FromDouble(value));
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

    int err = EN_setlinkvalue(ph, index, property, value);

    return PyTuple_Pack(1, PyLong_FromLong(err));
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

    int err = EN_setpipedata(ph, index, length, diam, rough, mloss);

    return PyTuple_Pack(1, PyLong_FromLong(err));
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
    int err = EN_getvertexcount(ph, index, &count);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(count));
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
    int err = EN_getvertex(ph, index, vertex, &x, &y);

    return PyTuple_Pack(3, PyLong_FromLong(err), PyFloat_FromDouble(x), PyFloat_FromDouble(y));
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

    int err = EN_setvertices(ph, index, xRaw, yRaw, count);
    free(xRaw);
    free(yRaw);

    return PyTuple_Pack(1, PyLong_FromLong(err));
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
    int err = EN_getpumptype(ph, linkIndex, &pumpType);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(pumpType));
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
    int err = EN_getheadcurveindex(ph, linkIndex, &curveIndex);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(curveIndex));
}

PyObject* method_EN_setheadcurveindex(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int linkIndex, curveIndex;
    if(!PyArg_ParseTuple(args, "Ki", &ptr, &linkIndex, &curveIndex)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int err = EN_setheadcurveindex(ph, linkIndex, curveIndex);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_EN_addpattern(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    char* id = NULL;
    if(!PyArg_ParseTuple(args, "Ks", &ptr, &id)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int err = EN_addpattern(ph, id);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_EN_deletepattern(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index;
    if(!PyArg_ParseTuple(args, "Ki", &ptr, &index)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int err = EN_deletepattern(ph, index);

    return PyTuple_Pack(1, PyLong_FromLong(err));
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
    int err = EN_getpatternindex(ph, id, &index);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(index));
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
    int err = EN_getpatternid(ph, index, &out_id[0]);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyUnicode_FromString(&out_id[0]));
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

    int err = EN_setpatternid(ph, index, id);

    return PyTuple_Pack(1, PyLong_FromLong(err));
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
    int err = EN_getpatternlen(ph, index, &len);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(len));
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
    int err = EN_getpatternvalue(ph, index, period, &value);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyFloat_FromDouble(value));
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

    int err = EN_setpatternvalue(ph, index, period, value);

    return PyTuple_Pack(1, PyLong_FromLong(err));
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
    int err = EN_getaveragepatternvalue(ph, index, &value);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyFloat_FromDouble(value));
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

    int err = EN_setpattern(ph, index, valuesRaw, len);
    free(valuesRaw);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_EN_addcurve(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    char* id = NULL;
    if(!PyArg_ParseTuple(args, "Ks", &ptr, &id)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int err = EN_addcurve(ph, id);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_EN_deletecurve(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index;
    if(!PyArg_ParseTuple(args, "Ki", &ptr, &index)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int err = EN_deletecurve(ph, index);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_EN_getcurveindex(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    char* id = NULL;
    if(!PyArg_ParseTuple(args, "Ki", &ptr, &id)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int index;
    int err = EN_getcurveindex(ph, id, &index);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(index));
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
    int err = EN_getcurveid(ph, index, &out_id[0]);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyUnicode_FromString(&out_id[0]));
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

    int err = EN_setcurveid(ph, index, id);

    return PyTuple_Pack(1, PyLong_FromLong(err));
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
    int err = EN_getcurvelen(ph, index, &len);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(len));
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
    int err = EN_getcurvetype(ph, index, &type);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(type));
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
    int err = EN_getcurvevalue(ph, curveIndex, pointIndex, &x, &y);

    return PyTuple_Pack(3, PyLong_FromLong(err), PyFloat_FromDouble(x), PyFloat_FromDouble(y));
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

    int err = EN_setcurvevalue(ph, curveIndex, pointIndex, x, y);

    return PyTuple_Pack(1, PyLong_FromLong(err));
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
    int err = EN_getcurvelen(ph, index, &len);
    if(err != 0) {
        return PyTuple_Pack(1, PyLong_FromLong(err));
    }

    char out_id[MAXID + 1];
    int nPoints;
    double* xValues = (double*) PyMem_Calloc(len, sizeof(double));
    double* yValues = (double*) PyMem_Calloc(len, sizeof(double));
    err = EN_getcurve(ph, index, &out_id[0], &nPoints, xValues, yValues);

    PyObject* xValuesList = PyList_New(nPoints);
    PyObject* yValuesList = PyList_New(nPoints);

    for(int i=0; i != nPoints; i++) {
        PyList_SetItem(xValuesList, i, PyFloat_FromDouble(xValues[i]));
        PyList_SetItem(yValuesList, i, PyFloat_FromDouble(yValues[i]));
    }

    PyMem_Free(xValues);
    PyMem_Free(yValues);

    return PyTuple_Pack(3, PyLong_FromLong(err), xValuesList, yValuesList);
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

    int err = EN_setcurve(ph, index, xValuesRaw, yValuesRaw, nPoints);
    free(xValuesRaw);
    free(yValuesRaw);

    return PyTuple_Pack(1, PyLong_FromLong(err));
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
    int err = EN_addcontrol(ph, type, linkIndex, setting, nodeIndex, level, &index);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(index));
}

PyObject* method_EN_deletecontrol(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index;
    if(!PyArg_ParseTuple(args, "Ki", &ptr, &index)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int err = EN_deletecontrol(ph, index);

    return PyTuple_Pack(1, PyLong_FromLong(err));
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
    int err = EN_getcontrol(ph, index, &type, &linkIndex, &setting, &nodeIndex, &level);

    return PyTuple_Pack(6, PyLong_FromLong(err), PyLong_FromLong(type), PyLong_FromLong(linkIndex), PyFloat_FromDouble(setting), PyLong_FromLong(nodeIndex), PyFloat_FromDouble(level));
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

    int err = EN_setcontrol(ph, index, type, linkIndex, setting, nodeIndex, level);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_EN_addrule(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    char* rule = NULL;
    if(!PyArg_ParseTuple(args, "Ks", &ptr, &rule)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int err = EN_addrule(ph, rule);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_EN_deleterule(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index;
    if(!PyArg_ParseTuple(args, "Ki", &ptr, &index)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int err = EN_deleterule(ph, index);

    return PyTuple_Pack(1, PyLong_FromLong(err));
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
    int err = EN_getrule(ph, index, &nPremises, &nThenActions, &nElseActions, &priority);

    return PyTuple_Pack(5, PyLong_FromLong(err), PyLong_FromLong(nPremises), PyLong_FromLong(nThenActions), PyLong_FromLong(nElseActions), PyFloat_FromDouble(priority));
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
    int err = EN_getruleID(ph, index, &out_id[0]);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyUnicode_FromString(&out_id[0]));
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
    int err = EN_getpremise(ph, ruleIndex, premiseIndex, &logop, &object, &objIndex, &variable, &relop, &status, &value);

    return PyTuple_Pack(8, PyLong_FromLong(err), PyLong_FromLong(logop), PyLong_FromLong(object), PyLong_FromLong(objIndex), PyLong_FromLong(variable), PyLong_FromLong(relop), PyLong_FromLong(status), PyFloat_FromDouble(value));
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

    int err = EN_setpremise(ph, ruleIndex, premiseIndex, logop, object, objIndex, variable, relop, status, value);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_EN_setpremiseindex(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int ruleIndex, premiseIndex, objIndex;
    if(!PyArg_ParseTuple(args, "Kiii", &ptr, &ruleIndex, &premiseIndex, &objIndex)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int err = EN_setpremiseindex(ph, ruleIndex, premiseIndex, objIndex);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_EN_setpremisestatus(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int ruleIndex, premiseIndex, status;
    if(!PyArg_ParseTuple(args, "Kiii", &ptr, &ruleIndex, &premiseIndex, &status)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int err = EN_setpremisestatus(ph, ruleIndex, premiseIndex, status);

    return PyTuple_Pack(1, PyLong_FromLong(err));
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

    int err = EN_setpremisevalue(ph, ruleIndex, premiseIndex, value);

    return PyTuple_Pack(1, PyLong_FromLong(err));
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
    int err = EN_getthenaction(ph, ruleIndex, actionIndex, &linkIndex, &status, &setting);

    return PyTuple_Pack(4, PyLong_FromLong(err), PyLong_FromLong(linkIndex), PyLong_FromLong(status), PyFloat_FromDouble(setting));
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

    int err = EN_setthenaction(ph, ruleIndex, actionIndex, linkIndex, status, setting);

    return PyTuple_Pack(1, PyLong_FromLong(err));
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
    int err = EN_getelseaction(ph, ruleIndex, actionIndex, &linkIndex, &status, &setting);

    return PyTuple_Pack(4, PyLong_FromLong(err), PyLong_FromLong(linkIndex), PyLong_FromLong(status), PyFloat_FromDouble(setting));
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

    int err = EN_setelseaction(ph, ruleIndex, actionIndex, linkIndex, status, setting);

    return PyTuple_Pack(1, PyLong_FromLong(err));
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

    int err = EN_setrulepriority(ph, index, priority);

    return PyTuple_Pack(1, PyLong_FromLong(err));
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
    int err = EN_gettag(ph, object, index, &tag[0]);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyUnicode_FromString(&tag[0]));
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

    int err = EN_settag(ph, object, index, tag);

    return PyTuple_Pack(1, PyLong_FromLong(err));
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
    int err = EN_timetonextevent(ph, &eventType, &duration, &elemIndex);

    return PyTuple_Pack(4, PyLong_FromLong(err), PyLong_FromLong(eventType), PyLong_FromLong(duration), PyLong_FromLong(elemIndex));
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
    int err = EN_getcount(ph, EN_NODECOUNT, &numNodes);
    if(err != 0) {
        return PyTuple_Pack(1, PyLong_FromLong(err));
    }

    double* values = (double*) malloc(sizeof(double) * numNodes);
    err = EN_getnodevalues(ph, property, values);

    PyObject* valuesList = PyList_New(numNodes);
    for(int i=0; i != numNodes; i++) {
        PyList_SET_ITEM(valuesList, i, PyFloat_FromDouble(values[i]));
    }

    free(values);

    return PyTuple_Pack(2, PyLong_FromLong(err), valuesList);
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
    int err = EN_getcount(ph, EN_LINKCOUNT, &numLinks);
    if(err != 0) {
        return PyTuple_Pack(1, PyLong_FromLong(err));
    }

    double* value = (double*) malloc(sizeof(double) * numLinks);
    err = EN_getlinkvalues(ph, property, value);

    PyObject* valuesList = PyList_New(numLinks);
    for(int i=0; i != numLinks; i++) {
        PyList_SET_ITEM(valuesList, i, PyFloat_FromDouble(value[i]));
    }

    free(value);

    return PyTuple_Pack(2, PyLong_FromLong(err), valuesList);
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

    int err = EN_setvertex(ph, index, vertex, x, y);

    return PyTuple_Pack(1, PyLong_FromLong(err));
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

    int err = EN_loadpatternfile(ph, filename, id);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_EN_setcurvetype(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index, type;
    if(!PyArg_ParseTuple(args, "Kii", &ptr, &index, &type)) {
        return NULL;
    }    
    EN_Project ph = (EN_Project) ptr;

    int err = EN_setcurvetype(ph, index, type);

    return PyTuple_Pack(1, PyLong_FromLong(err));
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
    int err = EN_getcontrolenabled(ph, index, &out_enabled);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(out_enabled));
}

PyObject* method_EN_setcontrolenabled(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index, enabled;
    if(!PyArg_ParseTuple(args, "Kii", &ptr, &index, &enabled)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int err = EN_setcontrolenabled(ph, index, enabled);

    return PyTuple_Pack(1, PyLong_FromLong(err));
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
    int err = EN_getruleenabled(ph, index, &out_enabled);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(out_enabled));
}

PyObject* method_EN_setruleenabled(PyObject* self, PyObject* args)
{
    uintptr_t ptr;
    int index, enabled;
    if(!PyArg_ParseTuple(args, "Kii", &ptr, &index, &enabled)) {
        return NULL;
    }
    EN_Project ph = (EN_Project) ptr;

    int err = EN_setruleenabled(ph, index, enabled);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}