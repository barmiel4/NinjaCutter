#include "ninjamath.h"


sf::Vector3f math::cross2D(const sf::Vector2f& v1, const sf::Vector2f& v2)
{
	return  sf::Vector3f(v1.y - v2.y, v2.x - v1.x, v1.x * v2.y - v1.y * v2.x);
}

float math::crossZ(const sf::Vector2f& v1, const sf::Vector2f& v2)
{
	return (v1.x * v2.y - v1.y * v2.x);
}

bool math::isZeroVector(const sf::Vector3f & v)
{
	return (v.x == 0 && v.y == 0 && v.z == 0);
}

//returns true if point is on the right side of the given line segment
bool math::pointOnSide(const sf::Vector2f& line, const sf::Vector2f& point)
{
	float z = crossZ(line, point);
	if (z > 0)		return 1;	//right
	if (z < 0)		return 0;	//left
}

float math::length(const sf::Vector2f& v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}

void math::operator *=(sf::Vector2f& v, const float& scalar)
{
	v = v * scalar;
}

sf::Vector2f math::normalize(sf::Vector2f normalized)
{
	float l = length(normalized);
	normalized *= (1.0 / l);

	return normalized;
}

//rotate and return provided vector:
sf::Vector2f math::rotate(const sf::Vector2f& v, float a)
{
	a *= M_PI / 180.0f;
	sf::Vector2f rotated(
		v.x * cos(a) - v.y * sin(a),
		v.x * sin(a) + v.y * cos(a)
	);

	return rotated;
}

//rotate provided vector:
void math::rotate(sf::Vector2f& v, float a)
{
	sf::Vector2f temp = v;
	a *= M_PI / 180.0f;
	v.x = temp.x * cos(a) - temp.y * sin(a);
	v.y = temp.x * sin(a) + temp.y * cos(a);
}

float math::dotProduct(const sf::Vector2f& v1, const sf::Vector2f& v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

//project vector v1 onto v2
sf::Vector2f math::projection(const sf::Vector2f& v1, sf::Vector2f projected)
{
	projected = math::normalize(projected);
	projected *= math::dotProduct(v1, projected);

	return projected;
}

sf::Vector2f math::normalizedRejection(const sf::Vector2f& v1, const sf::Vector2f& v2)
{
	//normalized rejection
	sf::Vector2f nr = v1 - math::projection(v1, v2);

	return normalize(nr);
}

sf::Vector2f math::vectorAbs(sf::Vector2f v)
{
	v.x = abs(v.x);
	v.y = abs(v.y);
	return v;
}
