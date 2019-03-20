#pragma once

using Scalar = float;

struct Vector {
    Vector& operator*=(Scalar scalar);
    Vector& operator/=(Scalar scalar);

    Vector& operator+=(const Vector& other);
    Vector& operator-=(const Vector& other);

    Scalar x;
    Scalar y;
};

Vector operator*(Vector vector, Scalar scalar);
Vector operator/(Vector vector, Scalar scalar);

Vector operator+(Vector lhs, const Vector& rhs);
Vector operator-(Vector lhs, const Vector& rhs);

Scalar length(const Vector& vector);
Vector normalized(const Vector& vector);

struct Point {
    Point& operator+=(const Vector& vector);
    Point& operator-=(const Vector& vector);

    Scalar x;
    Scalar y;
};

Point operator+(Point point, const Vector& vector);
Point operator+(const Vector& vector, Point point);
Point operator-(Point point, const Vector& vector);
Vector operator-(const Point& lhs, const Point& rhs);
