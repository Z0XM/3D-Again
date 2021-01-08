#include "Renderer3D.hpp"
#include "BlinkingColors.hpp"

#include < iostream>

Renderer3D::Renderer3D(unsigned int pixel_rows, unsigned int pixel_cols) :
	pixel_rows(pixel_rows), pixel_cols(pixel_cols), pixel_count(pixel_rows * pixel_cols), pixels(new sf::Vertex[pixel_count]), zBuffer(new unsigned int[pixel_count]), viewPoint(0, 0, 300)
{
	for (int i = 0; i < pixel_count; i++) {
		this->pixels[i].position = sf::Vector2f(i % pixel_cols, i / pixel_cols);
		this->pixels[i].color = sf::Color::Black;
		this->zBuffer[i] = 1000;
	}

	viewPlane.n.setData(0, 0, 1);
	viewPlane.p.setData(0, 0, 0);
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

Vector Renderer3D::projectPointTo2d(Vector p)
{
	Vector K = intersectionLinePlane(Line(viewPoint, p), viewPlane);

	return { K.x, K.y, K.z};
}

bool pointLiesInTriangle(Vector point, Vector* triangle)
{
	auto triArea = [](Vector a, Vector b, Vector c) {
		return crossMag(a - b, c - b) / 2;
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
}

void Renderer3D::draw(Vector* triangle, sf::Color color)
{
	Plane trianglePlane(triangle[0], triangle[1], triangle[2]);
	int x[2] = { pixel_cols, 0 }, y[2] = { pixel_rows, 0};
	Vector k[3];
	for (int i = 0; i < 3; i++) {
		k[i] = projectPointTo2d(triangle[i]);
		if (k[i].x < x[0])x[0] = k[i].x;
		if (k[i].x > x[1])x[1] = k[i].x;
		if (k[i].y < y[0])y[0] = k[i].y;
		if (k[i].y > y[1])y[1] = k[i].y;
	}

	for (int j = x[0]; j < x[1]; j++) {
		for (int i = y[0]; i < y[1]; i++) {
			Vector q = intersectionLinePlane(Line(viewPoint, Vector(j, i, viewPlane.p.z)), trianglePlane);
			if (pointLiesInTriangle(q, k)) {
				int index = int(i) * pixel_cols + int(j);
				if (q.z < this->zBuffer[index]) {
					if (this->pixels[index].color == sf::Color::Black)this->pixels[index].color = sf::Color::White;
					this->pixels[index].color = BlinkingColors::next(this->pixels[index].color);
					this->zBuffer[index] = q.z;
				}
			}
		}
	}
}

void Renderer3D::render(sf::RenderWindow& window)
{
	window.draw(this->pixels, this->pixel_count, sf::Points);
}
