#include "Simulation.h"

long double checkBounce(long double firstMass, long double secondMass, long double firstspeed, long double secondSpeed)
{
	long double sum = firstMass + secondMass;
	long double newSpeed = (firstMass - secondMass) / sum * firstspeed;
	newSpeed += (2 * secondMass / sum) * secondSpeed;
	return newSpeed;
}

Simulation::Simulation() : window(sf::VideoMode(WIDTH,HEIGHT),"PI Calculator")
{
	window.setFramerateLimit(144);

	// Border
	sf::RectangleShape rectangle;
	rectangle.setPosition(0.0f, 0.0f);
	rectangle.setSize(sf::Vector2f(200.0f, 800.0f));
	rectangle.setFillColor(sf::Color::Green);
	shapes.push_back(rectangle);

	rectangle.move(0.0f, 400.0f);
	rectangle.setSize(sf::Vector2f(800.0f, 400.0f));
	shapes.push_back(rectangle);
	
	// Small rectangle
	rectangle.move(400.0f, -20.0f);
	rectangle.setSize(sf::Vector2f(20.0f, 20.0f));
	rectangle.setFillColor(sf::Color::White);
	shapes.push_back(rectangle);

	// Big rectangle
	rectangle.move(200.0f, -40.0f);
	rectangle.setSize(sf::Vector2f(60.0f, 60.0f));
	rectangle.setFillColor(sf::Color::Red);
	shapes.push_back(rectangle);

	font.loadFromFile("font.ttf");
	text.setFont(font);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::Red);
	text.setPosition(200.0f, 200.0f);
}

void Simulation::run()
{
	float deltaTime{ 0.0f };
	sf::Clock clock;
	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		pollEvent();
		update(deltaTime);
		window.clear();
		draw();
		window.display();
	}
}

void Simulation::pollEvent()
{
	sf::Event e;
	while (window.pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
			window.close();
	}
}

void Simulation::update(float deltaTime)
{
	for (int k = 0; k < timeStamp; k++)
	{
		// Did it hit wall
		if (shapes[2].getGlobalBounds().intersects(shapes[0].getGlobalBounds()))
		{
			smallSpeed *= -1;
			hitCounter++;

		}
		// Did it hit big rectangle
		if (shapes[2].getGlobalBounds().intersects(shapes[3].getGlobalBounds()))
		{
			long double v1 = checkBounce(smallMass, bigMass, smallSpeed, bigSpeed);
			long double v2 = checkBounce(bigMass, smallMass, bigSpeed, smallSpeed);

			smallSpeed = v1;
			bigSpeed = v2;
			hitCounter++;
		}
		shapes[2].move(static_cast<float>(smallSpeed / timeStamp), 0.0f);
		shapes[3].move(static_cast<float>(bigSpeed / timeStamp), 0.0f);
	}
}

void Simulation::draw()
{
	std::string msg = "Hit Counter: " + std::to_string(hitCounter);
	text.setString(msg);
	window.draw(text);
	for (int i = 0; i < shapes.size(); i++)
	{
		window.draw(shapes[i]);
	}
}
