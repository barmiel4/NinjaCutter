#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <optional>
#include "ninjamath.h"
#include "line.h"

typedef std::vector<sf::Vector2f> vertecies;

struct properties
{
	sf::Vector2f position;

	sf::Color fillColor;
	sf::Color outlineColor;
	float outlineThickness;

	properties();

	properties(const sf::Vector2f& p, const sf::Color& fillColor_in, const sf::Color& outlineColor_in, const float& outlineThickness_in);
};


struct polygon : public sf::ConvexShape
{
	properties prop;
	uint16_t vertex;
	sf::Vector2f origin;
	//float momentOfInertia;
	float sidelength;

	polygon();

	polygon(const properties& p_in, const vertecies& vert);

	polygon(const uint16_t& vcount, const float& side, const properties& p_in);

	void dispenseProperites();

	//later on MUST BE PROTECTED(so that only rigid body can call it and know about the rotation):
	//moved to rigidBody:
	void rotate(const float& a);

	//later on MUST BE PROTECTED(so that only rigid body can call it and know about the movement):
	//overrides the basic convex shape function. Moves relative to the (0,0) point
	void move(const sf::Vector2f& v);

	//moves polygon relative to it's center of mass
	void moveCenterOfMass(const sf::Vector2f& v);

	//test each edge of given polygon with a given line to check if it fully penetrates
	std::optional<std::vector<vertecies>> checkEdges(line cut);

protected:
	void draw(const float& a);

	//void calculateMomentOfInertia();
};



