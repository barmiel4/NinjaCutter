#pragma once
#include <iostream>
#include <optional>
#include "SFML/Graphics.hpp"
#include "gameVariables.h"

//line:
struct line
{
	sf::Vertex vert[2];
	sf::Vector2f start;
	sf::Vector2f end;
	bool dotend;

	line(const sf::Color& color = sf::Color::Red, const bool& de = 0);

	line(const sf::Vector2f& start, const sf::Vector2f& end, const sf::Color& color = sf::Color::Red, const bool& de = 0);

	void setstart(const sf::Vector2f& start);

	void setend(const sf::Vector2f& end);

	float direction();

	float yintersect();

	//v1 - ifs
	bool online(const sf::Vector2f& point);

	//v2 - cross product(NOT WORKING)
	//bool online(const sf::Vector2f& point);

	//linevline collision with cross product
	std::optional<sf::Vector2f> linevline_2(line l);

	//sets line coordinates outside the range in form of a point:
	void resetLine();

	void draw(sf::RenderWindow& window, bool dotend = 0);
};

