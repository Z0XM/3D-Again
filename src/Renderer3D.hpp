#pragma once
#include <SFML/Graphics.hpp>
#include "Math3D.hpp"

class Renderer3D{
	unsigned int pixel_rows, pixel_cols, pixel_count;
	sf::Vertex* pixels;
	unsigned int* zBuffer;

	Vector viewPoint;
	Plane viewPlane;

public:
	Renderer3D(unsigned int pixel_count, unsigned int pixel_rows);
	~Renderer3D();

	Vector projectPointTo2d(Vector);
	void draw(Vector* triangle, sf::Color color);

	void update();
	void render(sf::RenderWindow& window);
};