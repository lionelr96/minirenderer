#include "tgaimage.h"
#include <cmath>
#include <iostream>
#include <vector>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor blue = TGAColor(0, 0, 255, 255);
const TGAColor green = TGAColor(0, 255, 0, 255);

std::vector<float> interpolate(float i0, float d0, float i1, float d1);
void line(float x0, float y0, float x1, float y1, TGAImage& image, TGAColor color);
void draw_wireframe(float x0, float y0, float x1, float y1, float x2, float y2, TGAImage& image, TGAColor color);
void draw_filled_triangle(float x0, float y0, float x1, float y1, float x2, float y2, TGAImage& image, TGAColor color);

int main(int argc, char** argv)
{
    TGAImage image(1000, 1000, TGAImage::RGB);

    // line(-200 + 300, -100 + 300, 240 + 300, 120 + 300, image, white);
    int position_shift = 500;
    draw_wireframe(-200 + position_shift, -250 + position_shift, 200 + position_shift, 50 + position_shift, 20 + position_shift, 250 + position_shift, image, green);

    draw_filled_triangle(-200 + position_shift, -250 + position_shift, 200 + position_shift, 50 + position_shift, 20 + position_shift, 250 + position_shift, image, green);

    image.flip_vertically();
    image.write_tga_file("output.tga");

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

    for (int i = i0; i < i1; ++i) {
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

void draw_wireframe(float x0, float y0, float x1, float y1, float x2, float y2, TGAImage& image, TGAColor color)
{
    line(x0, y0, x1, y1, image, color);
    line(x1, y1, x2, y2, image, color);
    // std::cout << x0 << ", " << y0 << ", " << x1 << ", " << y1 << ", " << x2 << ", " << y2 << std::endl;
    line(x2, y2, x0, y0, image, color);
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