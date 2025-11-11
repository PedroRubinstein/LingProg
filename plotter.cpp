#include "plotter.h"
#include "point.h"
#include "line.h"
#include "circumference.h"
#include <Python.h>
#include <vector>
#include <iostream>

namespace {
    // Helper to set string key to double value in a dict
    inline void dict_set_double(PyObject* dict, const char* key, double value) {
        PyObject* pyVal = PyFloat_FromDouble(value);
        PyDict_SetItemString(dict, key, pyVal);
        Py_DECREF(pyVal);
    }

    inline void dict_set_string(PyObject* dict, const char* key, const char* value) {
        PyObject* pyVal = PyUnicode_FromString(value);
        PyDict_SetItemString(dict, key, pyVal);
        Py_DECREF(pyVal);
    }
}

void Plotter::plot(const std::vector<geometricObject*> &objects) {
    Py_Initialize();
    
        // Ensure current working directory is on sys.path to find plotter.py
        PyRun_SimpleString("import sys, os");
        PyRun_SimpleString("sys.path.insert(0, os.getcwd())");

    PyObject* pName = PyUnicode_DecodeFSDefault("plotter");
    PyObject* pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (!pModule) {
        PyErr_Print();
        Py_Finalize();
        return;
    }

    PyObject* pFunc = PyObject_GetAttrString(pModule, "plot_objects");
    if (!pFunc || !PyCallable_Check(pFunc)) {
        PyErr_Print();
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
        Py_Finalize();
        return;
    }

    // Build Python list of shape dicts
    PyObject* pShapes = PyList_New(objects.size());
    size_t idx = 0;
    for (auto* obj : objects) {
        PyObject* shape = PyDict_New();
        switch (obj->type()) {
            case geometricObject::Type::Point: {
                auto* p = dynamic_cast<Point*>(obj);
                dict_set_string(shape, "type", "point");
                dict_set_double(shape, "x", p->getX());
                dict_set_double(shape, "y", p->getY());
                break;
            }
            case geometricObject::Type::Polygon: {
                auto* poly = dynamic_cast<Polygon*>(obj);
                dict_set_string(shape, "type", "polygon");
                const auto& verts = poly->getVertices();
                PyObject* xs = PyList_New(verts.size());
                PyObject* ys = PyList_New(verts.size());
                for (size_t i = 0; i < verts.size(); ++i) {
                    PyList_SetItem(xs, i, PyFloat_FromDouble(verts[i].getX()));
                    PyList_SetItem(ys, i, PyFloat_FromDouble(verts[i].getY()));
                }
                PyDict_SetItemString(shape, "x", xs); Py_DECREF(xs);
                PyDict_SetItemString(shape, "y", ys); Py_DECREF(ys);
                break;
            }
            case geometricObject::Type::Line: {
                auto* l = dynamic_cast<Line*>(obj);
                dict_set_string(shape, "type", "line");
                PyObject* xs = PyList_New(2);
                PyObject* ys = PyList_New(2);
                PyList_SetItem(xs, 0, PyFloat_FromDouble(l->getP1().getX()));
                PyList_SetItem(xs, 1, PyFloat_FromDouble(l->getP2().getX()));
                PyList_SetItem(ys, 0, PyFloat_FromDouble(l->getP1().getY()));
                PyList_SetItem(ys, 1, PyFloat_FromDouble(l->getP2().getY()));
                PyDict_SetItemString(shape, "x", xs); Py_DECREF(xs);
                PyDict_SetItemString(shape, "y", ys); Py_DECREF(ys);
                break;
            }
            case geometricObject::Type::Circumference: {
                auto* c = dynamic_cast<Circumference*>(obj);
                dict_set_string(shape, "type", "circumference");
                dict_set_double(shape, "radius", c->getRadius());
                PyObject* center = PyTuple_New(2);
                if (!center) {
                    PyErr_Print();
                    Py_DECREF(shape);
                    continue;
                }
                PyObject* cx = PyFloat_FromDouble(c->getCenter().getX());
                PyObject* cy = PyFloat_FromDouble(c->getCenter().getY());
                if (!cx || !cy) {
                    Py_XDECREF(cx);
                    Py_XDECREF(cy);
                    Py_DECREF(center);
                    Py_DECREF(shape);
                    PyErr_Print();
                    continue;
                }
                PyTuple_SetItem(center, 0, cx);
                PyTuple_SetItem(center, 1, cy);
                int ret = PyDict_SetItemString(shape, "center", center);
                if (ret != 0) {
                    PyErr_Print();
                }
                Py_DECREF(center);
                break;
            }
            default:
                dict_set_string(shape, "type", "unknown");
                break;
        }

        PyList_SetItem(pShapes, idx++, shape); // steals ref to shape
    }

    PyObject* pArgs = PyTuple_New(1);
    PyTuple_SetItem(pArgs, 0, pShapes); // steals ref

    PyObject* pRes = PyObject_CallObject(pFunc, pArgs);
    if (!pRes) {
        PyErr_Print();
    } else {
        Py_DECREF(pRes);
    }

    Py_DECREF(pArgs);
    Py_DECREF(pFunc);
    Py_DECREF(pModule);
    Py_Finalize();
}