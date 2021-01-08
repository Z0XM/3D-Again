#include "SFML_Control.hpp"
#include <iostream>
#include "BlinkingColors.hpp"
#include "Matrix.hpp"

void SFML_Control::InitWindow()
{
	window.create(sf::VideoMode(1200, 700), "3D Again");
	window.setFramerateLimit(60);
}

SFML_Control::SFML_Control()
{
	this->InitWindow();

	this->renderer = new Renderer3D(window.getSize().y, window.getSize().x);

	running = true;
}

SFML_Control::~SFML_Control()
{
}

bool SFML_Control::isRunning()
{
	return this->running;
}

void SFML_Control::update()
{
	this->pollEvents();
	this->renderer->update();
}

void SFML_Control::pollEvents()
{
	sf::Event event;
	sf::Vector2f mousePos = this->getMousePosition();
	while (this->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			this->running = false;

		if (event.type == sf::Event::MouseButtonPressed) {

		}
		else if (event.type == sf::Event::MouseButtonReleased) {

		}
		else if (event.type == sf::Event::KeyPressed) {

		}
	}
}

void SFML_Control::render()
{
	this->window.clear();

	Vector tri[3]{ {100, 100, 0}, {200, 100, 0}, {150, 200, 0} };
	this->renderer->draw(tri, sf::Color::Green);

	this->renderer->render(this->window);

	this->window.display();
}

sf::Vector2f SFML_Control::getMousePosition()
{
	return window.mapPixelToCoords(sf::Mouse::getPosition(this->window));
}

sf::Vector2f SFML_Control::getWinSize()
{
	return sf::Vector2f(this->window.getSize());
}