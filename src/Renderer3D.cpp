#include "Renderer3D.hpp"
#include "BlinkingColors.hpp"

#include < iostream>

Renderer3D::Renderer3D(unsigned int pixel_rows, unsigned int pixel_cols) :
	pixel_rows(pixel_rows), pixel_cols(pixel_cols), pixel_count(pixel_rows * pixel_cols), pixels(new sf::Vertex[pixel_count]), zBuffer(new unsigned int[pixel_count]), viewPoint(1, 3)
{
	for (int i = 0; i < pixel_count; i++) {
		this->pixels[i].position = sf::Vector2f(i % pixel_cols, i / pixel_cols);
		this->pixels[i].color = sf::Color::Black;
		this->zBuffer[i] = 1000;
	}

	generateMat1x3(viewPlane.p, 0, 0, 0);
	generateMat1x3(viewPlane.n, 0, 0, 1);
	generateMat1x3(viewPoint, 0, 0, 300);
}

Renderer3D::~Renderer3D()
{
	delete pixels;
	delete zBuffer;
}

void Renderer3D::update()
{
	/*sf::Color color = BlinkingColors::next(this->pixels[0].color);
	for (int i = 0; i < this->pixel_count; i++) {
		this->pixels[i].color = color;
	}*/
}

sf::Vector2f Renderer3D::projectPointTo2d(Matrix p)
{
	Matrix K = intersectionLinePlane(Line(viewPoint, p), viewPlane);

	return { K[0][0], K[0][1]};
}

bool pointLiesInTriangle(sf::Vector2f point, sf::Vector2f* triangle)
{
	auto triArea = [](sf::Vector2f a, sf::Vector2f b, sf::Vector2f c) {
		return abs((a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)) / 2);
	};

	float areas[4];
	areas[0] = triArea(triangle[0], triangle[1], triangle[2]);
	areas[1] = triArea(triangle[0], triangle[1], point);
	areas[2] = triArea(triangle[0], triangle[2], point);
	areas[3] = triArea(triangle[1], triangle[2], point);

	float a = areas[1] / areas[0];
	float b = areas[2] / areas[0];
	float c = areas[3] / areas[0];

	if (1000 == round((a + b + c) * 1000))return true;
	return false;

	if (areas[1] + areas[2] + areas[3] == areas[0])return true;
	return false;
}

void Renderer3D::draw(Matrix* triangle, sf::Color color)
{
	Plane trianglePlane(triangle[0], triangle[1], triangle[2]);

	int x[2] = { pixel_cols, 0 }, y[2] = { pixel_rows, 0};
	sf::Vector2f k[3];
	for (int i = 0; i < 3; i++) {
		k[i] = projectPointTo2d(triangle[i]);
		if (k[i].x < x[0])x[0] = k[i].x;
		if (k[i].x > x[1])x[1] = k[i].x;
		if (k[i].y < y[0])y[0] = k[i].y;
		if (k[i].y > y[1])y[1] = k[i].y;
	}

	for (int j = x[0]; j < x[1]; j++) {
		for (int i = y[0]; i < y[1]; i++) {
			if (pointLiesInTriangle(sf::Vector2f(j, i), k)) {
				int index = int(i) * pixel_cols + int(j);
				if (this->pixels[index].color == sf::Color::Black)this->pixels[index].color = sf::Color::White;
				this->pixels[index].color = BlinkingColors::next(this->pixels[index].color);
			}
		}
	}
}

/*
	int index = int(k.y) * pixel_cols + int(k.x);
	if (k.z < this->zBuffer[index]) {
		this->pixels[index].color = color;
		this->zBuffer[index] = k.z;
	}
*/

void Renderer3D::render(sf::RenderWindow& window)
{
	window.draw(this->pixels, this->pixel_count, sf::Points);
}
