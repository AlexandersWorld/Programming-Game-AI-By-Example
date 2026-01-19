#pragma once
#include <cmath>

struct Vector2D
{
    double x;
    double y;

    Vector2D() : x(0.0), y(0.0) {}
    Vector2D(double x_, double y_) : x(x_), y(y_) {}

    Vector2D operator+(const Vector2D& rhs) const
    {
        return { x + rhs.x, y + rhs.y };
    }

    Vector2D operator-(const Vector2D& rhs) const
    {
        return { x - rhs.x, y - rhs.y };
    }

    Vector2D operator*(double scalar) const
    {
        return { x * scalar, y * scalar };
    }

    Vector2D operator/(double scalar) const
    {
        return { x / scalar, y / scalar };
    }

    double Length() const
    {
        return std::sqrt(x * x + y * y);
    }

    Vector2D Normalize() const
    {
        double len = Length();
        return (len > 0) ? Vector2D(x / len, y / len) : Vector2D();
    }

    Vector2D Perp() const
    {
        return Vector2D(-y, x);
    }

};
