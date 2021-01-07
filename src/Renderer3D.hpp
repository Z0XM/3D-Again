#pragma once
#include <SFML/Graphics.hpp>
#include "Math3D.hpp"
#include "Matrix.hpp"

class Renderer3D{
	unsigned int pixel_rows, pixel_cols, pixel_count;
	sf::Vertex* pixels;
	unsigned int* zBuffer;

	Plane viewPlane;
	Matrix viewPoint;

public:
	Renderer3D(unsigned int pixel_count, unsigned int pixel_rows);
	~Renderer3D();

	sf::Vector2f projectPointTo2d(Matrix);
	void draw(Matrix* triangle, sf::Color color);

	void update();
	void render(sf::RenderWindow& window);
};