#ifndef __GEOMETRY__
#define __GEOMETRY__

#include <cmath>
#include <iostream>
#include <utility>
#include <vector>

struct Point2i {
    int x, y;

    Point2i()
        : x(0)
        , y(0)
    {
    }
    Point2i(const int& x, const int& y)
        : x(x)
        , y(y)
    {
    }

    void print_points()
    {
        std::cout << x << ", " << y << std::endl;
    }
};

struct Point2f {
public:
    float x, y;

public:
    Point2f()
        : x(0)
        , y(0)
    {
    }
    Point2f(const float& x, const float& y)
        : x(x)
        , y(y)
    {
    }

    void print_points()
    {
        std::cout << x << ", " << y << std::endl;
    }
};

struct Vec3f {
    float x, y, z, magnitude;

    // Vec3f() {}
    Vec3f(float x = 0, float y = 0, float z = 0)
        : x(x)
        , y(y)
        , z(z)
    {
        // std::cout << "Vector created!" << std::endl;
        magnitude = std::sqrt(x * x + y * y + z * z);
    }

    float dot(Vec3f& w)
    {
        return this->x * w.x + this->y * w.y + this->z * w.z;
    }

    Vec3f normalize()
    {
        this->x = this->x / magnitude;
        this->y = this->y / magnitude;
        this->z = this->z / magnitude;
        return *this;
    }

    Vec3f operator+(const Vec3f& w)
    {
        return Vec3f(this->x + w.x, this->y + w.y, this->z + w.z);
    }

    Vec3f operator-(const Vec3f& w)
    {
        return Vec3f(this->x - w.x, this->y - w.y, this->z - w.z);
    }

    Vec3f operator*(const float& x)
    {
        return Vec3f(this->x * x, this->y * x, this->z * x);
    }

    Vec3f operator/(const float& x)
    {
        return Vec3f(this->x / x, this->y / x, this->z / x);
    }

    Vec3f operator-()
    {
        return Vec3f(this->x * -1, this->y * -1, this->z * -1);
    }

    float& operator[](int i)
    {
        assert(i < 3);
        return i <= 0 ? x : (1 == i ? y : z);
    }

    // cross product
    Vec3f operator*(const Vec3f& w)
    {
        int x_value = this->y * w.z - this->z * w.y;
        int y_value = this->x * w.z - this->z * w.x;
        int z_value = this->x * w.y - this->y * w.x;
        return Vec3f(x_value, y_value, z_value);
    }
};

#endif /* __GEOMETRY__ */
