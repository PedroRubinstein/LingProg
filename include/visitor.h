#ifndef VISITOR_H
#define VISITOR_H

// Forward declarations para evitar dependências circulares de include
class Vector2D;
class Line;
class Polygon;
class Circumference;

/**
 * @brief Interface abstrata para o padrão de projeto Visitor.
 * Permite definir novas operações sobre a hierarquia de objetos geométricos 
 * sem alterar as classes dos objetos em si.
 */
class ShapeVisitor {
public:
    virtual ~ShapeVisitor() = default;

    /**
     * @brief Visita e processa um objeto do tipo Vector2D (Ponto).
     * @param v Referência para o objeto Vector2D a ser visitado.
     */
    virtual void visit(Vector2D& v) = 0;

    /**
     * @brief Visita e processa um objeto do tipo Line (Segmento de Reta).
     * @param l Referência para o objeto Line a ser visitado.
     */
    virtual void visit(Line& l) = 0;

    /**
     * @brief Visita e processa um objeto do tipo Polygon (Polígono).
     * @param p Referência para o objeto Polygon a ser visitado.
     */
    virtual void visit(Polygon& p) = 0;

    /**
     * @brief Visita e processa um objeto do tipo Circumference (Circunferência).
     * @param c Referência para o objeto Circumference a ser visitado.
     */
    virtual void visit(Circumference& c) = 0;
};

#endif // VISITOR_H
