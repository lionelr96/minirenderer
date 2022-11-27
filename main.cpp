#include "geometry.h"
#include "tgaimage.h"
#include <cmath>
#include <iostream>
#include <utility>
#include <vector>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor blue = TGAColor(0, 0, 255, 255);
const TGAColor green = TGAColor(0, 255, 0, 255);
const TGAColor yellow = TGAColor(255, 255, 0, 255);
const TGAColor purple = TGAColor(255, 0, 255, 255);
const TGAColor cyan = TGAColor(0, 255, 255, 255);

std::vector<float> interpolate(float i0, float d0, float i1, float d1);
void line(float x0, float y0, float x1, float y1, TGAImage& image, TGAColor color);
void line(Point2f a, Point2f b, TGAImage& image, TGAColor color);
void line(Point2i a, Point2i b, TGAImage& image, TGAColor color);
// void draw_wireframe(float x0, float y0, float x1, float y1, float x2, float y2, TGAImage& image, TGAColor color);
void draw_wireframe_triangle(Point2f a, Point2f b, Point2f c, TGAImage& image, TGAColor color);
void draw_wireframe_triangle(Point2i a, Point2i b, Point2i c, TGAImage& image, TGAColor color);
// void draw_wireframe_square(Point2f a, Point2f b, Point2f c, Point2f d, TGAImage& image, TGAColor color);
void draw_filled_triangle(float x0, float y0, float x1, float y1, float x2, float y2, TGAImage& image, TGAColor color);
// std::pair<float, float> project_vertex(Vec3f v, float d);
// Point2f project_vertex(Vec3f v, float d);
Point2i project_vertex(Vec3f v, float d);
void render(std::vector<Vec3f> vertices, std::vector<std::vector<int>> triangles, TGAImage& image, TGAColor color, float d);
void render_triangle(std::vector<int> triangle, std::vector<Point2i> projected, TGAImage& image, TGAColor color, float d);

int main(int argc, char** argv)
{
    TGAImage image(500, 500, TGAImage::RGB);

    // line(-200 + 300, -100 + 300, 240 + 300, 120 + 300, image, white);
    int position_x_shift = 200;
    int position_y_shift = 300;
    float distance = 1;
    int position_base = 100;

    // Point2f a(-200 + position_shift, -250 + position_shift);
    // Point2f b(200 + position_shift, 50 + position_shift);
    // Point2f c(20 + position_shift, 250 + position_shift);

    // draw_wireframe(-200 + position_shift, -250 + position_shift, 200 + position_shift, 50 + position_shift, 20 + position_shift, 250 + position_shift, image, green);

    // draw_filled_triangle(-200 + position_shift, -250 + position_shift, 200 + position_shift, 50 + position_shift, 20 + position_shift, 250 + position_shift, image, green);

    // four front vertices
    // Vec3f vAf(-position_base + position_x_shift, position_base + position_y_shift, 1);
    // Vec3f vBf(position_base + position_x_shift, position_base + position_y_shift, 1);
    // Vec3f vCf(position_base + position_x_shift, -position_base + position_y_shift, 1);
    // Vec3f vDf(-position_base + position_x_shift, -position_base + position_y_shift, 1);

    // // four back vertices
    // Vec3f vAb(-position_base + position_x_shift, position_base + position_y_shift, 1.3);
    // Vec3f vBb(position_base + position_x_shift, position_base + position_y_shift, 1.3);
    // Vec3f vCb(position_base + position_x_shift, -position_base + position_y_shift, 1.3);
    // Vec3f vDb(-position_base + position_x_shift, -position_base + position_y_shift, 1.3);

    // the front face
    // line(project_vertex(vAf, distance), project_vertex(vBf, distance), image, blue);
    // line(project_vertex(vBf, distance), project_vertex(vCf, distance), image, blue);
    // line(project_vertex(vCf, distance), project_vertex(vDf, distance), image, blue);
    // line(project_vertex(vDf, distance), project_vertex(vAf, distance), image, blue);

	// the back face
	// line(project_vertex(vAb, distance), project_vertex(vBb, distance), image, red);
    // line(project_vertex(vBb, distance), project_vertex(vCb, distance), image, red);
    // line(project_vertex(vCb, distance), project_vertex(vDb, distance), image, red);
    // line(project_vertex(vDb, distance), project_vertex(vAb, distance), image, red);

    // the front-to-back edges
    // line(project_vertex(vAf, distance), project_vertex(vAb, distance), image, green);
    // line(project_vertex(vBf, distance), project_vertex(vBb, distance), image, green);
    // line(project_vertex(vCf, distance), project_vertex(vCb, distance), image, green);
    // line(project_vertex(vDf, distance), project_vertex(vDb, distance), image, green);

    std::vector<Vec3f> vertices {};
    vertices.push_back(Vec3f(position_base + position_x_shift, position_base + position_y_shift, 1));
    vertices.push_back(Vec3f(-position_base + position_x_shift, position_base + position_y_shift, 1));
    vertices.push_back(Vec3f(-position_base + position_x_shift, -position_base + position_y_shift, 1));
    vertices.push_back(Vec3f(position_base + position_x_shift, -position_base + position_y_shift, 1));
    vertices.push_back(Vec3f(position_base + position_x_shift, position_base + position_y_shift, 1.3));
    vertices.push_back(Vec3f(-position_base + position_x_shift, position_base + position_y_shift, 1.3));
    vertices.push_back(Vec3f(-position_base + position_x_shift, -position_base + position_y_shift, 1.3));
    vertices.push_back(Vec3f(position_base + position_x_shift, -position_base + position_y_shift, 1.3));

    std::vector<std::vector<int>> triangles {
        { 0, 1, 2, 0 },
        { 0, 2, 3, 0 },
        { 4, 0, 3, 1 },
        { 4, 3, 7, 1 },
        { 5, 4, 7, 2 },
        { 5, 7, 6, 2 },
        { 1, 5, 6, 3 },
        { 1, 6, 2, 3 },
        { 4, 5, 1, 4 },
        { 4, 1, 0, 4 },
        { 2, 6, 7, 5 },
        { 2, 7, 3, 5 }
    };

    render(vertices, triangles, image, blue, distance);

    image.flip_vertically();
    image.write_tga_file("output_cube2.tga");

    return 0;
}

std::vector<float> interpolate(float i0, float d0, float i1, float d1)
{
    std::vector<float> values;
    if (i0 == i1) {
        values.push_back(d0);
        return values;
    }
    float a = (d1 - d0) / (i1 - i0);
    float d = d0;

    for (int i = i0; i <= i1; ++i) {
        values.push_back(d);
        d = d + a;
    }
    return values;
}

void line(float x0, float y0, float x1, float y1, TGAImage& image, TGAColor color)
{
    if (std::abs(x1 - x0) > std::abs(y1 - y0)) {
        // line is horizontal
        if (x0 > x1) {
            std::swap(x0, x1);
            std::swap(y0, y1);
        }
        std::vector<float> ys = interpolate(x0, y0, x1, y1);
        for (float x = x0; x < x1; ++x) {
            image.set(x, ys[x - x0], color);
            // std::cout << x << ", " << ys[x - x0] << std::endl;
        }
    } else {
        // line is vertical
        if (y0 > y1) {
            std::swap(x0, x1);
            std::swap(y0, y1);
        }
        std::vector<float> xs = interpolate(y0, x0, y1, x1);
        for (float y = y0; y < y1; ++y) {
            image.set(xs[y - y0], y, color);
            // std::cout << xs[y - y0] << ", " << y << std::endl;
        }
    }
}

void line(Point2i a, Point2i b, TGAImage& image, TGAColor color)
{
    if (std::abs(b.x - a.x) > std::abs(b.y - a.y)) {
        if (a.x > b.x) {
            std::swap(a.x, b.x);
            std::swap(a.y, b.y);
        }
        std::vector<float> ys = interpolate(a.x, a.y, b.x, b.y);

        for (float x = a.x; x <= b.x; ++x) {
            image.set(x, ys[x - a.x], color);
        }
    } else {
        if (a.y > b.y) {
            std::swap(a.x, b.x);
            std::swap(a.y, b.y);
        }
        std::vector<float> xs = interpolate(a.y, a.x, b.y, b.x);
        for (float y = a.y; y <= b.y; ++y) {
            image.set(xs[y - a.y], y, color);
        }
    }
}

void line(Point2f a, Point2f b, TGAImage& image, TGAColor color)
{
    if (std::abs(b.x - a.x) > std::abs(b.y - a.y)) {
        if (a.x > b.x) {
            std::swap(a.x, b.x);
            std::swap(a.y, b.y);
        }
        std::vector<float> ys = interpolate(a.x, a.y, b.x, b.y);

        for (float x = a.x; x < b.x; ++x) {
            image.set(x, ys[x - a.x], color);
        }
    } else {
        if (a.y > b.y) {
            std::swap(a.x, b.x);
            std::swap(a.y, b.y);
        }
        std::vector<float> xs = interpolate(a.y, a.x, b.y, a.x);
        for (float y = a.y; y < b.y; ++y) {
            image.set(xs[y - a.y], y, color);
        }
    }
}

// void draw_wireframe(float x0, float y0, float x1, float y1, float x2, float y2, TGAImage& image, TGAColor color)
// {
//     line(x0, y0, x1, y1, image, color);
//     line(x1, y1, x2, y2, image, color);
//     // std::cout << x0 << ", " << y0 << ", " << x1 << ", " << y1 << ", " << x2 << ", " << y2 << std::endl;
//     line(x2, y2, x0, y0, image, color);
// }

void draw_wireframe_triangle(Point2f a, Point2f b, Point2f c, TGAImage& image, TGAColor color)
{
    line(a.x, a.y, b.x, b.y, image, color);
    line(b.x, b.y, c.x, c.y, image, color);
    line(c.x, c.y, a.x, a.y, image, color);

    // draw_filled_triangle(a.x, a.y, b.x, b.y, c.x, c.y, image, color);
}

void draw_wireframe_triangle(Point2i a, Point2i b, Point2i c, TGAImage& image, TGAColor color)
{
    line(a.x, a.y, b.x, b.y, image, color);
    line(b.x, b.y, c.x, c.y, image, color);
    line(c.x, c.y, a.x, a.y, image, color);

    // draw_filled_triangle(a.x, a.y, b.x, b.y, c.x, c.y, image, color);
}

std::vector<float> concatenate(std::vector<float> a, std::vector<float> b)
{
    std::vector<float> c {};
    for (int i = 0; i < a.size(); ++i) {
        c.push_back(a[i]);
    }
    for (int i = 0; i < b.size(); ++i) {
        c.push_back(b[i]);
    }
    return c;
}

void draw_filled_triangle(float x0, float y0, float x1, float y1, float x2, float y2, TGAImage& image, TGAColor color)
{
    // sort the points so that y0 <= y1 <= y2
    if (y1 < y0) {
        std::swap(x1, x0);
        std::swap(y1, y0);
    }
    if (y2 < y0) {
        std::swap(x2, x0);
        std::swap(y2, y0);
    }
    if (y2 < y1) {
        std::swap(x2, x1);
        std::swap(y2, y1);
    }

    // compute the x coordinates of the triangle edges
    std::vector<float> x01 = interpolate(y0, x0, y1, x1);
    std::vector<float> x12 = interpolate(y1, x1, y2, x2);
    std::vector<float> x02 = interpolate(y0, x0, y2, x2);

    // remove last element from one vector and concatenate the short sides
    x01.pop_back();
    // std::vector<float> x012 = x01.insert(x01.end(), x12.begin(), x12.end());
    std::vector<float> x012 = concatenate(x01, x12);

    // determine which is left and which is right
    auto m = std::floor(x02.size() / 2);
    std::vector<float> x_left {};
    std::vector<float> x_right {};

    if (x02[m] < x012[m]) {
        x_left = x02;
        x_right = x012;
    } else {
        x_left = x012;
        x_right = x02;
    }

    // draw the horizontal segments
    for (int y = y0; y < y2; y++) {
        for (int x = x_left[y - y0]; x < x_right[y - y0]; x++) {
            image.set(x, y, color);
        }
    }
}

// std::pair<float, float> project_vertex(Vec3f v, float d) {
// 	return std::make_pair(v.x * d / v.z, v.y * d / v.z);
// }

Point2i project_vertex(Vec3f v, float d)
{
    return Point2i(v.x * d / v.z, v.y * d / v.z);
}

void render_triangle(std::vector<int> triangle, std::vector<Point2i> projected, TGAImage& image, TGAColor color, float d)
{
	std::vector<TGAColor> colors = { red, green, blue, yellow, purple, cyan };
    // TODO check values of triangle and match corresponding number with projected values
    draw_wireframe_triangle(projected[triangle[0]], projected[triangle[1]], projected[triangle[2]], image, colors[triangle[3]]);
    // std::cout << projected[0] << std::endl;
    // projected[0].print_points();
}

void render(std::vector<Vec3f> vertices, std::vector<std::vector<int>> triangles, TGAImage& image, TGAColor color, float d)
{
    std::vector<Point2i> projected {};
    for (auto v : vertices) {
        projected.push_back(project_vertex(v, d));
        // project_vertex(v, d).print_points();
    }

    for (auto t : triangles) {
        render_triangle(t, projected, image, cyan, d);
    }
}