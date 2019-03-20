#include "geometry.hpp"

#include <cmath>

Vector& Vector::operator*=(Scalar scalar)
{
    x *= scalar;
    y *= scalar;
    return *this;
}

Vector& Vector::operator/=(Scalar scalar)
{
    x /= scalar;
    y /= scalar;
    return *this;
}

Vector& Vector::operator+=(const Vector& other)
{
    x += other.x;
    y += other.y;
    return *this;
}

Vector& Vector::operator-=(const Vector& other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

Vector operator*(Vector vector, Scalar scalar)
{
    vector *= scalar;
    return vector;
}

Vector operator/(Vector vector, Scalar scalar)
{
    vector /= scalar;
    return vector;
}

Vector operator+(Vector lhs, const Vector& rhs)
{
    lhs += rhs;
    return lhs;
}

Vector operator-(Vector lhs, const Vector& rhs)
{
    lhs -= rhs;
    return lhs;
}

Scalar length(const Vector& vector)
{
    return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

Vector normalized(const Vector& vector)
{
    auto currentLength = length(vector);
    if (currentLength != 0) {
        return {vector.x / currentLength, vector.y / currentLength};
    } else {
        return {0, 0};
    }
}

Point& Point::operator+=(const Vector& vector)
{
    x += vector.x;
    y += vector.y;
    return *this;
}

Point& Point::operator-=(const Vector& vector)
{
    x -= vector.x;
    y -= vector.y;
    return *this;
}

Point operator+(Point point, const Vector& vector)
{
    point += vector;
    return point;
}

Point operator+(const Vector& vector, Point point)
{
    point += vector;
    return point;
}

Point operator-(Point point, const Vector& vector)
{
    point -= vector;
    return point;
}

Vector operator-(const Point& lhs, const Point& rhs)
{
    return {lhs.x - rhs.x, lhs.y - rhs.y};
}
