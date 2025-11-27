#include <Python.h>
#include <vector>
#include <iostream>

#include "plotter.h"
#include "plottervisitor.h"
#include "visitor.h"
#include "geometricObjects/geometricobject.h"

bool Plotter::saveFigure(const std::string &filename) {
    // Garante que o Python está a correr
    if (!Py_IsInitialized()) {
        std::cerr << "Error: Python not initialized." << std::endl;
        return false;
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
        std::cerr << "Error: Python not initialized." << std::endl;
        return;
    }

    PyGILState_STATE gstate = PyGILState_Ensure();

    // Recarrega o módulo plotter para limpar o estado (se necessário durante desenvolvimento)
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

    // 1. Cria a lista vazia onde os dicionários serão anexados
    PyObject* pShapes = PyList_New(0);
    if (!pShapes) {
        PyErr_Print();
        Py_DECREF(pFunc);
        Py_DECREF(pModule);
        PyGILState_Release(gstate);
        return;
    }

    // 2. Instancia o Visitor passando a lista de destino
    PlotterVisitor visitor(pShapes);

    // 3. Itera sobre os objetos e aplica o Visitor (Double Dispatch)
    // O switch-case foi removido; cada objeto sabe como se desenhar através do visitor.
    for (auto* obj : objects) {
        obj->accept(visitor);
    }

    // 4. Prepara os argumentos para a função Python
    PyObject* pArgs = PyTuple_New(1);
    if (!pArgs) {
        PyErr_Print();
        Py_DECREF(pShapes);
        Py_DECREF(pFunc);
        Py_DECREF(pModule);
        PyGILState_Release(gstate);
        return;
    }
    
    // PyTuple_SetItem rouba a referência de pShapes, então não precisamos decrementar pShapes manualmente se tiver sucesso
    PyTuple_SetItem(pArgs, 0, pShapes);

    // 5. Chama a função Python plotter.plot_objects(shapes)
    PyObject* pRes = PyObject_CallObject(pFunc, pArgs);
    if (!pRes) {
        PyErr_Print();
    } else {
        Py_DECREF(pRes);
    }

    Py_DECREF(pArgs);
    Py_DECREF(pFunc);
    Py_DECREF(pModule);
    
    // Limpeza do estado do matplotlib
    PyRun_SimpleString("import matplotlib.pyplot as plt");
    PyRun_SimpleString("plt.close('all')");
    
    PyGILState_Release(gstate);
}
