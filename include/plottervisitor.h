#ifndef PLOTTERVISITOR_H
#define PLOTTERVISITOR_H

#include <Python.h>
#include "visitor.h"

// Forward declarations para evitar includes desnecessários no header
// e reduzir tempo de compilação
class Vector2D;
class Line;
class Polygon;
class Circumference;

/**
 * @brief Visitor responsável por converter objetos geométricos C++
 * em dicionários Python para plotagem.
 */
class PlotterVisitor : public ShapeVisitor {
public:
    /**
     * @brief Construtor
     * @param list Ponteiro para a lista Python (PyList) onde os objetos serializados serão adicionados.
     */
    explicit PlotterVisitor(PyObject* list);

    // Métodos da interface ShapeVisitor
    void visit(Vector2D& v) override;
    void visit(Line& l) override;
    void visit(Polygon& p) override;
    void visit(Circumference& c) override;

private:
    PyObject* pShapesList; // Referência não-possuidora (borrowed ref) para a lista alvo
};

#endif // PLOTTERVISITOR_H
