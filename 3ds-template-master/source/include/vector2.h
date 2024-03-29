#pragma once

struct Vector2
{
    float x, y;

    Vector2() : x(0), y(0) {}
    Vector2(float x, float y) : x(x), y(y) {}
    void operator=(const Vector2& other)
    {
        x = other.x;
        y = other.y;
    }

    Vector2 operator+(const Vector2& other)
    {
        return Vector2((x + other.x), (y + other.y));
    }

    Vector2 operator-(const Vector2& other)
    {
        return Vector2((x - other.x), (y - other.y));
    }

    Vector2 operator*(const float other)
    {
        return Vector2((x * other), (y * other));
    }

    Vector2 operator/(const float other)
    {
        return Vector2((x / other), (y / other));
    }

    void operator+=(const Vector2& other) { (*this) = (*this) + other; }
    void operator-=(const Vector2& other) { (*this) = (*this) - other; }
    void operator*=(const float other) { (*this) = (*this) * other; }
    void operator/=(const float other) { (*this) = (*this) / other; }

    bool operator==(const Vector2& other)
    {
        return ((x == other.x) && (y == other.y));
    }

    bool operator!=(const Vector2& other)
    {
        return ((x != other.x) && (y != other.y));
    }
};