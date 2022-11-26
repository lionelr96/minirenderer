#pragma once
#include <iostream>
#include <utility>


struct Point {
public:
    float x, y;

public:
    Point()
        : x(0)
        , y(0) {}
    Point(const float& x, const float& y)
        : x(x)
		, y(y) {}

	void print_points() {
		std::cout << x << ", " << y << std::endl;
	}
};
