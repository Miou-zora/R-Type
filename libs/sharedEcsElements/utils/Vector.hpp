/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Vector
*/

#pragma once

#include <cmath>
#include <iostream>

namespace rtype::utils
{
    template <typename T>
    class Vector
    {
    public:
        Vector(T _x, T _y) : x(_x), y(_y){};
        ~Vector() = default;

        Vector(const Vector<T> &other) : x(other.x), y(other.y){};
        Vector<T> &operator=(const Vector<T> &other) = default;

        Vector<T> operator+(const Vector<T> &other) const
        {
            return (Vector<T>(x + other.x, y + other.y));
        }

        Vector<T> operator-(const Vector<T> &other) const
        {
            return (Vector<T>(x - other.x, y - other.y));
        }

        Vector<T> operator*(const Vector<T> &other) const
        {
            return (Vector<T>(x * other.x, y * other.y));
        }

        Vector<T> operator/(const Vector<T> &other) const
        {
            return (Vector<T>(x / other.x, y / other.y));
        }

        Vector<T> operator*(const T &other) const
        {
            return (Vector<T>(x * other, y * other));
        }

        Vector<T> operator/(const T &other) const
        {
            return (Vector<T>(x / other, y / other));
        }

        Vector<T> &operator+=(const Vector<T> &other)
        {
            x += other.x;
            y += other.y;
            return (*this);
        }

        Vector<T> &operator-=(const Vector<T> &other)
        {
            x -= other.x;
            y -= other.y;
            return (*this);
        }

        Vector<T> &operator*=(const Vector<T> &other)
        {
            x *= other.x;
            y *= other.y;
            return (*this);
        }

        Vector<T> &operator/=(const Vector<T> &other)
        {
            x /= other.x;
            y /= other.y;
            return (*this);
        }

        Vector<T> &operator*=(const T &other)
        {
            x *= other;
            y *= other;
            return (*this);
        }

        Vector<T> &operator/=(const T &other)
        {
            x /= other;
            y /= other;
            return (*this);
        }

        Vector<T> &operator=(const T &other)
        {
            x = other;
            y = other;
            return (*this);
        }

        bool operator==(const Vector<T> &other) const
        {
            return (x == other.x && y == other.y);
        }

        bool operator<(const Vector<T> &other) const
        {
            return (getLength() < other.getLength());
        }

        bool operator<=(const Vector<T> &other) const
        {
            return (getLength() <= other.getLength());
        }

        bool operator>(const Vector<T> &other) const
        {
            return (getLength() > other.getLength());
        }

        bool operator>=(const Vector<T> &other) const
        {
            return (getLength() >= other.getLength());
        }

        bool operator!=(const Vector<T> &other) const
        {
            return (x != other.x || y != other.y);
        }

        T getLength() const
        {
            return static_cast<T>(std::sqrt(std::pow(x, 2) + std::pow(y, 2)));
        }

        Vector<T> normalized() const
        {
            return (Vector<T>(x / getLength(), y / getLength()));
        }

        T distance(const Vector<T> &other) const
        {
            return static_cast<T>(std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2)));
        }

        static Vector<T> getVector(const Vector<T> &a, const Vector<T> &b)
        {
            return (Vector<T>(b.x - a.x, b.y - a.y));
        }

        T x;
        T y;
    };


    template <typename T>
    std::ostream &operator<<(std::ostream &os, const Vector<T> &other)
    {
        os << "(" << other.x << ", " << other.y << ")";
        return (os);
    }
    template <typename T>
    Vector<T> operator/(const T &other, const Vector<T> &vec)
    {
        return (Vector<T>(other / vec.getLength(), other / vec.getLength()));
    }

    template <typename T>
    Vector<T> operator*(const T &other, const Vector<T> &vec)
    {
        return (Vector<T>(other * vec.getLength(), other * vec.getLength()));
    }

    template <typename T>
    Vector<T> operator+(const T &other, const Vector<T> &vec)
    {
        return (Vector<T>(other + vec.getLength(), other + vec.getLength()));
    }

    template <typename T>
    Vector<T> operator-(const T &other, const Vector<T> &vec)
    {
        return (Vector<T>(other - vec.getLength(), other - vec.getLength()));
    }

    template <typename T>
    Vector<T> operator-(const Vector<T> &vec)
    {
        return (Vector<T>(-vec.x, -vec.y));
    }
}
