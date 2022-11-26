#include <iostream>
#include <vector>
#include "tgaimage.h"
#include "Point.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor blue = TGAColor(0, 0, 255, 255);

std::vector<float> interpolate(float i0, float d0, float i1, float d1);
void line(float x0, float y0, float x1, float y1, TGAImage& image, TGAColor color);

int main(int argc, char** argv)
{
	TGAImage image(1000, 1000, TGAImage::RGB);

	line(-200 + 300, -100 + 300, 240 + 300, 120 + 300, image, white);

	image.flip_vertically();
	image.write_tga_file("output.tga");

	return 0;
}

std::vector<float> interpolate(float i0, float d0, float i1, float d1) {
	std::vector<float> values;
	if (i0 == i1) {
		values.push_back(d0);
		return values;
	}
	float a = ( d1 - d0 ) / ( i1 - i0 );
	float d = d0;

	for (int i = i0; i < i1; ++i) {
		values.push_back(d);
		d = d + a;
	}
	return values;

}

void line(float x0, float y0, float x1, float y1, TGAImage& image, TGAColor color) {
	if (std::abs(x1 - x0) > std::abs(y1 - y0)) {
		// the line is horizontal
		if (x0 > x1) {
			std::swap(x0, y0);
			std::swap(x1, y1);
		}
		std::vector<float> ys = interpolate(x0, y0, x1, y1);
		for (float x = x0; x < x1; ++x) {
			image.set(x, ys[x - x0], color);
		}
	} else {
		// line is vertical
		if (y0 > y1) {
			std::swap(x0, y0);
			std::swap(x1, y1);
		}
		std::vector<float> xs = interpolate(y0, x0, y1, x1);
		for (float y = y0; y < y1; ++y) {
			image.set(xs[y - y0], y, color);
		}
	}
}
