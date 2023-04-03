#pragma once

#include <SFML/Graphics.hpp>

constexpr int WIDTH = 800, HEIGHT = 800;

class Simulation
{
public:
	Simulation();
	void run();
private:
	void pollEvent();
	void update(float deltaTime);
	void draw();
private:
	std::vector<sf::RectangleShape>shapes;
	sf::RenderWindow window;
	long double smallSpeed{1.f };
	long double bigSpeed{ -5.0f };
	long double smallMass{ 1.f };
	long double bigMass{ 1000000000000 };
	int hitCounter = 0;
	int timeStamp = 100000;
	// Hit counter message
	sf::Font font;
	sf::Text text;
};