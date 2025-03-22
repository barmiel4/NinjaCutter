#include <iostream>
#include <algorithm>
#include "polygon.h"
#include "debug.h"

properties::properties() {}

properties::properties(const sf::Vector2f& p, const sf::Color& fillColor_in, const sf::Color& outlineColor_in, const float& outlineThickness_in)
	: position(p), fillColor(fillColor_in), outlineColor(outlineColor_in), outlineThickness(outlineThickness_in)
{}

polygon::polygon() 
{
}


polygon::polygon(const properties& p_in, const vertecies& vert)
	:	prop(p_in)
{
	auto center = findCenter(vert);

	setPointCount(vert.size());
	for (int v = 0; v < vert.size(); v++)
		setPoint(v, vert[v] - center);

	dispenseProperites();
	this->move(center);		//move it so that they have the same 'local' position, before changing individual points

#ifdef VIS_DEBUG
	debugLines.push_back(line({ 0.f, 0.f }, getPosition(), sf::Color::Cyan, 1));
#endif
}

polygon::polygon(const uint16_t& vcount, const float& side, const properties& p_in)
{
	vertCount = vcount;
	prop = p_in;
	dispenseProperites();
	draw(side);
}

//later on MUST BE PROTECTED(so that only rigid body can call it and know about the rotation):
void polygon::rotate(const float& a)
{
	for (int v = 0; v < getPointCount(); v++)
		setPoint(v, math::rotate(getPoint(v), a));
}

//later on MUST BE PROTECTED(so that only rigid body can call it and know about the movement):
//overrides the basic convex shape function. Moves relative to the (0,0) point
void polygon::move(const sf::Vector2f& v)
{
	prop.position = v + getPosition();
	setPosition(prop.position);
}

//moves polygon relative to it's center of mass
void polygon::moveCenterOfMass(const sf::Vector2f& v)
{
#ifdef _DEBUG
	std::cout << "examine moveCenterOfMass function implementation in more detail!\n";
#endif

	prop.position = v + getPosition();
	setPosition(prop.position);
}

//test each edge of given polygon with a given line to check if it fully penetrates
std::optional<std::vector<vertecies>> polygon::checkEdges(line cut)
{
	line edge;
	cut.offsetBy(getPosition());
	std::vector<vertecies> shapes(2);


	bool side = 0;			//begin with shape 0
	char changes = 0;
	for (int v = 0; v < getPointCount(); v++)
	{
		edge.setstart(getPoint(v));
		edge.setend(getPoint((v + 1) % getPointCount()));

		auto point = cut & edge;

		if (point)
		{
			changes++;
			shapes[side].push_back(point.value());
			side = !side;								//switch sides
			shapes[side].push_back(point.value());
		}
		shapes[side].push_back(getPoint((v + 1) % getPointCount()));
	}

	if (changes == 2)
		return shapes;
	return std::nullopt;
}

//does exactly the same thing as polygon::checkEdges but with operator overloading
std::optional<std::vector<vertecies>> polygon::operator / (line cut)
{
	line edge;
	cut.offsetBy(getPosition());
	std::vector<vertecies> shapes(2);


	bool side = 0;			//begin with shape 0
	char changes = 0;
	for (int v = 0; v < getPointCount(); v++)
	{
		edge.setstart(getPoint(v));
		edge.setend(getPoint((v + 1) % getPointCount()));

		auto point = cut & edge;

		if (point)
		{
			changes++;
			shapes[side].push_back(point.value());
			side = !side;								//switch sides
			shapes[side].push_back(point.value());
		}
		shapes[side].push_back(getPoint((v + 1) % getPointCount()));
	}
	if (changes == 2)
		return shapes;
	return std::nullopt;
}


void polygon::dispenseProperites() 
{
	setPosition(prop.position);
	setFillColor(prop.fillColor);
	setOutlineColor(prop.outlineColor);
	setOutlineThickness(prop.outlineThickness);
}

//test which method is better: that or with cos/sin. (The latter would need a -45d rotation when drawing a square)
void polygon::draw(const float& side)
{
	setPointCount(vertCount);
	float step = (360.0f / vertCount) * M_PI / 180.0f;
	sf::Vector2f v(0, 0);
	float nx;
	uint8_t vc = 0;

	sf::Vector2f center(0.f, 0.f);
	sf::Vector2f offset(0.f, 0.f);

	while (vc < vertCount)
	{
		nx = v.x * cos(step) - v.y * sin(step);
		v.y = v.x * sin(step) + v.y * cos(step);
		v.x = nx + side;
		setPoint(vc, v - offset);
		center += v;
		vc++;
	}

	center /= (float)getPointCount();
	for (int v = 0; v < getPointCount(); v++)
		setPoint(v, getPoint(v) - center);
	this->move(center);		
}

sf::Vector2f polygon::findCenter(const vertecies& verts) const
{
	sf::Vector2f vsum(0.f, 0.f);

	int i = 1;

	for (const auto& v : verts)
		vsum += v;

	return vsum / (float)verts.size();
}