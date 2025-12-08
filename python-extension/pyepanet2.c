#include <Python.h>
#include "epanet2.h"
#include "types.h"


PyObject* method_ENopen(PyObject* self, PyObject* args)
{
    char *inpFile, *rptFile, *outFile = NULL;

    if(!PyArg_ParseTuple(args, "sss", &inpFile, &rptFile, &outFile)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENopen(inpFile, rptFile, outFile));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENopenX(PyObject* self, PyObject* args)
{
    char *inpFile, *rptFile, *outFile = NULL;

    if(!PyArg_ParseTuple(args, "sss", &inpFile, &rptFile, &outFile)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENopenX(inpFile, rptFile, outFile));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENclose(PyObject* self, PyObject* Py_UNUSED(args))
{
    PyObject* err = PyLong_FromLong(ENclose());

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENaddcontrol(PyObject* self, PyObject* args)
{
    int type;
    int linkIndex;
    float setting;
    int nodeIndex;
    float level;
    int index;

    if(!PyArg_ParseTuple(args, "iifif", &type, &linkIndex, &setting, &nodeIndex, &level)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENaddcontrol(type, linkIndex, setting, nodeIndex, level, &index));
    PyObject* pyIndex = PyLong_FromLong(index);

    PyObject* r = PyTuple_Pack(2, err, pyIndex);
    Py_DECREF(err);
    Py_DECREF(pyIndex);

    return r;
}

PyObject* method_ENaddcurve(PyObject* self, PyObject* args)
{
    char* id = NULL;
    if(!PyArg_ParseTuple(args, "s", &id)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENaddcurve(id));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENadddemand(PyObject* self, PyObject* args)
{
    int nodeIndex;
    float baseDemand;
    char* demandPattern = NULL;
    char* demandName = NULL;

    if(!PyArg_ParseTuple(args, "ifss", &nodeIndex, &baseDemand, &demandPattern, &demandName)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENadddemand(nodeIndex, baseDemand, demandPattern, demandName));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENaddlink(PyObject* self, PyObject* args)
{
    char* id = NULL;
    int linkType;
    char* fromNode = NULL;
    char* toNode = NULL;
    int index;

    if(!PyArg_ParseTuple(args, "siss", &id, &linkType, &fromNode, &toNode)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENaddlink(id, linkType, fromNode, toNode, &index));
    PyObject* pyIndex = PyLong_FromLong(index);

    PyObject* r = PyTuple_Pack(2, err, pyIndex);
    Py_DECREF(err);
    Py_DECREF(pyIndex);

    return r;
}

PyObject* method_ENaddnode(PyObject* self, PyObject* args)
{
    char* id = NULL;
    int nodeType;
    int index;

    if(!PyArg_ParseTuple(args, "si", &id, &nodeType)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENaddnode(id, nodeType, &index));
    PyObject* pyIndex = PyLong_FromLong(index);

    PyObject* r = PyTuple_Pack(2, err, pyIndex);
    Py_DECREF(err);
    Py_DECREF(pyIndex);

    return r;
}

PyObject* method_ENaddpattern(PyObject* self, PyObject* args)
{
    char* id = NULL;

    if(!PyArg_ParseTuple(args, "s", &id)) {
        return NULL;
    }
    
    PyObject* err = PyLong_FromLong(ENaddpattern(id));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENaddrule(PyObject* self, PyObject* args)
{
    char* rule = NULL;

    if(!PyArg_ParseTuple(args, "s", &rule)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENaddrule(rule));
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENclearreport(PyObject* self, PyObject* Py_UNUSED(args))
{
    PyObject* err = PyLong_FromLong(ENclearreport());
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENcloseH(PyObject* self, PyObject* Py_UNUSED(args))
{
    PyObject* err = PyLong_FromLong(ENcloseH());

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENcloseQ(PyObject* self, PyObject* Py_UNUSED(args))
{
    PyObject* err = PyLong_FromLong(ENcloseQ());
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENcopyreport(PyObject* self, PyObject* args)
{
    char* filename = NULL;

    if(!PyArg_ParseTuple(args, "s", &filename)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENcopyreport(filename));
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENdeletecontrol(PyObject* self, PyObject* args)
{
    int index;

    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENdeletecontrol(index));
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENdeletecurve(PyObject* self, PyObject* args)
{
    int index;

    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENdeletecurve(index));
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENdeletedemand(PyObject* self, PyObject* args)
{
    int nodeIndex, demandIndex;

    if(!PyArg_ParseTuple(args, "ii", &nodeIndex, &demandIndex)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENdeletedemand(nodeIndex, demandIndex));
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENdeletelink(PyObject* self, PyObject* args)
{
    int index, actionCode;

    if(!PyArg_ParseTuple(args, "ii", &index, &actionCode)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENdeletelink(index, actionCode));
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENdeletenode(PyObject* self, PyObject* args)
{
    int index, actionCode;

    if(!PyArg_ParseTuple(args, "ii", &index, &actionCode)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENdeletenode(index, actionCode));
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENdeletepattern(PyObject* self, PyObject* args)
{
    int index;

    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENdeletepattern(index));
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENdeleterule(PyObject* self, PyObject* args)
{
    int index;

    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENdeleterule(index));
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENgetaveragepatternvalue(PyObject* self, PyObject* args)
{
    int index;
    float value;

    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENgetaveragepatternvalue(index, &value));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENgetbasedemand(PyObject* self, PyObject* args)
{
    int nodeIndex, demandIndex;
    float baseDemand;

    if(!PyArg_ParseTuple(args, "ii", &nodeIndex, &demandIndex)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENgetbasedemand(nodeIndex, demandIndex, &baseDemand));
    PyObject* pyBaseDemand = PyFloat_FromDouble(baseDemand);

    PyObject* r = PyTuple_Pack(2, err, pyBaseDemand);
    Py_DECREF(err);
    Py_DECREF(pyBaseDemand);

    return r;
}

PyObject* method_ENgetcomment(PyObject* self, PyObject* args)
{
    int object, index;
    if(!PyArg_ParseTuple(args, "ii", &object, &index)) {
        return NULL;
    }

    char comment[MAXLINE + 1];
    PyObject* err = PyLong_FromLong(ENgetcomment(object, index, &comment[0]));
    PyObject* pyComment = PyUnicode_FromString(&comment[0]);

    PyObject* r = PyTuple_Pack(2, err, pyComment);
    Py_DECREF(err);
    Py_DECREF(pyComment);

    return r;
}

PyObject* method_ENgetcontrol(PyObject* self, PyObject* args)
{
    int index, type, linkIndex, nodeIndex;
    float setting, level;

    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENgetcontrol(index, &type, &linkIndex, &setting, &nodeIndex, &level));
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

PyObject* method_ENgetcoord(PyObject* self, PyObject* args)
{
    int index;
    double x, y;

    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENgetcoord(index, &x, &y));
    PyObject* pyX = PyFloat_FromDouble(x);
    PyObject* pyY = PyFloat_FromDouble(y);

    PyObject* r = PyTuple_Pack(3, err, pyX, pyY);
    Py_DECREF(err);
    Py_DECREF(pyX);
    Py_DECREF(pyY);

    return r;
}

PyObject* method_ENgetcount(PyObject* self, PyObject* args)
{
    int object, count;

    if(!PyArg_ParseTuple(args, "i", &object)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENgetcount(object, &count));
    PyObject* pyCount = PyLong_FromLong(count);

    PyObject* r = PyTuple_Pack(2, err, pyCount);
    Py_DECREF(err);
    Py_DECREF(pyCount);

    return r;
}

PyObject* method_ENgetcurve(PyObject* self, PyObject* args)
{
    int index;
    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }

    int len;
    int errcode = ENgetcurvelen(index, &len);
    if(errcode != 0) {
        PyObject* err = PyLong_FromLong(errcode);
        PyObject* r = PyTuple_Pack(1, err);
        Py_DECREF(err);

        return r;
    }

    char out_id[MAXID + 1];
    int nPoints;
    float* xValues = (float*) PyMem_Calloc(len, sizeof(float));
    float* yValues = (float*) PyMem_Calloc(len, sizeof(float));
    PyObject* err = PyLong_FromLong(ENgetcurve(index, &out_id[0], &nPoints, xValues, yValues));

    PyObject* xValuesList = PyList_New(nPoints);
    PyObject* yValuesList = PyList_New(nPoints);

    for(int i=0; i != nPoints; i++) {
        PyList_SetItem(xValuesList, i, PyFloat_FromDouble(xValues[i]));
        PyList_SetItem(yValuesList, i, PyFloat_FromDouble(yValues[i]));
    }

    PyMem_Free(xValues);
    PyMem_Free(yValues);

    PyObject* pyOutId = PyUnicode_FromString(&out_id[0]);
    PyObject* pyNPoints = PyLong_FromLong(nPoints);

    PyObject* r = PyTuple_Pack(5, err, pyOutId, pyNPoints, xValuesList, yValuesList);
    Py_DECREF(xValuesList);
    Py_DECREF(yValuesList);
    Py_DECREF(err);
    Py_DECREF(pyOutId);
    Py_DECREF(pyNPoints);

    return r;
}

PyObject* method_ENgetcurveid(PyObject* self, PyObject* args)
{
    int index;

    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }

    char out_id[MAXID + 1];
    PyObject* err = PyLong_FromLong(ENgetcurveid(index, &out_id[0]));
    PyObject* pyId = PyUnicode_FromString(&out_id[0]);

    PyObject* r = PyTuple_Pack(2, err, pyId);
    Py_DECREF(err);
    Py_DECREF(pyId);

    return r;
}

PyObject* method_ENgetcurveindex(PyObject* self, PyObject* args)
{
    char* id = NULL;
    int index;

    if(!PyArg_ParseTuple(args, "s", &id)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENgetcurveindex(id, &index));
    PyObject* pyIndex = PyLong_FromLong(index);

    PyObject* r = PyTuple_Pack(2, err, pyIndex);
    Py_DECREF(err);
    Py_DECREF(pyIndex);

    return r;
}

PyObject* method_ENgetcurvelen(PyObject* self, PyObject* args)
{
    int index, len;

    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    } 

    PyObject* err = PyLong_FromLong(ENgetcurvelen(index, &len));
    PyObject* pyLen = PyLong_FromLong(len);

    PyObject* r = PyTuple_Pack(2, err, pyLen);
    Py_DECREF(err);
    Py_DECREF(pyLen);

    return r;
}

PyObject* method_ENgetcurvetype(PyObject* self, PyObject* args)
{
    int index, type;

    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENgetcurvetype(index, &type));
    PyObject* pyType = PyLong_FromLong(type);

    PyObject* r = PyTuple_Pack(2, err, pyType);
    Py_DECREF(err);
    Py_DECREF(pyType);

    return r;
}

PyObject* method_ENgetcurvevalue(PyObject* self, PyObject* args)
{
    int curveIndex, pointIndex;
    float x, y;

    if(!PyArg_ParseTuple(args, "ii", &curveIndex, &pointIndex)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENgetcurvevalue(curveIndex, pointIndex, &x, &y));
    PyObject* pyX = PyFloat_FromDouble(x);
    PyObject* pyY = PyFloat_FromDouble(y);

    PyObject* r = PyTuple_Pack(3, err, pyX, pyY);
    Py_DECREF(err);
    Py_DECREF(pyX);
    Py_DECREF(pyY);

    return r;
}

PyObject* method_ENgetdemandindex(PyObject* self, PyObject* args)
{
    int nodeIndex, demandIndex;
    char* demandName = NULL;

    if(!PyArg_ParseTuple(args, "is", &nodeIndex, &demandName)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENgetdemandindex(nodeIndex, demandName, &demandIndex));
    PyObject* pyDemandIndex = PyLong_FromLong(demandIndex);

    PyObject* r = PyTuple_Pack(2, err, pyDemandIndex);
    Py_DECREF(err);
    Py_DECREF(pyDemandIndex);

    return r;
}

PyObject* method_ENgetdemandmodel(PyObject* self, PyObject* Py_UNUSED(args))
{
    int model;
    float pmin, preq, pexp;

    PyObject* err = PyLong_FromLong(ENgetdemandmodel(&model, &pmin, &preq, &pexp));
    PyObject* pyModel = PyLong_FromLong(model);
    PyObject* pyPMin = PyFloat_FromDouble(pmin);
    PyObject* pyPReq = PyFloat_FromDouble(preq);
    PyObject* pyPExp = PyFloat_FromDouble(pexp);

    PyObject* r = PyTuple_Pack(5, err, pyModel, pyPMin, pyPReq, pyPExp);
    Py_DECREF(err);
    Py_DECREF(pyModel);
    Py_DECREF(pyPMin);
    Py_DECREF(pyPReq);
    Py_DECREF(pyPExp);

    return r;
}

PyObject* method_ENgetdemandname(PyObject* self, PyObject* args)
{
    int nodeIndex, demandIndex;
    if(!PyArg_ParseTuple(args, "ii", &nodeIndex, &demandIndex)) {
        return NULL;
    } 

    char demandName[MAXID + 1];
    PyObject* err = PyLong_FromLong(ENgetdemandname(nodeIndex, demandIndex, &demandName[0]));
    PyObject* pyDemandName = PyUnicode_FromString(&demandName[0]);

    PyObject* r = PyTuple_Pack(2, err, pyDemandName);
    Py_DECREF(err);
    Py_DECREF(pyDemandName);

    return r;
}

PyObject* method_ENgetdemandpattern(PyObject* self, PyObject* args)
{
    int nodeIndex, demandIndex, patIndex;

    if(!PyArg_ParseTuple(args, "ii", &nodeIndex, &demandIndex)) {
        return NULL;
    } 

    PyObject* err = PyLong_FromLong(ENgetdemandpattern(nodeIndex, demandIndex, &patIndex));
    PyObject* pyPatIndex = PyLong_FromLong(patIndex);

    PyObject* r = PyTuple_Pack(2, err, pyPatIndex);
    Py_DECREF(err);
    Py_DECREF(pyPatIndex);

    return r;
}

PyObject* method_ENgetelseaction(PyObject* self, PyObject* args)
{
    int ruleIndex, actionIndex, linkIndex, status;
    float setting;

    if(!PyArg_ParseTuple(args, "ii", &ruleIndex, &actionIndex)) {
        return NULL;
    }   

    PyObject* err = PyLong_FromLong(ENgetelseaction(ruleIndex, actionIndex, &linkIndex, &status, &setting));
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

PyObject* method_ENgeterror(PyObject* self, PyObject* args)
{
    int errcode;
    char errmsg[MAXMSG + 1];

    if(!PyArg_ParseTuple(args, "i", &errcode)) {
        return NULL;
    }  

    PyObject* err = PyLong_FromLong(ENgeterror(errcode, &errmsg[0], MAXMSG));
    PyObject* pyErrmsg = PyUnicode_FromString(&errmsg[0]);

    PyObject* r = PyTuple_Pack(2, err, pyErrmsg);
    Py_DECREF(err);
    Py_DECREF(pyErrmsg);

    return r;
}

PyObject* method_ENgetflowunits(PyObject* self, PyObject* Py_UNUSED(args))
{
    int units;
    PyObject* err = PyLong_FromLong(ENgetflowunits(&units));
    PyObject* pyUnits = PyLong_FromLong(units);

    PyObject* r = PyTuple_Pack(2, err, pyUnits);
    Py_DECREF(err);
    Py_DECREF(pyUnits);

    return r;
}

PyObject* method_ENgetheadcurveindex(PyObject* self, PyObject* args)
{
    int linkIndex, curveIndex;

    if(!PyArg_ParseTuple(args, "i", &linkIndex)) {
        return NULL;
    } 

    PyObject* err = PyLong_FromLong(ENgetheadcurveindex(linkIndex, &curveIndex));
    PyObject* pyCurveIndex = PyLong_FromLong(curveIndex);

    PyObject* r = PyTuple_Pack(2, err, pyCurveIndex);
    Py_DECREF(err);
    Py_DECREF(pyCurveIndex);

    return r;
}

PyObject* method_ENgetlinkid(PyObject* self, PyObject* args)
{
    int index;
    char id[MAXID + 1];

    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENgetlinkid(index, &id[0]));
    PyObject* pyId = PyUnicode_FromString(&id[0]);

    PyObject* r = PyTuple_Pack(2, err, pyId);
    Py_DECREF(err);
    Py_DECREF(pyId);

    return r;
}

PyObject* method_ENgetlinkindex(PyObject* self, PyObject* args)
{
    int index;
    char* id = NULL;

    if(!PyArg_ParseTuple(args, "s", &id)) {
        return NULL;
    }   

    PyObject* err = PyLong_FromLong(ENgetlinkindex(id, &index));
    PyObject* pyIndex = PyLong_FromLong(index);

    PyObject* r = PyTuple_Pack(2, err, pyIndex);
    Py_DECREF(err);
    Py_DECREF(pyIndex);

    return r;
}

PyObject* method_ENgetlinknodes(PyObject* self, PyObject* args)
{
    int index, node1, node2;

    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENgetlinknodes(index, &node1, &node2));
    PyObject* pyNode1 = PyLong_FromLong(node1);
    PyObject* pyNode2 = PyLong_FromLong(node2);

    PyObject* r = PyTuple_Pack(3, err, pyNode1, pyNode2);
    Py_DECREF(err);
    Py_DECREF(pyNode1);
    Py_DECREF(pyNode2);

    return r;
}

PyObject* method_ENgetlinktype(PyObject* self, PyObject* args)
{
    int index, linkType;

    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENgetlinktype(index, &linkType));
    PyObject* pyLinkType = PyLong_FromLong(linkType);

    PyObject* r = PyTuple_Pack(2, err, pyLinkType);
    Py_DECREF(err);
    Py_DECREF(pyLinkType);

    return r;
}

PyObject* method_ENgetlinkvalue(PyObject* self, PyObject* args)
{
    int index, property;
    float value;

    if(!PyArg_ParseTuple(args, "ii", &index, &property)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENgetlinkvalue(index, property, &value));
    PyObject* pyValue = PyFloat_FromDouble(value);

    PyObject* r = PyTuple_Pack(2, err, pyValue);
    Py_DECREF(err);
    Py_DECREF(pyValue);

    return r;    
}

PyObject* method_ENgetnodeid(PyObject* self, PyObject* args)
{
    int index;
    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }

    char id[MAXID + 1];
    PyObject* err = PyLong_FromLong(ENgetnodeid(index, &id[0]));
    PyObject* pyId = PyUnicode_FromString(&id[0]);

    PyObject* r = PyTuple_Pack(2, err, pyId);
    Py_DECREF(err);
    Py_DECREF(pyId);

    return r;
}

PyObject* method_ENgetnodeindex(PyObject* self, PyObject* args)
{
    char* id = NULL;
    if(!PyArg_ParseTuple(args, "s", &id)) {
        return NULL;
    }

    int index;
    PyObject* err = PyLong_FromLong(ENgetnodeindex(id, &index));
    PyObject* pyIndex = PyLong_FromLong(index);

    PyObject* r = PyTuple_Pack(2, err, PyLong_FromLong(index));
    Py_DECREF(err);
    Py_DECREF(pyIndex);

    return r;
}

PyObject* method_ENgetnodetype(PyObject* self, PyObject* args)
{
    int index, nodeType;

    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENgetnodetype(index, &nodeType));
    PyObject* pyNodeType = PyLong_FromLong(nodeType);

    PyObject* r = PyTuple_Pack(2, err, pyNodeType);
    Py_DECREF(err);
    Py_DECREF(pyNodeType);

    return r;
}

PyObject* method_ENgetnodevalue(PyObject* self, PyObject* args)
{
    int index, property;
    float value;

    if(!PyArg_ParseTuple(args, "ii", &index, &property)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENgetnodevalue(index, property, &value));
    PyObject* pyValue = PyFloat_FromDouble(value);

    PyObject* r = PyTuple_Pack(2, err, pyValue);
    Py_DECREF(err);
    Py_DECREF(pyValue);

    return r;
}

PyObject* method_ENgetnumdemands(PyObject* self, PyObject* args)
{
    int nodeIndex, numDemands;

    if(!PyArg_ParseTuple(args, "i", &nodeIndex)) {
        return NULL;
    }  

    PyObject* err = PyLong_FromLong(ENgetnumdemands(nodeIndex, &numDemands));
    PyObject* pyNumDemands = PyLong_FromLong(numDemands);

    PyObject* r = PyTuple_Pack(2, err, pyNumDemands);
    Py_DECREF(err);
    Py_DECREF(pyNumDemands);

    return r;
}

PyObject* method_ENgetoption(PyObject* self, PyObject* args)
{
    int option;
    float value;

    if(!PyArg_ParseTuple(args, "i", &option)) {
        return NULL;
    }  

    PyObject* err = PyLong_FromLong(ENgetoption(option, &value));
    PyObject* pyValue = PyLong_FromDouble(value);

    PyObject* r = PyTuple_Pack(2, err, pyValue);
    Py_DECREF(err);
    Py_DECREF(pyValue);

    return r;
}

PyObject* method_ENgetpatternid(PyObject* self, PyObject* args)
{
    int index;
    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    } 

    char id[MAXID + 1];
    PyObject* err = PyLong_FromLong(ENgetpatternid(index, &id[0]));
    PyObject* pyId = PyUnicode_FromString(&id[0]);

    PyObject* r = PyTuple_Pack(2, err, pyId);
    Py_DECREF(err);
    Py_DECREF(pyId);

    return r;
}

PyObject* method_ENgetpatternindex(PyObject* self, PyObject* args)
{
    char *id = NULL;
    if(!PyArg_ParseTuple(args, "s", &id)) {
        return NULL;
    } 

    int index;
    PyObject* err = PyLong_FromLong(ENgetpatternindex(id, &index));
    PyObject* pyIndex = PyLong_FromLong(index);

    PyObject* r = PyTuple_Pack(2, err, pyIndex);
    Py_DECREF(err);
    Py_DECREF(pyIndex);

    return r;
}

PyObject* method_ENgetpatternlen(PyObject* self, PyObject* args)
{
    int index, len;

    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }    

    PyObject* err = PyLong_FromLong(ENgetpatternlen(index, &len));
    PyObject* pyLen = PyLong_FromLong(len);

    PyObject* r = PyTuple_Pack(2, err, pyLen);
    Py_DECREF(err);
    Py_DECREF(pyLen);

    return r;
}

PyObject* method_ENgetpatternvalue(PyObject* self, PyObject* args)
{
    int index, period;
    float value;

    if(!PyArg_ParseTuple(args, "ii", &index, &period)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENgetpatternvalue(index, period, &value));
    PyObject* pyValue = PyFloat_FromDouble(value);

    PyObject* r = PyTuple_Pack(2, err, pyValue);
    Py_DECREF(err);
    Py_DECREF(pyValue);

    return r;
}

PyObject* method_ENgetpremise(PyObject* self, PyObject* args)
{
    int ruleIndex, premiseIndex, logop, object, objIndex, variable, relop, status;
    float value;

    if(!PyArg_ParseTuple(args, "ii", &ruleIndex, &premiseIndex)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENgetpremise(ruleIndex, premiseIndex, &logop, &object, &objIndex, &variable, &relop, &status, &value));
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

PyObject* method_ENgetpumptype(PyObject* self, PyObject* args)
{
    int linkIndex, pumpType;

    if(!PyArg_ParseTuple(args, "i", &linkIndex)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENgetpumptype(linkIndex, &pumpType));
    PyObject* pyPumpType = PyLong_FromLong(pumpType);

    PyObject* r = PyTuple_Pack(2, err, pyPumpType);
    Py_DECREF(err);
    Py_DECREF(pyPumpType);

    return r;
}

PyObject* method_ENgetqualinfo(PyObject* self, PyObject* Py_UNUSED(args))
{
    int qualType, traceNode;
    char chemName[MAXID + 1];
    char chemUnits[MAXID + 1];

    PyObject* err = PyLong_FromLong(ENgetqualinfo(&qualType, &chemName[0], &chemUnits[0], &traceNode));
    PyObject* pyQualType = PyLong_FromLong(qualType);
    PyObject* pyChemName = PyUnicode_FromString(&chemName[0]);
    PyObject* pyChemUnits = PyUnicode_FromString(&chemUnits[0]);
    PyObject* pyTraceNode = PyLong_FromLong(traceNode);

    PyObject* r = PyTuple_Pack(5, err, pyQualType, pyChemName, pyChemUnits, pyTraceNode);
    Py_DECREF(err);
    Py_DECREF(pyQualType);
    Py_DECREF(pyChemName);
    Py_DECREF(pyChemUnits);
    Py_DECREF(pyTraceNode);

    return r;
}

PyObject* method_ENgetqualtype(PyObject* self, PyObject* Py_UNUSED(args))
{
    int qualType, traceNode;

    PyObject* err = PyLong_FromLong(ENgetqualtype(&qualType, &traceNode));
    PyObject* pyQualType = PyLong_FromLong(qualType);
    PyObject* pyTraceNode = PyLong_FromLong(traceNode);

    PyObject* r = PyTuple_Pack(3, err, pyQualType, pyTraceNode);
    Py_DECREF(err);
    Py_DECREF(pyQualType);
    Py_DECREF(pyTraceNode);

    return r;
}

PyObject* method_ENgetresultindex(PyObject* self, PyObject* args)
{
    int type, index, value;

    if(!PyArg_ParseTuple(args, "ii", &type, &index)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENgetresultindex(type, index, &value));
    PyObject* pyValue = PyLong_FromLong(value);

    PyObject* r = PyTuple_Pack(2, err, pyValue);
    Py_DECREF(err);
    Py_DECREF(pyValue);

    return r;
}

PyObject* method_ENgetrule(PyObject* self, PyObject* args)
{
    int index, nPremises, nThenActions, nElseActions;
    float priority;

    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }  

    PyObject* err = PyLong_FromLong(ENgetrule(index, &nPremises, &nThenActions, &nElseActions, &priority));
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

PyObject* method_ENgetruleID(PyObject* self, PyObject* args)
{
    int index;
    char id[MAXID + 1];

    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENgetruleID(index, &id[0]));
    PyObject* pyId = PyUnicode_FromString(&id[0]);

    PyObject* r = PyTuple_Pack(2, err, pyId);
    Py_DECREF(err);
    Py_DECREF(pyId);

    return r;
}

PyObject* method_ENgetstatistic(PyObject* self, PyObject* args)
{
    int type;
    float value;

    if(!PyArg_ParseTuple(args, "i", &type)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENgetstatistic(type, &value));
    PyObject* pyValue = PyFloat_FromDouble(value);

    PyObject* r = PyTuple_Pack(2, err, pyValue);
    Py_DECREF(err);
    Py_DECREF(pyValue);

    return r;
}

PyObject* method_ENgetthenaction(PyObject* self, PyObject* args)
{
    int ruleIndex, actionIndex, linkIndex, status;
    float setting;

    if(!PyArg_ParseTuple(args, "ii", &ruleIndex, &actionIndex)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENgetthenaction(ruleIndex, actionIndex, &linkIndex, &status, &setting));
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

PyObject* method_ENgettimeparam(PyObject* self, PyObject* args)
{
    int param;
    long value;

    if(!PyArg_ParseTuple(args, "i", &param)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENgettimeparam(param, &value));
    PyObject* pyValue = PyLong_FromLong(value);

    PyObject* r = PyTuple_Pack(2, err, pyValue);
    Py_DECREF(err);
    Py_DECREF(pyValue);

    return r;
}

PyObject* method_ENgettitle(PyObject* self, PyObject* Py_UNUSED(args))
{
    char line1[TITLELEN + 1];
    char line2[TITLELEN + 1];
    char line3[TITLELEN + 1];

    PyObject* err = PyLong_FromLong(ENgettitle(&line1[0], &line2[0], &line3[0]));
    PyObject* pyLine1 = PyUnicode_FromString(&line1[0]);
    PyObject* pyLine2 = PyUnicode_FromString(&line2[0]);
    PyObject* pyLine3 = PyUnicode_FromString(&line3[0]);

    PyObject* r = PyTuple_Pack(4, err, pyLine1, pyLine2, pyLine3);
    Py_DECREF(err);
    Py_DECREF(pyLine1);
    Py_DECREF(pyLine2);
    Py_DECREF(pyLine3);

    return r;
}

PyObject* method_ENgetversion(PyObject* self, PyObject* Py_UNUSED(args))
{
    int version;
    PyObject* err = PyLong_FromLong(ENgetversion(&version));
    PyObject* pyVersion = PyLong_FromLong(version);

    PyObject* r = PyTuple_Pack(2, err, pyVersion);
    Py_DECREF(err);
    Py_DECREF(pyVersion);

    return r;
}

PyObject* method_ENgetvertex(PyObject* self, PyObject* args)
{
    int index, vertex;
    double x, y;

    if(!PyArg_ParseTuple(args, "ii", &index, &vertex)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENgetvertex(index, vertex, &x, &y));
    PyObject* pyX = PyFloat_FromDouble(x);
    PyObject* pyY = PyFloat_FromDouble(y);
    
    PyObject* r = PyTuple_Pack(3, err, pyX, pyY);
    Py_DECREF(err);
    Py_DECREF(pyX);
    Py_DECREF(pyY);

    return r;
}

PyObject* method_ENgetvertexcount(PyObject* self, PyObject* args)
{
    int index, count;

    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENgetvertexcount(index, &count));
    PyObject* pyCount = PyLong_FromLong(count);

    PyObject* r = PyTuple_Pack(2, err, pyCount);
    Py_DECREF(err);
    Py_DECREF(pyCount);

    return r;
}

PyObject* method_ENinit(PyObject* self, PyObject* args)
{
    char* rptFile, *outFile = NULL;
    int unitsType, headlossType;

    if(!PyArg_ParseTuple(args, "ssii", &rptFile, &outFile, &unitsType, &headlossType)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENinit(rptFile, outFile, unitsType, headlossType));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENinitH(PyObject* self, PyObject* args)
{
    int initFlag;
    if(!PyArg_ParseTuple(args, "i", &initFlag)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENinitH(initFlag));
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENinitQ(PyObject* self, PyObject* args)
{
    int saveFlag;
    if(!PyArg_ParseTuple(args, "i", &saveFlag)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENinitQ(saveFlag));
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENnextH(PyObject* self, PyObject* Py_UNUSED(args))
{
    long lStep;
    PyObject* err = PyLong_FromLong(ENnextH(&lStep));
    PyObject* pyLStep = PyLong_FromLong(lStep);

    PyObject* r = PyTuple_Pack(2, err, pyLStep);
    Py_DECREF(err);
    Py_DECREF(pyLStep);

    return r;
}

PyObject* method_ENnextQ(PyObject* self, PyObject* Py_UNUSED(args))
{
    long tStep;
    PyObject* err = PyLong_FromLong(ENnextQ(&tStep));
    PyObject* pyTStep = PyLong_FromLong(tStep);

    PyObject* r = PyTuple_Pack(2, err, pyTStep);
    Py_DECREF(err);
    Py_DECREF(pyTStep);

    return r;
}

PyObject* method_ENopenH(PyObject* self, PyObject* Py_UNUSED(args))
{
    PyObject* err = PyLong_FromLong(ENopenH());
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENopenQ(PyObject* self, PyObject* Py_UNUSED(args))
{
    PyObject* err = PyLong_FromLong(ENopenQ());

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENreport(PyObject* self, PyObject* Py_UNUSED(args))
{
    PyObject* err = PyLong_FromLong(ENreport());

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENresetreport(PyObject* self, PyObject* Py_UNUSED(args))
{
    PyObject* err = PyLong_FromLong(ENresetreport());

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENrunH(PyObject* self, PyObject* Py_UNUSED(args))
{
    long currentTime;
    PyObject* err = PyLong_FromLong(ENrunH(&currentTime));
    PyObject* pyCurrentTime = PyLong_FromLong(currentTime);

    PyObject* r = PyTuple_Pack(2, err, pyCurrentTime);
    Py_DECREF(err);
    Py_DECREF(pyCurrentTime);

    return r;
}

PyObject* method_ENrunQ(PyObject* self, PyObject* Py_UNUSED(args))
{
    long currentTime;
    PyObject* err = PyLong_FromLong(ENrunQ(&currentTime));
    PyObject* pyCurrentTime = PyLong_FromLong(currentTime);

    PyObject* r = PyTuple_Pack(2, err, pyCurrentTime);
    Py_DECREF(err);
    Py_DECREF(pyCurrentTime);

    return r;
}

PyObject* method_ENsavehydfile(PyObject* self, PyObject* args)
{
    char* filename = NULL;

    if(!PyArg_ParseTuple(args, "s", &filename)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENsavehydfile(filename));
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENsaveH(PyObject* self, PyObject* Py_UNUSED(args))
{
    PyObject* err = PyLong_FromLong(ENsaveH());

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENsaveinpfile(PyObject* self, PyObject* args)
{
    char* filename = NULL;

    if(!PyArg_ParseTuple(args, "s", &filename)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENsaveinpfile(filename));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENsetbasedemand(PyObject* self, PyObject* args)
{
    int nodeIndex, demandIndex;
    float baseDemand;

    if(!PyArg_ParseTuple(args, "iif", &nodeIndex, &demandIndex, &baseDemand)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENsetbasedemand(nodeIndex, demandIndex, baseDemand));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENsetcomment(PyObject* self, PyObject* args)
{
    int object, index;
    char* comment = NULL;

    if(!PyArg_ParseTuple(args, "iis", &object, &index, &comment)) {
        return NULL;
    }   

    PyObject* err = PyLong_FromLong(ENsetcomment(object, index, comment));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENsetcontrol(PyObject* self, PyObject* args)
{
    int index, type, linkIndex, nodeIndex;
    float setting, level;

    if(!PyArg_ParseTuple(args, "iiifif", &index, &type, &linkIndex, &setting, &nodeIndex, &level)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENsetcontrol(index, type, linkIndex, setting, nodeIndex, level));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENsetcurveid(PyObject* self, PyObject* args)
{
    int index;
    char* id = NULL;

    if(!PyArg_ParseTuple(args, "is", &index, &id)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENsetcurveid(index, id));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENsetcurve(PyObject* self, PyObject* args)
{
    int index, nPoints;
    PyObject* xValues = NULL;
    PyObject* yValues = NULL;
    if(!PyArg_ParseTuple(args, "iOOi", &index, &xValues, &yValues, &nPoints)) {
        return NULL;
    }

    float* xValuesRaw = (float*) malloc(sizeof(float) * nPoints);
    float* yValuesRaw = (float*) malloc(sizeof(float) * nPoints);

    for(int i=0; i != nPoints; i++) {
        xValuesRaw[i] = (float) PyFloat_AsDouble(PyList_GET_ITEM(xValues, i));
        yValuesRaw[i] = (float) PyFloat_AsDouble(PyList_GET_ITEM(yValues, i));
    }

    PyObject* err = PyLong_FromLong(ENsetcurve(index, xValuesRaw, yValuesRaw, nPoints));
    free(xValuesRaw);
    free(yValuesRaw);

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENsetcoord(PyObject* self, PyObject* args)
{
    int index;
    double x, y;

    if(!PyArg_ParseTuple(args, "idd", &index, &x, &y)) {
        return NULL;
    }    

    PyObject* err = PyLong_FromLong(ENsetcoord(index, x, y));
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENsetcurvevalue(PyObject* self, PyObject* args)
{
    int curveIndex, pointIndex;
    float x, y;

    if(!PyArg_ParseTuple(args, "iiff", &curveIndex, &pointIndex, &x, &y)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENsetcurvevalue(curveIndex, pointIndex, x, y));
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENsetdemandmodel(PyObject* self, PyObject* args)
{
    int model;
    float pmin, preq, pexp;

    if(!PyArg_ParseTuple(args, "ifff", &model, &pmin, &preq, &pexp)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENsetdemandmodel(model, pmin, preq, pexp));
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENsetdemandname(PyObject* self, PyObject* args)
{
    int nodeIndex, demandIndex;
    char* demandName = NULL;

    if(!PyArg_ParseTuple(args, "iis", &nodeIndex, &demandIndex, &demandName)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENsetdemandname(nodeIndex, demandIndex, demandName));
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENsetdemandpattern(PyObject* self, PyObject* args)
{
    int nodeIndex, demandIndex, patIndex;

    if(!PyArg_ParseTuple(args, "iii", &nodeIndex, &demandIndex, &patIndex)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENsetdemandpattern(nodeIndex, demandIndex, patIndex));
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENsetelseaction(PyObject* self, PyObject* args)
{
    int ruleIndex, actionIndex, linkIndex, status;
    float setting;

    if(!PyArg_ParseTuple(args, "iiiif", &ruleIndex, &actionIndex, &linkIndex, &status, &setting)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENsetelseaction(ruleIndex, actionIndex, linkIndex, status, setting));
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENsetflowunits(PyObject* self, PyObject* args)
{
    int units;

    if(!PyArg_ParseTuple(args, "i", &units)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENsetflowunits(units));
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENsetheadcurveindex(PyObject* self, PyObject* args)
{
    int linkIndex, curveIndex;

    if(!PyArg_ParseTuple(args, "ii", &linkIndex, &curveIndex)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENsetheadcurveindex(linkIndex, curveIndex));
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENsetjuncdata(PyObject* self, PyObject* args)
{
    int index;
    float elev, dmnd;
    char* dmndpat = NULL;

    if(!PyArg_ParseTuple(args, "iffs", &index, &elev, &dmnd, &dmndpat)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENsetjuncdata(index, elev, dmnd, dmndpat));
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENsetlinkid(PyObject* self, PyObject* args)
{
    int index;
    char* newid = NULL;

    if(!PyArg_ParseTuple(args, "is", &index, &newid)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENsetlinkid(index, newid));
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENsetlinknodes(PyObject* self, PyObject* args)
{
    int index, node1, node2;

    if(!PyArg_ParseTuple(args, "iii", &index, &node1, &node2)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENsetlinknodes(index, node1, node2));
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENsetlinktype(PyObject* self, PyObject* args)
{
    int index;
    int linkType, actionCode;

    if(!PyArg_ParseTuple(args, "iii", &index, &linkType, &actionCode)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENsetlinktype(&index, linkType, actionCode));
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENsetlinkvalue(PyObject* self, PyObject* args)
{
    int index, property;
    float value;

    if(!PyArg_ParseTuple(args, "iif", &index, &property, &value)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENsetlinkvalue(index, property, value));
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENsetnodeid(PyObject* self, PyObject* args)
{
    int index;
    char* newid = NULL;

    if(!PyArg_ParseTuple(args, "is", &index, &newid)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENsetnodeid(index, newid));
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENsetnodevalue(PyObject* self, PyObject* args)
{
    int index, property;
    float value;

    if(!PyArg_ParseTuple(args, "iif", &index, &property, &value)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENsetnodevalue(index, property, value));
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENsetoption(PyObject* self, PyObject* args)
{
    int option;
    float value;

    if(!PyArg_ParseTuple(args, "if", &option, &value)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENsetoption(option, value));
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENsetpattern(PyObject* self, PyObject* args)
{
    int index;
    PyObject* values = NULL;
    int len;
    if(!PyArg_ParseTuple(args, "iOi", &index, &values, &len)) {
        return NULL;
    }

    int numValues = PyList_Size(values);
    float* valuesRaw = (float*) malloc(sizeof(float) * numValues);
    for(int i=0; i != numValues; i++) {
        valuesRaw[i] = (float) PyFloat_AsDouble(PyList_GET_ITEM(values, i));
    }

    PyObject* err = PyLong_FromLong(ENsetpattern(index, valuesRaw, len));
    free(valuesRaw);

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENsetpatternid(PyObject* self, PyObject* args)
{
    int index;
    char* id = NULL;

    if(!PyArg_ParseTuple(args, "is", &index, &id)) {
        return NULL;
    }   

    PyObject* err = PyLong_FromLong(ENsetpatternid(index, id));
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENsetpatternvalue(PyObject* self, PyObject* args)
{
    int index, period;
    float value;

    if(!PyArg_ParseTuple(args, "iif", &index, &period, &value)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENsetpatternvalue(index, period, value));
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENsetpipedata(PyObject* self, PyObject* args)
{
    int index;
    float length, diam, rough, mloss;

    if(!PyArg_ParseTuple(args, "iffff", &index, &length, &diam, &rough, &mloss)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENsetpipedata(index, length, diam, rough, mloss));
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENsetpremise(PyObject* self, PyObject* args)
{
    int ruleIndex, premiseIndex, logop, object, objIndex, variable, relop, status;
    float value;

    if(!PyArg_ParseTuple(args, "iiiiiiiif", &ruleIndex, &premiseIndex, &logop, &object, &objIndex, &variable, &relop, &status, &value)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENsetpremise(ruleIndex, premiseIndex, logop, object, objIndex, variable, relop, status, value));
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENsetpremiseindex(PyObject* self, PyObject* args)
{
    int ruleIndex, premiseIndex, objIndex;

    if(!PyArg_ParseTuple(args, "iii", &ruleIndex, &premiseIndex, &objIndex)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENsetpremiseindex(ruleIndex, premiseIndex, objIndex));
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENsetpremisevalue(PyObject* self, PyObject* args)
{
    int ruleIndex, premiseIndex;
    float value;

    if(!PyArg_ParseTuple(args, "iif", &ruleIndex, &premiseIndex, &value)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENsetpremisevalue(ruleIndex, premiseIndex, value));
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENsetpremisestatus(PyObject* self, PyObject* args)
{
    int ruleIndex, premiseIndex, status;
    if(!PyArg_ParseTuple(args, "iii", &ruleIndex, &premiseIndex, &status)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENsetpremisestatus(ruleIndex, premiseIndex, status));
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENsetqualtype(PyObject* self, PyObject* args)
{
    int qualtype;
    char* chemName = NULL;
    char* chemUnits = NULL;
    char* traceNode = NULL;

    if(!PyArg_ParseTuple(args, "isss", &qualtype, &chemName, &chemUnits, &traceNode)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENsetqualtype(qualtype, chemName, chemUnits, traceNode));
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENsetreport(PyObject* self, PyObject* args)
{
    char* format = NULL;

    if(!PyArg_ParseTuple(args, "s", &format)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENsetreport(format));
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENsetrulepriority(PyObject* self, PyObject* args)
{
    int index;
    float priority;

    if(!PyArg_ParseTuple(args, "if", &index, &priority)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENsetrulepriority(index, priority));
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENsetstatusreport(PyObject* self, PyObject* args)
{
    int level;

    if(!PyArg_ParseTuple(args, "i", &level)) {
        return NULL;
    } 

    PyObject* err = PyLong_FromLong(ENsetstatusreport(level));
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENsettankdata(PyObject* self, PyObject* args)
{
    int index;
    float elev, initlvl, minlvl, maxlvl, diam, minvol;
    char* volcurve = NULL;

    if(!PyArg_ParseTuple(args, "iffffffs", &index, &elev, &initlvl, &minlvl, &maxlvl, &diam, &minvol, &volcurve)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENsettankdata(index, elev, initlvl, minlvl, maxlvl, diam, minvol, volcurve));
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENsetthenaction(PyObject* self, PyObject* args)
{
    int ruleIndex, actionIndex, linkIndex, status;
    float setting;

    if(!PyArg_ParseTuple(args, "iiiif", &ruleIndex, &actionIndex, &linkIndex, &status, &setting)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENsetthenaction(ruleIndex, actionIndex, linkIndex, status, setting));
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENsettimeparam(PyObject* self, PyObject* args)
{
    int param;
    long value;

    if(!PyArg_ParseTuple(args, "il", &param, &value)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENsettimeparam(param, value));
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENsettitle(PyObject* self, PyObject* args)
{
    char* line1 = NULL;
    char* line2 = NULL;
    char* line3 = NULL;

    if(!PyArg_ParseTuple(args, "sss", &line1, &line2, &line3)) {
        return NULL;
    }   

    PyObject* err = PyLong_FromLong(ENsettitle(line1, line2, line3));
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENsetvertices(PyObject* self, PyObject* args)
{
    int index;
    double* x = NULL;
    double* y = NULL;
    int count;
    if(!PyArg_ParseTuple(args, "iOOi", &index, &x, &y, &count)) {
        return NULL;
    }

    double* xRaw = (double*) malloc(sizeof(double) * count);
    double* yRaw = (double*) malloc(sizeof(double) * count);

    for(int i=0; i != count; i++) {
        xRaw[i] = PyFloat_AsDouble(PyList_GET_ITEM(x, i));
        yRaw[i] = PyFloat_AsDouble(PyList_GET_ITEM(y, i));
    }

    PyObject* err = PyLong_FromLong(ENsetvertices(index, xRaw, yRaw, count));
    free(xRaw);
    free(yRaw);

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENsolveH(PyObject* self, PyObject* Py_UNUSED(args))
{
    PyObject* err = PyLong_FromLong(ENsolveH());
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENsolveQ(PyObject* self, PyObject* Py_UNUSED(args))
{
    PyObject* err = PyLong_FromLong(ENsolveQ());
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENstepQ(PyObject* self, PyObject* Py_UNUSED(args))
{
    long timeLeft;
    PyObject* err = PyLong_FromLong(ENstepQ(&timeLeft));
    PyObject* pyTimeLeft = PyLong_FromLong(timeLeft);

    PyObject* r = PyTuple_Pack(2, err, pyTimeLeft);
    Py_DECREF(err);
    Py_DECREF(pyTimeLeft);

    return r;
}

PyObject* method_ENusehydfile(PyObject* self, PyObject* args)
{
    char* filename = NULL;
    if(!PyArg_ParseTuple(args, "s", &filename)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENusehydfile(filename));
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENwriteline(PyObject* self, PyObject* args)
{
    char* line = NULL;
    if(!PyArg_ParseTuple(args, "s", &line)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENwriteline(line));
    
    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENgettag(PyObject* self, PyObject* args)
{
    int object, index;
    if(!PyArg_ParseTuple(args, "ii", &object, &index)) {
        return NULL;
    }

    char tag[MAXID + 1];
    PyObject* err = PyLong_FromLong(ENgettag(object, index, &tag[0]));
    PyObject* pyTag = PyUnicode_FromString(&tag[0]);

    PyObject* r = PyTuple_Pack(2, err, pyTag);
    Py_DECREF(err);
    Py_DECREF(pyTag);

    return r;
}

PyObject* method_ENsettag(PyObject* self, PyObject* args)
{
    int object, index;
    char* tag = NULL;
    if(!PyArg_ParseTuple(args, "iis", &object, &index, &tag)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENsettag(object, index, tag));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENtimetonextevent(PyObject* self, PyObject* Py_UNUSED(args))
{
    int eventType, elemIndex;
    long duration;
    PyObject* err = PyLong_FromLong(ENtimetonextevent(&eventType, &duration, &elemIndex));
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

PyObject* method_ENgetnodevalues(PyObject* self, PyObject* args)
{
    int property;
    if(!PyArg_ParseTuple(args, "i", &property)) {
        return NULL;
    }

    int numNodes;
    int errcode = ENgetcount(EN_NODECOUNT, &numNodes);
    if(errcode != 0) {
        PyObject* err = PyLong_FromLong(errcode);
        PyObject* r = PyTuple_Pack(1, err);
        Py_DECREF(err);

        return r;
    }

    float* values = (float*) malloc(sizeof(float) * numNodes);
    PyObject* err = PyLong_FromLong(ENgetnodevalues(property, values));

    PyObject* valuesList = PyList_New(numNodes);
    for(int i=0; i != numNodes; i++) {
        PyList_SET_ITEM(valuesList, i, PyFloat_FromDouble((double) values[i]));
    }

    free(values);

    PyObject* r = PyTuple_Pack(2, err, valuesList);
    Py_DECREF(valuesList);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENgetlinkvalues(PyObject* self, PyObject* args)
{
    int property;
    if(!PyArg_ParseTuple(args, "i", &property)) {
        return NULL;
    }

    int numLinks;
    int errcode = ENgetcount(EN_LINKCOUNT, &numLinks);
    if(errcode != 0) {
        PyObject* err = PyLong_FromLong(errcode);
        PyObject* r = PyTuple_Pack(1, err);
        Py_DECREF(err);

        return r;
    }

    float* value = (float*) malloc(sizeof(float) * numLinks);
    PyObject* err = PyLong_FromLong(ENgetlinkvalues(property, value));

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

PyObject* method_ENsetvertex(PyObject* self, PyObject* args)
{
    int index, vertex;
    double x, y;
    if(!PyArg_ParseTuple(args, "iidd", &index, &vertex, &x, &y)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENsetvertex(index, vertex, x, y));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENloadpatternfile(PyObject* self, PyObject* args)
{
    char* filename = NULL;
    char* id = NULL;
    if(!PyArg_ParseTuple(args, "ss", &filename, &id)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENloadpatternfile(filename, id));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENsetcurvetype(PyObject* self, PyObject* args)
{
    int index, type;
    if(!PyArg_ParseTuple(args, "ii", &index, &type)) {
        return NULL;
    }    

    PyObject* err = PyLong_FromLong(ENsetcurvetype(index, type));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENgetcontrolenabled(PyObject* self, PyObject* args)
{
    int index;
    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }

    int out_enabled;
    PyObject* err = PyLong_FromLong(ENgetcontrolenabled(index, &out_enabled));
    PyObject* pyOutEnabled = PyLong_FromLong(out_enabled);

    PyObject* r = PyTuple_Pack(2, err, pyOutEnabled);
    Py_DECREF(err);
    Py_DECREF(pyOutEnabled);

    return r;
}

PyObject* method_ENsetcontrolenabled(PyObject* self, PyObject* args)
{
    int index, enabled;
    if(!PyArg_ParseTuple(args, "ii", &index, &enabled)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENsetcontrolenabled(index, enabled));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}

PyObject* method_ENgetruleenabled(PyObject* self, PyObject* args)
{
    int index;
    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }

    int out_enabled;
    PyObject* err = PyLong_FromLong(ENgetruleenabled(index, &out_enabled));
    PyObject* pyOutEnabled = PyLong_FromLong(out_enabled);

    PyObject* r = PyTuple_Pack(2, err, pyOutEnabled);
    Py_DECREF(err);
    Py_DECREF(pyOutEnabled);

    return r;
}

PyObject* method_ENsetruleenabled(PyObject* self, PyObject* args)
{
    int index, enabled;
    if(!PyArg_ParseTuple(args, "ii", &index, &enabled)) {
        return NULL;
    }

    PyObject* err = PyLong_FromLong(ENsetruleenabled(index, enabled));

    PyObject* r = PyTuple_Pack(1, err);
    Py_DECREF(err);

    return r;
}