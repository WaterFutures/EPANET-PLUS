#include <Python.h>
#include "epanet2.h"
#include "types.h"


PyObject* method_ENopen(PyObject* self, PyObject* args)
{
    char *inpFile, *rptFile, *outFile = NULL;

    if(!PyArg_ParseTuple(args, "sss", &inpFile, &rptFile, &outFile)) {
        return NULL;
    }

    int err = ENopen(inpFile, rptFile, outFile);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}


PyObject* method_ENclose(PyObject* self, PyObject* Py_UNUSED(args))
{
    int err = ENclose();

    return PyTuple_Pack(1, PyLong_FromLong(err));
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

    int err = ENaddcontrol(type, linkIndex, setting, nodeIndex, level, &index);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(index));
}

PyObject* method_ENaddcurve(PyObject* self, PyObject* args)
{
    char* id = NULL;
    if(!PyArg_ParseTuple(args, "s", &id)) {
        return NULL;
    }

    int err = ENaddcurve(id);

    return PyTuple_Pack(1, PyLong_FromLong(err));
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

    int err = ENadddemand(nodeIndex, baseDemand, demandPattern, demandName);

    return PyTuple_Pack(1, PyLong_FromLong(err));
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

    int err = ENaddlink(id, linkType, fromNode, toNode, &index);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(index));
}

PyObject* method_ENaddnode(PyObject* self, PyObject* args)
{
    char* id = NULL;
    int nodeType;
    int index;

    if(!PyArg_ParseTuple(args, "si", &id, &nodeType)) {
        return NULL;
    }

    int err = ENaddnode(id, nodeType, &index);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(index));
}

PyObject* method_ENaddpattern(PyObject* self, PyObject* args)
{
    char* id = NULL;

    if(!PyArg_ParseTuple(args, "s", &id)) {
        return NULL;
    }
    
    int err = ENaddpattern(id);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENaddrule(PyObject* self, PyObject* args)
{
    char* rule = NULL;

    if(!PyArg_ParseTuple(args, "s", &rule)) {
        return NULL;
    }

    int err = ENaddrule(rule);
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENclearreport(PyObject* self, PyObject* Py_UNUSED(args))
{
    int err = ENclearreport();
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENcloseH(PyObject* self, PyObject* Py_UNUSED(args))
{
    int err = ENcloseH();

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENcloseQ(PyObject* self, PyObject* Py_UNUSED(args))
{
    int err = ENcloseQ();
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENcopyreport(PyObject* self, PyObject* args)
{
    char* filename = NULL;

    if(!PyArg_ParseTuple(args, "s", &filename)) {
        return NULL;
    }

    int err = ENcopyreport(filename);
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENdeletecontrol(PyObject* self, PyObject* args)
{
    int index;

    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }

    int err = ENdeletecontrol(index);
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENdeletecurve(PyObject* self, PyObject* args)
{
    int index;

    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }

    int err = ENdeletecurve(index);
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENdeletedemand(PyObject* self, PyObject* args)
{
    int nodeIndex, demandIndex;

    if(!PyArg_ParseTuple(args, "ii", &nodeIndex, &demandIndex)) {
        return NULL;
    }

    int err = ENdeletedemand(nodeIndex, demandIndex);
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENdeletelink(PyObject* self, PyObject* args)
{
    int index, actionCode;

    if(!PyArg_ParseTuple(args, "ii", &index, &actionCode)) {
        return NULL;
    }

    int err = ENdeletelink(index, actionCode);
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENdeletenode(PyObject* self, PyObject* args)
{
    int index, actionCode;

    if(!PyArg_ParseTuple(args, "ii", &index, &actionCode)) {
        return NULL;
    }

    int err = ENdeletenode(index, actionCode);
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENdeletepattern(PyObject* self, PyObject* args)
{
    int index;

    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }

    int err = ENdeletepattern(index);
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENdeleterule(PyObject* self, PyObject* args)
{
    int index;

    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }

    int err = ENdeleterule(index);
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENgetaveragepatternvalue(PyObject* self, PyObject* args)
{
    int index;
    float value;

    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }

    int err = ENgetaveragepatternvalue(index, &value);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENgetbasedemand(PyObject* self, PyObject* args)
{
    int nodeIndex, demandIndex;
    float baseDemand;

    if(!PyArg_ParseTuple(args, "ii", &nodeIndex, &demandIndex)) {
        return NULL;
    }

    int err = ENgetbasedemand(nodeIndex, demandIndex, &baseDemand);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyFloat_FromDouble(baseDemand));
}

PyObject* method_ENgetcomment(PyObject* self, PyObject* args)
{
    int object, index;
    if(!PyArg_ParseTuple(args, "ii", &object, &index)) {
        return NULL;
    }

    char comment[MAXLINE + 1];
    int err = ENgetcomment(object, index, &comment[0]);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyUnicode_FromString(&comment[0]));
}

PyObject* method_ENgetcontrol(PyObject* self, PyObject* args)
{
    int index, type, linkIndex, nodeIndex;
    float setting, level;

    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }

    int err = ENgetcontrol(index, &type, &linkIndex, &setting, &nodeIndex, &level);

    return Py_BuildValue("(iiifif)", err, type, linkIndex, setting, nodeIndex, level);
    return PyTuple_Pack(6, PyLong_FromLong(err), PyLong_FromLong(type), PyLong_FromLong(linkIndex), PyFloat_FromDouble(setting), PyLong_FromLong(nodeIndex), PyFloat_FromDouble(level));
}

PyObject* method_ENgetcoord(PyObject* self, PyObject* args)
{
    int index;
    double x, y;

    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }

    int err = ENgetcoord(index, &x, &y);

    return PyTuple_Pack(3, PyLong_FromLong(err), PyFloat_FromDouble(x), PyFloat_FromDouble(y));
}

PyObject* method_ENgetcount(PyObject* self, PyObject* args)
{
    int object, count;

    if(!PyArg_ParseTuple(args, "i", &object)) {
        return NULL;
    }

    int err = ENgetcount(object, &count);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(count));
}

PyObject* method_ENgetcurve(PyObject* self, PyObject* args)
{
    int index;
    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }

    int len;
    int err = ENgetcurvelen(index, &len);
    if(err != 0) {
        return PyTuple_Pack(1, PyLong_FromLong(err));
    }

    char out_id[MAXID + 1];
    int nPoints;
    float* xValues = (float*) PyMem_Calloc(len, sizeof(float));
    float* yValues = (float*) PyMem_Calloc(len, sizeof(float));
    err = ENgetcurve(index, &out_id[0], &nPoints, xValues, yValues);

    PyObject* xValuesList = PyList_New(nPoints);
    PyObject* yValuesList = PyList_New(nPoints);

    for(int i=0; i != nPoints; i++) {
        PyList_SetItem(xValuesList, i, PyFloat_FromDouble(xValues[i]));
        PyList_SetItem(yValuesList, i, PyFloat_FromDouble(yValues[i]));
    }

    PyMem_Free(xValues);
    PyMem_Free(yValues);

    return PyTuple_Pack(5, PyLong_FromLong(err), PyUnicode_FromString(&out_id[0]), PyLong_FromLong(nPoints), xValuesList, yValuesList);
}

PyObject* method_ENgetcurveid(PyObject* self, PyObject* args)
{
    int index;
    char* id = NULL;

    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }

    int err = ENgetcurveid(index, id);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyUnicode_FromString(&id[0]));
}

PyObject* method_ENgetcurveindex(PyObject* self, PyObject* args)
{
    char* id = NULL;
    int index;

    if(!PyArg_ParseTuple(args, "s", &id)) {
        return NULL;
    }

    int err = ENgetcurveindex(id, &index);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(index));
}

PyObject* method_ENgetcurvelen(PyObject* self, PyObject* args)
{
    int index, len;

    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    } 

    int err = ENgetcurvelen(index, &len);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(len));
}

PyObject* method_ENgetcurvetype(PyObject* self, PyObject* args)
{
    int index, type;

    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }

    int err = ENgetcurvetype(index, &type);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(type));
}

PyObject* method_ENgetcurvevalue(PyObject* self, PyObject* args)
{
    int curveIndex, pointIndex;
    float x, y;

    if(!PyArg_ParseTuple(args, "ii", &curveIndex, &pointIndex)) {
        return NULL;
    }

    int err = ENgetcurvevalue(curveIndex, pointIndex, &x, &y);

    return PyTuple_Pack(3, PyLong_FromLong(err), PyFloat_FromDouble(x), PyFloat_FromDouble(y));
}

PyObject* method_ENgetdemandindex(PyObject* self, PyObject* args)
{
    int nodeIndex, demandIndex;
    char* demandName = NULL;

    if(!PyArg_ParseTuple(args, "is", &nodeIndex, &demandName)) {
        return NULL;
    }

    int err = ENgetdemandindex(nodeIndex, demandName, &demandIndex);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(demandIndex));
}

PyObject* method_ENgetdemandmodel(PyObject* self, PyObject* Py_UNUSED(args))
{
    int model;
    float pmin, preq, pexp;

    int err = ENgetdemandmodel(&model, &pmin, &preq, &pexp);
    
    return PyTuple_Pack(5, PyLong_FromLong(err), PyLong_FromLong(model), PyFloat_FromDouble(pmin), PyFloat_FromDouble(preq), PyFloat_FromDouble(pexp));
}

PyObject* method_ENgetdemandname(PyObject* self, PyObject* args)
{
    int nodeIndex, demandIndex;
    if(!PyArg_ParseTuple(args, "ii", &nodeIndex, &demandIndex)) {
        return NULL;
    } 

    char demandName[MAXID + 1];
    int err = ENgetdemandname(nodeIndex, demandIndex, &demandName[0]);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyUnicode_FromString(&demandName[0]));
}

PyObject* method_ENgetdemandpattern(PyObject* self, PyObject* args)
{
    int nodeIndex, demandIndex, patIndex;

    if(!PyArg_ParseTuple(args, "ii", &nodeIndex, &demandIndex)) {
        return NULL;
    } 

    int err = ENgetdemandpattern(nodeIndex, demandIndex, &patIndex);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(patIndex));
}

PyObject* method_ENgetelseaction(PyObject* self, PyObject* args)
{
    int ruleIndex, actionIndex, linkIndex, status;
    float setting;

    if(!PyArg_ParseTuple(args, "ii", &ruleIndex, &actionIndex)) {
        return NULL;
    }   

    int err = ENgetelseaction(ruleIndex, actionIndex, &linkIndex, &status, &setting);

    return PyTuple_Pack(4, PyLong_FromLong(err), PyLong_FromLong(linkIndex), PyLong_FromLong(status), PyFloat_FromDouble(setting));
}

PyObject* method_ENgeterror(PyObject* self, PyObject* args)
{
    int errcode;
    char errmsg[MAXMSG + 1];

    if(!PyArg_ParseTuple(args, "i", &errcode)) {
        return NULL;
    }  

    int err = ENgeterror(errcode, &errmsg[0], MAXMSG);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyUnicode_FromString(&errmsg[0]));
}

PyObject* method_ENgetflowunits(PyObject* self, PyObject* Py_UNUSED(args))
{
    int units;
    int err = ENgetflowunits(&units);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(units));
}

PyObject* method_ENgetheadcurveindex(PyObject* self, PyObject* args)
{
    int linkIndex, curveIndex;

    if(!PyArg_ParseTuple(args, "i", &linkIndex)) {
        return NULL;
    } 

    int err = ENgetheadcurveindex(linkIndex, &curveIndex);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(curveIndex));
}

PyObject* method_ENgetlinkid(PyObject* self, PyObject* args)
{
    int index;
    char id[MAXID + 1];

    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }

    int err = ENgetlinkid(index, &id[0]);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyUnicode_FromString(&id[0]));
}

PyObject* method_ENgetlinkindex(PyObject* self, PyObject* args)
{
    int index;
    char* id = NULL;

    if(!PyArg_ParseTuple(args, "s", &id)) {
        return NULL;
    }   

    int err = ENgetlinkindex(id, &index);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(index));
}

PyObject* method_ENgetlinknodes(PyObject* self, PyObject* args)
{
    int index, node1, node2;

    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }

    int err = ENgetlinknodes(index, &node1, &node2);

    return PyTuple_Pack(3, PyLong_FromLong(err), PyLong_FromLong(node1), PyLong_FromLong(node2));
}

PyObject* method_ENgetlinktype(PyObject* self, PyObject* args)
{
    int index, linkType;

    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }

    int err = ENgetlinktype(index, &linkType);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(linkType));
}

PyObject* method_ENgetlinkvalue(PyObject* self, PyObject* args)
{
    int index, property;
    float value;

    if(!PyArg_ParseTuple(args, "ii", &index, &property)) {
        return NULL;
    }

    int err = ENgetlinkvalue(index, property, &value);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyFloat_FromDouble(value));
}

PyObject* method_ENgetnodeid(PyObject* self, PyObject* args)
{
    int index;
    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }

    char id[MAXID + 1];
    int err = ENgetnodeid(index, &id[0]);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyUnicode_FromString(&id[0]));
}

PyObject* method_ENgetnodeindex(PyObject* self, PyObject* args)
{
    char* id = NULL;
    if(!PyArg_ParseTuple(args, "s", &id)) {
        return NULL;
    }

    int index;
    int err = ENgetnodeindex(id, &index);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(index));
}

PyObject* method_ENgetnodetype(PyObject* self, PyObject* args)
{
    int index, nodeType;

    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }

    int err = ENgetnodetype(index, &nodeType);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(nodeType));
}

PyObject* method_ENgetnodevalue(PyObject* self, PyObject* args)
{
    int index, property;
    float value;

    if(!PyArg_ParseTuple(args, "ii", &index, &property)) {
        return NULL;
    }

    int err = ENgetnodevalue(index, property, &value);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyFloat_FromDouble(value));
}

PyObject* method_ENgetnumdemands(PyObject* self, PyObject* args)
{
    int nodeIndex, numDemands;

    if(!PyArg_ParseTuple(args, "i", &nodeIndex)) {
        return NULL;
    }  

    int err = ENgetnumdemands(nodeIndex, &numDemands);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(numDemands));
}

PyObject* method_ENgetoption(PyObject* self, PyObject* args)
{
    int option;
    float value;

    if(!PyArg_ParseTuple(args, "i", &option)) {
        return NULL;
    }  

    int err = ENgetoption(option, &value);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromDouble(value));
}

PyObject* method_ENgetpatternid(PyObject* self, PyObject* args)
{
    int index;
    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    } 

    char id[MAXID + 1];
    int err = ENgetpatternid(index, &id[0]);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyUnicode_FromString(&id[0]));
}

PyObject* method_ENgetpatternindex(PyObject* self, PyObject* args)
{
    char *id = NULL;
    if(!PyArg_ParseTuple(args, "s", &id)) {
        return NULL;
    } 

    int index;
    int err = ENgetpatternindex(id, &index);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(index));
}

PyObject* method_ENgetpatternlen(PyObject* self, PyObject* args)
{
    int index, len;

    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }    

    int err = ENgetpatternlen(index, &len);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(len));
}

PyObject* method_ENgetpatternvalue(PyObject* self, PyObject* args)
{
    int index, period;
    float value;

    if(!PyArg_ParseTuple(args, "ii", &index, &period)) {
        return NULL;
    }

    int err = ENgetpatternvalue(index, period, &value);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyFloat_FromDouble(value));
}

PyObject* method_ENgetpremise(PyObject* self, PyObject* args)
{
    int ruleIndex, premiseIndex, logop, object, objIndex, variable, relop, status;
    float value;

    if(!PyArg_ParseTuple(args, "ii", &ruleIndex, &premiseIndex)) {
        return NULL;
    }

    int err = ENgetpremise(ruleIndex, premiseIndex, &logop, &object, &objIndex, &variable, &relop, &status, &value);

    return PyTuple_Pack(8, PyLong_FromLong(err), PyLong_FromLong(logop), PyLong_FromLong(object), PyLong_FromLong(objIndex), PyLong_FromLong(variable), PyLong_FromLong(relop), PyLong_FromLong(status), PyFloat_FromDouble(value));
}

PyObject* method_ENgetpumptype(PyObject* self, PyObject* args)
{
    int linkIndex, pumpType;

    if(!PyArg_ParseTuple(args, "i", &linkIndex)) {
        return NULL;
    }

    int err = ENgetpumptype(linkIndex, &pumpType);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(pumpType));
}

PyObject* method_ENgetqualinfo(PyObject* self, PyObject* Py_UNUSED(args))
{
    int qualType, traceNode;
    char chemName[MAXID + 1];
    char chemUnits[MAXID + 1];

    int err = ENgetqualinfo(&qualType, &chemName[0], &chemUnits[0], &traceNode);

    return PyTuple_Pack(5, PyLong_FromLong(err), PyLong_FromLong(qualType), PyUnicode_FromString(&chemName[0]), PyUnicode_FromString(&chemUnits[0]), PyLong_FromLong(traceNode));
}

PyObject* method_ENgetqualtype(PyObject* self, PyObject* Py_UNUSED(args))
{
    int qualType, traceNode;

    int err = ENgetqualtype(&qualType, &traceNode);

    return PyTuple_Pack(3, PyLong_FromLong(err), PyLong_FromLong(qualType), PyLong_FromLong(traceNode));
}

PyObject* method_ENgetresultindex(PyObject* self, PyObject* args)
{
    int type, index, value;

    if(!PyArg_ParseTuple(args, "ii", &type, &index)) {
        return NULL;
    }

    int err = ENgetresultindex(type, index, &value);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(value));
}

PyObject* method_ENgetrule(PyObject* self, PyObject* args)
{
    int index, nPremises, nThenActions, nElseActions;
    float priority;

    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }  

    int err = ENgetrule(index, &nPremises, &nThenActions, &nElseActions, &priority);

    return PyTuple_Pack(5, PyLong_FromLong(err), PyLong_FromLong(nPremises), PyLong_FromLong(nThenActions), PyLong_FromLong(nElseActions), PyFloat_FromDouble(priority));
}

PyObject* method_ENgetruleID(PyObject* self, PyObject* args)
{
    int index;
    char id[MAXID + 1];

    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }

    int err = ENgetruleID(index, &id[0]);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyUnicode_FromString(&id[0]));
}

PyObject* method_ENgetstatistic(PyObject* self, PyObject* args)
{
    int type;
    float value;

    if(!PyArg_ParseTuple(args, "i", &type)) {
        return NULL;
    }

    int err = ENgetstatistic(type, &value);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyFloat_FromDouble(value));
}

PyObject* method_ENgetthenaction(PyObject* self, PyObject* args)
{
    int ruleIndex, actionIndex, linkIndex, status;
    float setting;

    if(!PyArg_ParseTuple(args, "ii", &ruleIndex, &actionIndex)) {
        return NULL;
    }

    int err = ENgetthenaction(ruleIndex, actionIndex, &linkIndex, &status, &setting);

    return PyTuple_Pack(4, PyLong_FromLong(err), PyLong_FromLong(linkIndex), PyLong_FromLong(status), PyFloat_FromDouble(setting));
}

PyObject* method_ENgettimeparam(PyObject* self, PyObject* args)
{
    int param;
    long value;

    if(!PyArg_ParseTuple(args, "i", &param)) {
        return NULL;
    }

    int err = ENgettimeparam(param, &value);
    
    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(value));
}

PyObject* method_ENgettitle(PyObject* self, PyObject* Py_UNUSED(args))
{
    char line1[TITLELEN + 1];
    char line2[TITLELEN + 1];
    char line3[TITLELEN + 1];

    int err = ENgettitle(&line1[0], &line2[0], &line3[0]);

    return PyTuple_Pack(4, PyLong_FromLong(err), PyUnicode_FromString(&line1[0]), PyUnicode_FromString(&line2[0]), PyUnicode_FromString(&line3[0]));
}

PyObject* method_ENgetversion(PyObject* self, PyObject* Py_UNUSED(args))
{
    int version;
    int err = ENgetversion(&version);
    
    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(version));
}

PyObject* method_ENgetvertex(PyObject* self, PyObject* args)
{
    int index, vertex;
    double x, y;

    if(!PyArg_ParseTuple(args, "ii", &index, &vertex)) {
        return NULL;
    }

    int err = ENgetvertex(index, vertex, &x, &y);
    
    return PyTuple_Pack(3, PyLong_FromLong(err), PyFloat_FromDouble(x), PyFloat_FromDouble(y));
}

PyObject* method_ENgetvertexcount(PyObject* self, PyObject* args)
{
    int index, count;

    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }

    int err = ENgetvertexcount(index, &count);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(count));
}

PyObject* method_ENinit(PyObject* self, PyObject* args)
{
    char* rptFile, *outFile = NULL;
    int unitsType, headlossType;

    if(!PyArg_ParseTuple(args, "ssii", &rptFile, &outFile, &unitsType, &headlossType)) {
        return NULL;
    }

    int err = ENinit(rptFile, outFile, unitsType, headlossType);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENinitH(PyObject* self, PyObject* args)
{
    int initFlag;
    if(!PyArg_ParseTuple(args, "i", &initFlag)) {
        return NULL;
    }

    int err = ENinitH(initFlag);
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENinitQ(PyObject* self, PyObject* args)
{
    int saveFlag;
    if(!PyArg_ParseTuple(args, "i", &saveFlag)) {
        return NULL;
    }

    int err = ENinitQ(saveFlag);
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENnextH(PyObject* self, PyObject* Py_UNUSED(args))
{
    long lStep;
    int err = ENnextH(&lStep);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(lStep));
}

PyObject* method_ENnextQ(PyObject* self, PyObject* Py_UNUSED(args))
{
    long tStep;
    int err = ENnextQ(&tStep);
    
    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(tStep));
}

PyObject* method_ENopenH(PyObject* self, PyObject* Py_UNUSED(args))
{
    int err = ENopenH();
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENopenQ(PyObject* self, PyObject* Py_UNUSED(args))
{
    int err = ENopenQ();

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENreport(PyObject* self, PyObject* Py_UNUSED(args))
{
    int err = ENreport();

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENresetreport(PyObject* self, PyObject* Py_UNUSED(args))
{
    int err = ENresetreport();

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENrunH(PyObject* self, PyObject* Py_UNUSED(args))
{
    long currentTime;
    int err = ENrunH(&currentTime);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(currentTime));
}

PyObject* method_ENrunQ(PyObject* self, PyObject* Py_UNUSED(args))
{
    long currentTime;
    int err = ENrunQ(&currentTime);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(currentTime));
}

PyObject* method_ENsavehydfile(PyObject* self, PyObject* args)
{
    char* filename = NULL;

    if(!PyArg_ParseTuple(args, "s", &filename)) {
        return NULL;
    }

    int err = ENsavehydfile(filename);
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENsaveH(PyObject* self, PyObject* Py_UNUSED(args))
{
    int err = ENsaveH();

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENsaveinpfile(PyObject* self, PyObject* args)
{
    char* filename = NULL;

    if(!PyArg_ParseTuple(args, "s", &filename)) {
        return NULL;
    }

    int err = ENsaveinpfile(filename);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENsetbasedemand(PyObject* self, PyObject* args)
{
    int nodeIndex, demandIndex;
    float baseDemand;

    if(!PyArg_ParseTuple(args, "iif", &nodeIndex, &demandIndex, &baseDemand)) {
        return NULL;
    }

    int err = ENsetbasedemand(nodeIndex, demandIndex, baseDemand);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENsetcomment(PyObject* self, PyObject* args)
{
    int object, index;
    char* comment = NULL;

    if(!PyArg_ParseTuple(args, "iis", &object, &index, &comment)) {
        return NULL;
    }   

    int err = ENsetcomment(object, index, comment);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENsetcontrol(PyObject* self, PyObject* args)
{
    int index, type, linkIndex, nodeIndex;
    float setting, level;

    if(!PyArg_ParseTuple(args, "iiifif", &index, &type, &linkIndex, &setting, &nodeIndex, &level)) {
        return NULL;
    }

    int err = ENsetcontrol(index, type, linkIndex, setting, nodeIndex, level);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENsetcurveid(PyObject* self, PyObject* args)
{
    int index;
    char* id = NULL;

    if(!PyArg_ParseTuple(args, "is", &index, &id)) {
        return NULL;
    }

    int err = ENsetcurveid(index, id);

    return PyTuple_Pack(1, PyLong_FromLong(err));
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

    int err = ENsetcurve(index, xValuesRaw, yValuesRaw, nPoints);
    free(xValuesRaw);
    free(yValuesRaw);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENsetcoord(PyObject* self, PyObject* args)
{
    int index;
    double x, y;

    if(!PyArg_ParseTuple(args, "idd", &index, &x, &y)) {
        return NULL;
    }    

    int err = ENsetcoord(index, x, y);
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENsetcurvevalue(PyObject* self, PyObject* args)
{
    int curveIndex, pointIndex;
    float x, y;

    if(!PyArg_ParseTuple(args, "iiff", &curveIndex, &pointIndex, &x, &y)) {
        return NULL;
    }

    int err = ENsetcurvevalue(curveIndex, pointIndex, x, y);
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENsetdemandmodel(PyObject* self, PyObject* args)
{
    int model;
    float pmin, preq, pexp;

    if(!PyArg_ParseTuple(args, "ifff", &model, &pmin, &preq, &pexp)) {
        return NULL;
    }

    int err = ENsetdemandmodel(model, pmin, preq, pexp);
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENsetdemandname(PyObject* self, PyObject* args)
{
    int nodeIndex, demandIndex;
    char* demandName = NULL;

    if(!PyArg_ParseTuple(args, "iis", &nodeIndex, &demandIndex, &demandName)) {
        return NULL;
    }

    int err = ENsetdemandname(nodeIndex, demandIndex, demandName);
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENsetdemandpattern(PyObject* self, PyObject* args)
{
    int nodeIndex, demandIndex, patIndex;

    if(!PyArg_ParseTuple(args, "iii", &nodeIndex, &demandIndex, &patIndex)) {
        return NULL;
    }

    int err = ENsetdemandpattern(nodeIndex, demandIndex, patIndex);
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENsetelseaction(PyObject* self, PyObject* args)
{
    int ruleIndex, actionIndex, linkIndex, status;
    float setting;

    if(!PyArg_ParseTuple(args, "iiiif", &ruleIndex, &actionIndex, &linkIndex, &status, &setting)) {
        return NULL;
    }

    int err = ENsetelseaction(ruleIndex, actionIndex, linkIndex, status, setting);
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENsetflowunits(PyObject* self, PyObject* args)
{
    int units;

    if(!PyArg_ParseTuple(args, "i", &units)) {
        return NULL;
    }

    int err = ENsetflowunits(units);
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENsetheadcurveindex(PyObject* self, PyObject* args)
{
    int linkIndex, curveIndex;

    if(!PyArg_ParseTuple(args, "ii", &linkIndex, &curveIndex)) {
        return NULL;
    }

    int err = ENsetheadcurveindex(linkIndex, curveIndex);
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENsetjuncdata(PyObject* self, PyObject* args)
{
    int index;
    float elev, dmnd;
    char* dmndpat = NULL;

    if(!PyArg_ParseTuple(args, "iffs", &index, &elev, &dmnd, &dmndpat)) {
        return NULL;
    }

    int err = ENsetjuncdata(index, elev, dmnd, dmndpat);
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENsetlinkid(PyObject* self, PyObject* args)
{
    int index;
    char* newid = NULL;

    if(!PyArg_ParseTuple(args, "is", &index, &newid)) {
        return NULL;
    }

    int err = ENsetlinkid(index, newid);
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENsetlinknodes(PyObject* self, PyObject* args)
{
    int index, node1, node2;

    if(!PyArg_ParseTuple(args, "iii", &index, &node1, &node2)) {
        return NULL;
    }

    int err = ENsetlinknodes(index, node1, node2);
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENsetlinktype(PyObject* self, PyObject* args)
{
    int index;
    int linkType, actionCode;

    if(!PyArg_ParseTuple(args, "iii", &index, &linkType, &actionCode)) {
        return NULL;
    }

    int err = ENsetlinktype(&index, linkType, actionCode);
    

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENsetlinkvalue(PyObject* self, PyObject* args)
{
    int index, property;
    float value;

    if(!PyArg_ParseTuple(args, "iif", &index, &property, &value)) {
        return NULL;
    }

    int err = ENsetlinkvalue(index, property, value);
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENsetnodeid(PyObject* self, PyObject* args)
{
    int index;
    char* newid = NULL;

    if(!PyArg_ParseTuple(args, "is", &index, &newid)) {
        return NULL;
    }

    int err = ENsetnodeid(index, newid);
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENsetnodevalue(PyObject* self, PyObject* args)
{
    int index, property;
    float value;

    if(!PyArg_ParseTuple(args, "iif", &index, &property, &value)) {
        return NULL;
    }

    int err = ENsetnodevalue(index, property, value);
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENsetoption(PyObject* self, PyObject* args)
{
    int option;
    float value;

    if(!PyArg_ParseTuple(args, "if", &option, &value)) {
        return NULL;
    }

    int err = ENsetoption(option, value);
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
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

    int err = ENsetpattern(index, valuesRaw, len);
    free(valuesRaw);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENsetpatternid(PyObject* self, PyObject* args)
{
    int index;
    char* id = NULL;

    if(!PyArg_ParseTuple(args, "is", &index, &id)) {
        return NULL;
    }   

    int err = ENsetpatternid(index, id);
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENsetpatternvalue(PyObject* self, PyObject* args)
{
    int index, period;
    float value;

    if(!PyArg_ParseTuple(args, "iif", &index, &period, &value)) {
        return NULL;
    }

    int err = ENsetpatternvalue(index, period, value);
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENsetpipedata(PyObject* self, PyObject* args)
{
    int index;
    float length, diam, rough, mloss;

    if(!PyArg_ParseTuple(args, "iffff", &index, &length, &diam, &rough, &mloss)) {
        return NULL;
    }

    int err = ENsetpipedata(index, length, diam, rough, mloss);
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENsetpremise(PyObject* self, PyObject* args)
{
    int ruleIndex, premiseIndex, logop, object, objIndex, variable, relop, status;
    float value;

    if(!PyArg_ParseTuple(args, "iiiiiiiif", &ruleIndex, &premiseIndex, &logop, &object, &objIndex, &variable, &relop, &status, &value)) {
        return NULL;
    }

    int err = ENsetpremise(ruleIndex, premiseIndex, logop, object, objIndex, variable, relop, status, value);
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENsetpremiseindex(PyObject* self, PyObject* args)
{
    int ruleIndex, premiseIndex, objIndex;

    if(!PyArg_ParseTuple(args, "iii", &ruleIndex, &premiseIndex, &objIndex)) {
        return NULL;
    }

    int err = ENsetpremiseindex(ruleIndex, premiseIndex, objIndex);
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENsetpremisevalue(PyObject* self, PyObject* args)
{
    int ruleIndex, premiseIndex;
    float value;

    if(!PyArg_ParseTuple(args, "iif", &ruleIndex, &premiseIndex, &value)) {
        return NULL;
    }

    int err = ENsetpremisevalue(ruleIndex, premiseIndex, value);
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENsetpremisestatus(PyObject* self, PyObject* args)
{
    int ruleIndex, premiseIndex, status;
    if(!PyArg_ParseTuple(args, "iii", &ruleIndex, &premiseIndex, &status)) {
        return NULL;
    }

    int err = ENsetpremisestatus(ruleIndex, premiseIndex, status);
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
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

    int err = ENsetqualtype(qualtype, chemName, chemUnits, traceNode);
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENsetreport(PyObject* self, PyObject* args)
{
    char* format = NULL;

    if(!PyArg_ParseTuple(args, "s", &format)) {
        return NULL;
    }

    int err = ENsetreport(format);
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENsetrulepriority(PyObject* self, PyObject* args)
{
    int index;
    float priority;

    if(!PyArg_ParseTuple(args, "if", &index, &priority)) {
        return NULL;
    }

    int err = ENsetrulepriority(index, priority);
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENsetstatusreport(PyObject* self, PyObject* args)
{
    int level;

    if(!PyArg_ParseTuple(args, "i", &level)) {
        return NULL;
    } 

    int err = ENsetstatusreport(level);
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENsettankdata(PyObject* self, PyObject* args)
{
    int index;
    float elev, initlvl, minlvl, maxlvl, diam, minvol;
    char* volcurve = NULL;

    if(!PyArg_ParseTuple(args, "iffffffs", &index, &elev, &initlvl, &minlvl, &maxlvl, &diam, &minvol, &volcurve)) {
        return NULL;
    }

    int err = ENsettankdata(index, elev, initlvl, minlvl, maxlvl, diam, minvol, volcurve);
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENsetthenaction(PyObject* self, PyObject* args)
{
    int ruleIndex, actionIndex, linkIndex, status;
    float setting;

    if(!PyArg_ParseTuple(args, "iiiif", &ruleIndex, &actionIndex, &linkIndex, &status, &setting)) {
        return NULL;
    }

    int err = ENsetthenaction(ruleIndex, actionIndex, linkIndex, status, setting);
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENsettimeparam(PyObject* self, PyObject* args)
{
    int param;
    long value;

    if(!PyArg_ParseTuple(args, "il", &param, &value)) {
        return NULL;
    }

    int err = ENsettimeparam(param, value);
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENsettitle(PyObject* self, PyObject* args)
{
    char* line1 = NULL;
    char* line2 = NULL;
    char* line3 = NULL;

    if(!PyArg_ParseTuple(args, "sss", &line1, &line2, &line3)) {
        return NULL;
    }   

    int err = ENsettitle(line1, line2, line3);
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
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

    int err = ENsetvertices(index, xRaw, yRaw, count);
    free(xRaw);
    free(yRaw);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENsolveH(PyObject* self, PyObject* Py_UNUSED(args))
{
    int err = ENsolveH();
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENsolveQ(PyObject* self, PyObject* Py_UNUSED(args))
{
    int err = ENsolveQ();
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENstepQ(PyObject* self, PyObject* Py_UNUSED(args))
{
    long timeLeft;
    int err = ENstepQ(&timeLeft);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(timeLeft));
}

PyObject* method_ENusehydfile(PyObject* self, PyObject* args)
{
    char* filename = NULL;
    if(!PyArg_ParseTuple(args, "s", &filename)) {
        return NULL;
    }

    int err = ENusehydfile(filename);
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENwriteline(PyObject* self, PyObject* args)
{
    char* line = NULL;
    if(!PyArg_ParseTuple(args, "s", &line)) {
        return NULL;
    }

    int err = ENwriteline(line);
    
    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENgettag(PyObject* self, PyObject* args)
{
    int object, index;
    if(!PyArg_ParseTuple(args, "ii", &object, &index)) {
        return NULL;
    }

    char tag[MAXID + 1];
    int err = ENgettag(object, index, &tag[0]);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyUnicode_FromString(&tag[0]));
}

PyObject* method_ENsettag(PyObject* self, PyObject* args)
{
    int object, index;
    char* tag = NULL;
    if(!PyArg_ParseTuple(args, "iis", &object, &index, &tag)) {
        return NULL;
    }

    int err = ENsettag(object, index, tag);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENtimetonextevent(PyObject* self, PyObject* Py_UNUSED(args))
{
    int eventType, elemIndex;
    long duration;
    int err = ENtimetonextevent(&eventType, &duration, &elemIndex);

    return PyTuple_Pack(4, PyLong_FromLong(err), PyLong_FromLong(eventType), PyLong_FromLong(duration), PyLong_FromLong(elemIndex));
}

PyObject* method_ENgetnodevalues(PyObject* self, PyObject* args)
{
    int property;
    if(!PyArg_ParseTuple(args, "i", &property)) {
        return NULL;
    }

    int numNodes;
    int err = ENgetcount(EN_NODECOUNT, &numNodes);
    if(err != 0) {
        return PyTuple_Pack(1, PyLong_FromLong(err));
    }

    float* values = (float*) malloc(sizeof(float) * numNodes);
    err = ENgetnodevalues(property, values);

    PyObject* valuesList = PyList_New(numNodes);
    for(int i=0; i != numNodes; i++) {
        PyList_SET_ITEM(valuesList, i, PyFloat_FromDouble((double) values[i]));
    }

    free(values);

    return PyTuple_Pack(2, PyLong_FromLong(err), valuesList);
}

PyObject* method_ENgetlinkvalues(PyObject* self, PyObject* args)
{
    int property;
    if(!PyArg_ParseTuple(args, "i", &property)) {
        return NULL;
    }

    int numLinks;
    int err = ENgetcount(EN_LINKCOUNT, &numLinks);
    if(err != 0) {
        return PyTuple_Pack(1, PyLong_FromLong(err));
    }

    float* value = (float*) malloc(sizeof(float) * numLinks);
    err = ENgetlinkvalues(property, value);

    PyObject* valuesList = PyList_New(numLinks);
    for(int i=0; i != numLinks; i++) {
        PyList_SET_ITEM(valuesList, i, PyFloat_FromDouble(value[i]));
    }

    free(value);

    return PyTuple_Pack(2, PyLong_FromLong(err), valuesList);
}

PyObject* method_ENsetvertex(PyObject* self, PyObject* args)
{
    int index, vertex;
    double x, y;
    if(!PyArg_ParseTuple(args, "iidd", &index, &vertex, &x, &y)) {
        return NULL;
    }

    int err = ENsetvertex(index, vertex, x, y);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENloadpatternfile(PyObject* self, PyObject* args)
{
    char* filename = NULL;
    char* id = NULL;
    if(!PyArg_ParseTuple(args, "ss", &filename, &id)) {
        return NULL;
    }

    int err = ENloadpatternfile(filename, id);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENsetcurvetype(PyObject* self, PyObject* args)
{
    int index, type;
    if(!PyArg_ParseTuple(args, "ii", &index, &type)) {
        return NULL;
    }    

    int err = ENsetcurvetype(index, type);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENgetcontrolenabled(PyObject* self, PyObject* args)
{
    int index;
    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }

    int out_enabled;
    int err = ENgetcontrolenabled(index, &out_enabled);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(out_enabled));
}

PyObject* method_ENsetcontrolenabled(PyObject* self, PyObject* args)
{
    int index, enabled;
    if(!PyArg_ParseTuple(args, "ii", &index, &enabled)) {
        return NULL;
    }

    int err = ENsetcontrolenabled(index, enabled);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}

PyObject* method_ENgetruleenabled(PyObject* self, PyObject* args)
{
    int index;
    if(!PyArg_ParseTuple(args, "i", &index)) {
        return NULL;
    }

    int out_enabled;
    int err = ENgetruleenabled(index, &out_enabled);

    return PyTuple_Pack(2, PyLong_FromLong(err), PyLong_FromLong(out_enabled));
}

PyObject* method_ENsetruleenabled(PyObject* self, PyObject* args)
{
    int index, enabled;
    if(!PyArg_ParseTuple(args, "ii", &index, &enabled)) {
        return NULL;
    }

    int err = ENsetruleenabled(index, enabled);

    return PyTuple_Pack(1, PyLong_FromLong(err));
}