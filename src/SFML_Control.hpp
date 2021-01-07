#pragma once
#include <SFML/Graphics.hpp>
#include "Renderer3D.hpp"

class SFML_Control {
private:
	sf::RenderWindow window;
	bool running;

	Renderer3D *renderer;

	void InitWindow();
public:
	SFML_Control();
	~SFML_Control();

	bool isRunning();

	void update();
	void pollEvents();
	void render();

	sf::Vector2f getMousePosition();
	sf::Vector2f getWinSize();
};
