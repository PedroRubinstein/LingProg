
#include <Python.h>
#include <vector>
#include <iostream>

#include "plotter.h"
#include "geometricObjects/point.h"
#include "geometricObjects/line.h"
#include "geometricObjects/circumference.h"
#include "geometricObjects/vector2d.h"

namespace {
    // Helper to set string key to double value in a dict
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

Plotter::Plotter() {
    if (!Py_IsInitialized()) {
        Py_Initialize();
        PyRun_SimpleString("import sys, os");
        PyRun_SimpleString("sys.path.insert(0, os.getcwd())");
    }
}

Plotter::~Plotter() {
    Py_Finalize();
}

bool Plotter::saveFigure(const std::string &filename) {
    if (!Py_IsInitialized()) {
        Py_Initialize();
        PyRun_SimpleString("import sys, os");
        PyRun_SimpleString("sys.path.insert(0, os.getcwd())");
    }

    PyGILState_STATE gstate = PyGILState_Ensure();

    PyObject* pName = PyUnicode_DecodeFSDefault("plotter");
    if (!pName) {
        PyErr_Print();
        PyGILState_Release(gstate);
        return false;
    }

    PyObject* pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (!pModule) {
        PyErr_Print();
        PyGILState_Release(gstate);
        return false;
    }

    PyObject* pFunc = PyObject_GetAttrString(pModule, "save_figure");
    if (!pFunc || !PyCallable_Check(pFunc)) {
        PyErr_Print();
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
        PyGILState_Release(gstate);
        return false;
    }

    PyObject* pArgs = PyTuple_New(1);
    if (!pArgs) {
        PyErr_Print();
        Py_DECREF(pFunc);
        Py_DECREF(pModule);
        PyGILState_Release(gstate);
        return false;
    }

    PyObject* pFilename = PyUnicode_FromString(filename.c_str());
    if (!pFilename) {
        PyErr_Print();
        Py_DECREF(pArgs);
        Py_DECREF(pFunc);
        Py_DECREF(pModule);
        PyGILState_Release(gstate);
        return false;
    }

    PyTuple_SetItem(pArgs, 0, pFilename);

    PyObject* pRes = PyObject_CallObject(pFunc, pArgs);
    bool result = false;
    
    if (!pRes) {
        PyErr_Print();
    } else {
        if (PyBool_Check(pRes)) {
            result = PyObject_IsTrue(pRes);
        }
        Py_DECREF(pRes);
    }

    Py_DECREF(pArgs);
    Py_DECREF(pFunc);
    Py_DECREF(pModule);
    PyGILState_Release(gstate);

    return result;
}

void Plotter::plot(const std::vector<geometricObject*> &objects) {
    if (!Py_IsInitialized()) {
        Py_Initialize();
        PyRun_SimpleString("import sys, os");
        PyRun_SimpleString("sys.path.insert(0, os.getcwd())");
    }

    PyGILState_STATE gstate = PyGILState_Ensure();

    // Reload the plotter module to reset state
    PyRun_SimpleString("import importlib");
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("if 'plotter' in sys.modules: importlib.reload(sys.modules['plotter'])");

    PyObject* pName = PyUnicode_DecodeFSDefault("plotter");
    if (!pName) {
        PyErr_Print();
        PyGILState_Release(gstate);
        return;
    }

    PyObject* pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (!pModule) {
        PyErr_Print();
        PyGILState_Release(gstate);
        return;
    }

    PyObject* pFunc = PyObject_GetAttrString(pModule, "plot_objects");
    if (!pFunc || !PyCallable_Check(pFunc)) {
        PyErr_Print();
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
        PyGILState_Release(gstate);
        return;
    }

    // Build Python list of shape dicts
    PyObject* pShapes = PyList_New(objects.size());
    if (!pShapes) {
        PyErr_Print();
        Py_DECREF(pFunc);
        Py_DECREF(pModule);
        PyGILState_Release(gstate);
        return;
    }

    size_t idx = 0;
    for (auto* obj : objects) {
        PyObject* shape = PyDict_New();
        if (!shape) {
            PyErr_Print();
            continue;
        }

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
                if (!xs || !ys) {
                    Py_XDECREF(xs);
                    Py_XDECREF(ys);
                    Py_DECREF(shape);
                    PyErr_Print();
                    continue;
                }
                for (size_t i = 0; i < verts.size(); ++i) {
                    PyList_SetItem(xs, i, PyFloat_FromDouble(verts[i].getX()));
                    PyList_SetItem(ys, i, PyFloat_FromDouble(verts[i].getY()));
                }
                PyDict_SetItemString(shape, "x", xs);
                Py_DECREF(xs);
                PyDict_SetItemString(shape, "y", ys);
                Py_DECREF(ys);
                break;
            }
            case geometricObject::Type::Line: {
                auto* l = dynamic_cast<Line*>(obj);
                dict_set_string(shape, "type", "line");
                PyObject* xs = PyList_New(2);
                PyObject* ys = PyList_New(2);
                if (!xs || !ys) {
                    Py_XDECREF(xs);
                    Py_XDECREF(ys);
                    Py_DECREF(shape);
                    PyErr_Print();
                    continue;
                }
                PyList_SetItem(xs, 0, PyFloat_FromDouble(l->getP1().getX()));
                PyList_SetItem(xs, 1, PyFloat_FromDouble(l->getP2().getX()));
                PyList_SetItem(ys, 0, PyFloat_FromDouble(l->getP1().getY()));
                PyList_SetItem(ys, 1, PyFloat_FromDouble(l->getP2().getY()));
                PyDict_SetItemString(shape, "x", xs);
                Py_DECREF(xs);
                PyDict_SetItemString(shape, "y", ys);
                Py_DECREF(ys);
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
            case geometricObject::Type::Vector2D: {
                auto* v = dynamic_cast<Vector2D*>(obj);
                dict_set_string(shape, "type", "vector");
                dict_set_double(shape, "x", v->getX());
                dict_set_double(shape, "y", v->getY());
                break;
            }
            default:
                dict_set_string(shape, "type", "unknown");
                break;
        }

        PyList_SetItem(pShapes, idx++, shape);
    }

    PyObject* pArgs = PyTuple_New(1);
    if (!pArgs) {
        PyErr_Print();
        Py_DECREF(pShapes);
        Py_DECREF(pFunc);
        Py_DECREF(pModule);
        PyGILState_Release(gstate);
        return;
    }
    PyTuple_SetItem(pArgs, 0, pShapes);

    PyObject* pRes = PyObject_CallObject(pFunc, pArgs);
    if (!pRes) {
        PyErr_Print();
    } else {
        Py_DECREF(pRes);
    }

    Py_DECREF(pArgs);
    Py_DECREF(pFunc);
    Py_DECREF(pModule);
    
    // Clean up matplotlib state from Python side
    PyRun_SimpleString("import matplotlib.pyplot as plt");
    PyRun_SimpleString("plt.close('all')");
    
    PyGILState_Release(gstate);
}
