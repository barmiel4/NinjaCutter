#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include "SFML/Graphics.hpp"

namespace math
{
	sf::Vector3f cross2D(const sf::Vector2f& v1, const sf::Vector2f& v2);

	bool isZeroVector(const sf::Vector3f& v);

	float crossZ(const sf::Vector2f& v1, const sf::Vector2f& v2);

	//returns true if point is on the right side of the given line segment
	bool pointOnSide(const sf::Vector2f& line, const sf::Vector2f& point);

	float length(const sf::Vector2f& v);

	void operator *=(sf::Vector2f& v, const float& scalar);

	sf::Vector2f normalize(sf::Vector2f v);

	//rotate and return provided vector:
	sf::Vector2f rotate(const sf::Vector2f& v, float a);

	//rotate provided vector:
	void rotate(sf::Vector2f& v, float a);

	float dotProduct(const sf::Vector2f& v1, const sf::Vector2f& v2);

	//project vector v1 onto v2
	sf::Vector2f projection(const sf::Vector2f& v1, sf::Vector2f projected);

	sf::Vector2f normalizedRejection(const sf::Vector2f& v1, const sf::Vector2f& v2);

	sf::Vector2f vectorAbs(sf::Vector2f v);
}