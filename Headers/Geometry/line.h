#pragma once
#include <iostream>
#include <optional>
#include "SFML/Graphics.hpp"
#include "gameVariables.h"


//line:
class line
{
public:
	sf::Vertex vert[2];
	bool dotend;

	line(const sf::Color& color = sf::Color::Red, const bool& de = 0);

	line(const sf::Vector2f& start, const sf::Vector2f& end, const sf::Color& color = sf::Color::Red, const bool& de = 0);

	void setstart(const sf::Vector2f& start);

	void setend(const sf::Vector2f& end);

	void offsetBy(const sf::Vector2f&);

	float direction();

	float yintersect();

	//v1 - ifs
	bool online(const sf::Vector2f& point);

	//v2 - cross product(NOT WORKING)
	//bool online(const sf::Vector2f& point);

	//linevline collision with cross product
	std::optional<sf::Vector2f> linevline_2(const line& l);

	//same functinality as the linevline_2 but with operator overloading
	std::optional<sf::Vector2f> operator & (const line& l);

	//sets line coordinates outside the range in form of a point:
	void resetLine();

	void draw(sf::RenderWindow& window, bool dotend = 0) const;

//should be private probably:
//private:
	sf::Vector2f start;
	sf::Vector2f end;
};

