#include "plottervisitor.h"
#include "geometricObjects/vector2d.h"
#include "geometricObjects/line.h"
#include "geometricObjects/polygon.h"
#include "geometricObjects/circumference.h"

// Funções auxiliares mantidas apenas no escopo de implementação (.cpp)
namespace {
    inline void dict_set_double(PyObject* dict, const char* key, double value) {
        PyObject* pyVal = PyFloat_FromDouble(value);
        if (!pyVal) return;
        PyDict_SetItemString(dict, key, pyVal);
        Py_DECREF(pyVal);
    }

    inline void dict_set_string(PyObject* dict, const char* key, const char* value) {
        PyObject* pyVal = PyUnicode_FromString(value);
        if (!pyVal) return;
        PyDict_SetItemString(dict, key, pyVal);
        Py_DECREF(pyVal);
    }
}

PlotterVisitor::PlotterVisitor(PyObject* list) : pShapesList(list) {}

void PlotterVisitor::visit(Vector2D& v) {
    PyObject* shape = PyDict_New();
    if (!shape) return;

    dict_set_string(shape, "type", "point");
    
    dict_set_double(shape, "x", v.getX());
    dict_set_double(shape, "y", v.getY());
    
    PyList_Append(pShapesList, shape);
    Py_DECREF(shape);
}

void PlotterVisitor::visit(Line& l) {
    PyObject* shape = PyDict_New();
    if (!shape) return;

    dict_set_string(shape, "type", "line");
    
    PyObject* xs = PyList_New(2);
    PyObject* ys = PyList_New(2);
    
    if (xs && ys) {
        PyList_SetItem(xs, 0, PyFloat_FromDouble(l.getP1().getX()));
        PyList_SetItem(xs, 1, PyFloat_FromDouble(l.getP2().getX()));
        PyList_SetItem(ys, 0, PyFloat_FromDouble(l.getP1().getY()));
        PyList_SetItem(ys, 1, PyFloat_FromDouble(l.getP2().getY()));
        
        PyDict_SetItemString(shape, "x", xs);
        PyDict_SetItemString(shape, "y", ys);
    }
    
    Py_XDECREF(xs);
    Py_XDECREF(ys);

    PyList_Append(pShapesList, shape);
    Py_DECREF(shape);
}

void PlotterVisitor::visit(Polygon& p) {
    PyObject* shape = PyDict_New();
    if (!shape) return;

    dict_set_string(shape, "type", "polygon");
    const auto& verts = p.getVertices();
    
    PyObject* xs = PyList_New(verts.size());
    PyObject* ys = PyList_New(verts.size());

    if (xs && ys) {
        for (size_t i = 0; i < verts.size(); ++i) {
            PyList_SetItem(xs, i, PyFloat_FromDouble(verts[i].getX()));
            PyList_SetItem(ys, i, PyFloat_FromDouble(verts[i].getY()));
        }
        PyDict_SetItemString(shape, "x", xs);
        PyDict_SetItemString(shape, "y", ys);
    }

    Py_XDECREF(xs);
    Py_XDECREF(ys);

    PyList_Append(pShapesList, shape);
    Py_DECREF(shape);
}

void PlotterVisitor::visit(Circumference& c) {
    PyObject* shape = PyDict_New();
    if (!shape) return;

    dict_set_string(shape, "type", "circumference");
    dict_set_double(shape, "radius", c.getRadius());
    
    PyObject* center = PyTuple_New(2);
    if (center) {
        PyTuple_SetItem(center, 0, PyFloat_FromDouble(c.getCenter().getX()));
        PyTuple_SetItem(center, 1, PyFloat_FromDouble(c.getCenter().getY()));
        PyDict_SetItemString(shape, "center", center);
        Py_DECREF(center);
    }

    PyList_Append(pShapesList, shape);
    Py_DECREF(shape);
}
