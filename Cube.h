#ifndef __CUBE__
#define __CUBE__

#include "geometry.h"
#include <vector>

struct Cube {
    Vec3f position;
    std::vector<Vec3f> vertices {};
    std::vector<std::vector<int>> triangles {};

    Cube() : position(Vec3f(0, 0, 0))
    {
    }
    Cube(Vec3f position, std::vector<Vec3f> vertices, std::vector<std::vector<int>> triangles)
		: position(position)
		, vertices(vertices)
		, triangles(triangles)
	{
    }
    ~Cube() {};
};

#endif /* __CUBE__ */
