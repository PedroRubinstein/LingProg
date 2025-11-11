#include "point.h"
#include "line.h"
#include "polygon.h"
#include <iostream>
#include <cmath>
#include <vector>

#ifndef CALCULATOR_H
#define CALCULATOR_H

class Calculator {
public:
    Calculator() = default;
    ~Calculator() = default;

    // ===== POINT OPERATIONS =====
    // Point + Vector (represented as Line from origin) = Point (translation)
    static Point addPointVector(const Point& p, const Line& vec) {
        double dx = vec.getP2().getX() - vec.getP1().getX();
        double dy = vec.getP2().getY() - vec.getP1().getY();
        return Point(p.getX() + dx, p.getY() + dy);
    }

    // Point - Point = Vector (represented as Line)
    static Line subtractPoints(const Point& p1, const Point& p2) {
        return Line(p2, p1);  // Vector from p2 to p1
    }

    // Distance between two points
    static double distance(const Point& p1, const Point& p2) {
        return p1.distanceTo(p2);
    }

    // Midpoint between two points
    static Point midpoint(const Point& p1, const Point& p2) {
        return Point((p1.getX() + p2.getX()) / 2.0, (p1.getY() + p2.getY()) / 2.0);
    }

    // ===== VECTOR OPERATIONS (using Line class) =====
    // Vector addition (Line + Line = Line)
    static Line addVectors(const Line& v1, const Line& v2) {
        double dx1 = v1.getP2().getX() - v1.getP1().getX();
        double dy1 = v1.getP2().getY() - v1.getP1().getY();
        double dx2 = v2.getP2().getX() - v2.getP1().getX();
        double dy2 = v2.getP2().getY() - v2.getP1().getY();
        return Line(Point(0.0, 0.0), Point(dx1 + dx2, dy1 + dy2));
    }

    // Vector subtraction (Line - Line = Line)
    static Line subtractVectors(const Line& v1, const Line& v2) {
        double dx1 = v1.getP2().getX() - v1.getP1().getX();
        double dy1 = v1.getP2().getY() - v1.getP1().getY();
        double dx2 = v2.getP2().getX() - v2.getP1().getX();
        double dy2 = v2.getP2().getY() - v2.getP1().getY();
        return Line(Point(0.0, 0.0), Point(dx1 - dx2, dy1 - dy2));
    }

    // Scalar multiplication (scalar * Vector = Vector)
    static Line scalarMultiply(const Line& v, double scalar) {
        double dx = v.getP2().getX() - v.getP1().getX();
        double dy = v.getP2().getY() - v.getP1().getY();
        return Line(Point(0.0, 0.0), Point(dx * scalar, dy * scalar));
    }

    // Scalar division (Vector / scalar = Vector)
    static Line scalarDivide(const Line& v, double scalar) {
        if (scalar == 0) throw std::runtime_error("Division by zero");
        double dx = v.getP2().getX() - v.getP1().getX();
        double dy = v.getP2().getY() - v.getP1().getY();
        return Line(Point(0.0, 0.0), Point(dx / scalar, dy / scalar));
    }

    // Dot product (Line . Line = scalar)
    static double dotProduct(const Line& v1, const Line& v2) {
        double dx1 = v1.getP2().getX() - v1.getP1().getX();
        double dy1 = v1.getP2().getY() - v1.getP1().getY();
        double dx2 = v2.getP2().getX() - v2.getP1().getX();
        double dy2 = v2.getP2().getY() - v2.getP1().getY();
        return dx1 * dx2 + dy1 * dy2;
    }

    // Cross product (returns scalar: signed area)
    static double crossProduct(const Line& v1, const Line& v2) {
        double dx1 = v1.getP2().getX() - v1.getP1().getX();
        double dy1 = v1.getP2().getY() - v1.getP1().getY();
        double dx2 = v2.getP2().getX() - v2.getP1().getX();
        double dy2 = v2.getP2().getY() - v2.getP1().getY();
        return dx1 * dy2 - dy1 * dx2;
    }  

    // Magnitude (norm) of a vector
    static double magnitude(const Line& v) {
        double dx = v.getP2().getX() - v.getP1().getX();
        double dy = v.getP2().getY() - v.getP1().getY();
        return std::sqrt(dx * dx + dy * dy);
    }

    // Normalize a vector
    static Line normalize(const Line& v) {
        double mag = magnitude(v);
        if (mag == 0) throw std::runtime_error("Cannot normalize zero vector");
        return scalarDivide(v, mag);
    }

    // ===== SEGMENT (LINE) OPERATIONS =====
    // Length of a line segment
    static double segmentLength(const Line& segment) {
        return distance(segment.getP1(), segment.getP2());
    }

    // Midpoint of a line segment
    static Point segmentMidpoint(const Line& segment) {
        return midpoint(segment.getP1(), segment.getP2());
    }

    // Check if two segments are parallel
    static bool areParallel(const Line& seg1, const Line& seg2) {
        double cross = crossProduct(seg1, seg2);
        // Parallel if cross product is ~0
        return std::abs(cross) < 1e-9;
    }

    // Check if two segments are perpendicular
    static bool arePerpendicular(const Line& seg1, const Line& seg2) {
        double dot = dotProduct(seg1, seg2);
        // Perpendicular if dot product is ~0
        return std::abs(dot) < 1e-9;
    }

    // ===== POLYGON OPERATIONS =====
    // Perimeter of a polygon
    static double polygonPerimeter(const Polygon& poly) {
        const auto& vertices = poly.getVertices();
        if (vertices.size() < 2) return 0.0;

        double perimeter = 0.0;
        for (size_t i = 0; i < vertices.size(); ++i) {
            size_t next = (i + 1) % vertices.size();
            perimeter += distance(vertices[i], vertices[next]);
        }
        return perimeter;
    }

    // Area of a polygon using Shoelace formula
    static double polygonArea(const Polygon& poly) {
        const auto& vertices = poly.getVertices();
        if (vertices.size() < 3) return 0.0;

        double area = 0.0;
        for (size_t i = 0; i < vertices.size(); ++i) {
            size_t next = (i + 1) % vertices.size();
            area += vertices[i].getX() * vertices[next].getY();
            area -= vertices[next].getX() * vertices[i].getY();
        }
        return std::abs(area) / 2.0;
    }

    // Centroid (center of mass) of a polygon
    static Point polygonCentroid(const Polygon& poly) {
        const auto& vertices = poly.getVertices();
        if (vertices.empty()) {
            return Point(0.0, 0.0);
        }
        if (vertices.size() == 1) {
            return vertices[0];
        }

        double cx = 0.0, cy = 0.0;
        for (const auto& v : vertices) {
            cx += v.getX();
            cy += v.getY();
        }
        return Point(cx / vertices.size(), cy / vertices.size());
    }

    // Check if a point is inside a polygon (ray casting algorithm)
    static bool isPointInPolygon(const Point& p, const Polygon& poly) {
        const auto& vertices = poly.getVertices();
        if (vertices.size() < 3) return false;

        int count = 0;
        for (size_t i = 0; i < vertices.size(); ++i) {
            size_t next = (i + 1) % vertices.size();
            const Point& v1 = vertices[i];
            const Point& v2 = vertices[next];

            // Check if horizontal ray from p intersects edge v1-v2
            if ((v1.getY() <= p.getY() && p.getY() < v2.getY()) ||
                (v2.getY() <= p.getY() && p.getY() < v1.getY())) {
                // Calculate x-coordinate of intersection
                double x_intersect = v1.getX() + 
                    (p.getY() - v1.getY()) / (v2.getY() - v1.getY()) * 
                    (v2.getX() - v1.getX());
                if (p.getX() < x_intersect) {
                    count++;
                }
            }
        }

        return count % 2 == 1;
    }
};

#endif