#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <iostream>
#include <cmath>
#include <vector>

#include "geometricObjects/point.h"
#include "geometricObjects/vector2d.h"
#include "geometricObjects/line.h"
#include "geometricObjects/polygon.h"

class Calculator {
public:
    Calculator() = default;
    ~Calculator() = default;

    // ===== POINT OPERATIONS =====
    // Point + Vector = Point (translation)
    static Point addPointVector(const Point& p, const Vector2D& vec) {
        return Point(p.getX() + vec.getX(), p.getY() + vec.getY());
    }

    // Point - Point = Vector
    static Vector2D subtractPoints(const Point& p1, const Point& p2) {
        return Vector2D(p1.getX() - p2.getX(), p1.getY() - p2.getY());
    }

    // Distance between two points
    static double distance(const Point& p1, const Point& p2) {
        return p1.distanceTo(p2);
    }

    // Midpoint between two points
    static Point midpoint(const Point& p1, const Point& p2) {
        return Point((p1.getX() + p2.getX()) / 2.0, (p1.getY() + p2.getY()) / 2.0);
    }

    // ===== VECTOR OPERATIONS =====
    // Vector addition (Vector2D + Vector2D = Vector2D)
    static Vector2D addVectors(const Vector2D& v1, const Vector2D& v2) {
        return Vector2D(v1.getX() + v2.getX(), v1.getY() + v2.getY());
    }

    // Vector subtraction (Vector2D - Vector2D = Vector2D)
    static Vector2D subtractVectors(const Vector2D& v1, const Vector2D& v2) {
        return Vector2D(v1.getX() - v2.getX(), v1.getY() - v2.getY());
    }

    // Scalar multiplication (scalar * Vector2D = Vector2D)
    static Vector2D scalarMultiply(const Vector2D& v, double scalar) {
        return Vector2D(v.getX() * scalar, v.getY() * scalar);
    }

    // Scalar division (Vector2D / scalar = Vector2D)
    static Vector2D scalarDivide(const Vector2D& v, double scalar) {
        if (scalar == 0) throw std::runtime_error("Division by zero");
        return Vector2D(v.getX() / scalar, v.getY() / scalar);
    }

    // Dot product (Vector2D . Vector2D = scalar)
    static double dotProduct(const Vector2D& v1, const Vector2D& v2) {
        return v1.getX() * v2.getX() + v1.getY() * v2.getY();
    }

    // Cross product (returns scalar: signed area)
    static double crossProduct(const Vector2D& v1, const Vector2D& v2) {
        return v1.getX() * v2.getY() - v1.getY() * v2.getX();
    }

    // Magnitude (norm) of a vector
    static double magnitude(const Vector2D& v) {
        return std::sqrt(v.getX() * v.getX() + v.getY() * v.getY());
    }

    // Normalize a vector
    static Vector2D normalize(const Vector2D& v) {
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
        // Convert line segments to vectors
        Vector2D v1(seg1.getP2().getX() - seg1.getP1().getX(), 
                    seg1.getP2().getY() - seg1.getP1().getY());
        Vector2D v2(seg2.getP2().getX() - seg2.getP1().getX(), 
                    seg2.getP2().getY() - seg2.getP1().getY());
        double cross = crossProduct(v1, v2);
        // Parallel if cross product is ~0
        return std::abs(cross) < 1e-9;
    }

    // Check if two segments are perpendicular
    static bool arePerpendicular(const Line& seg1, const Line& seg2) {
        // Convert line segments to vectors
        Vector2D v1(seg1.getP2().getX() - seg1.getP1().getX(), 
                    seg1.getP2().getY() - seg1.getP1().getY());
        Vector2D v2(seg2.getP2().getX() - seg2.getP1().getX(), 
                    seg2.getP2().getY() - seg2.getP1().getY());
        double dot = dotProduct(v1, v2);
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
