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
	//std::cout << "default + \t";
	//calculateMomentOfInertia();
}


polygon::polygon(const properties& p_in, const vertecies& vert)
	:	prop(p_in)
{
	/*float minx = std::min_element(vert, smaller);
	float miny = std::min_element(vert, smaller);*/

	//sf::Vector2f min(-1.0f, -1.0f);
	//std::min_element(vert.begin(), vert.end(),
	//	[&](sf::Vector2f v1, sf::Vector2f v2)
	//	{
	//		//sf::Vector2f v;
	//		min.x = v1.x < v2.x ? v1.x : v2.x;
	//		min.y = v1.y < v2.y ? v1.y : v2.y;
	//		return min;
	//	}
	//);


	//BAD, BAD WAY:
	sf::Vector2f mins(10000.0f, 10000.0f);
	sf::Vector2f maxs(-10000.0f, -10000.0f);

	for (int i = 0; i < vert.size(); i++)
	{
		if (mins.x > vert[i].x)
			mins.x = vert[i].x;

		if (mins.y > vert[i].y)
			mins.y = vert[i].y;

		if (maxs.x < vert[i].x)
			maxs.x = vert[i].x;

		if (maxs.y < vert[i].y)
			maxs.y = vert[i].y;
	}

	sf::Vector2f center = (maxs - mins) * 0.5f;


	setPointCount(vert.size());
	getPoint(0);
	for (int v = 0; v < vert.size(); v++)
		setPoint(v, vert[v] - mins - center);
	dispenseProperites();
	move(mins + center);		//move it so that they have the same 'local' position, before changing individual points
	//setOrigin(mins);
	/*std::cout << "origin is: ";
	print(getOrigin());*/

	//calculateMomentOfInertia();
}

polygon::polygon(const uint16_t& vcount, const float& side, const properties& p_in)
{
	vertex = vcount;
	setPointCount(vertex);
	prop = p_in;
	dispenseProperites();
	draw(side);

	//doesnt have to be called(for now) since we call another constructor inside draw function(which shouldn be done, not elegant. For now will do):
	//calculateMomentOfInertia();
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
	//std::cout << "it behaves like moving center of mass!\n";
	prop.position = v + getPosition();
	setPosition(prop.position);
}

//moves polygon relative to it's center of mass
void polygon::moveCenterOfMass(const sf::Vector2f& v)
{
	std::cout << "examine moveCenterOfMass function implementation in more detail!\n";
	prop.position = v + getPosition();
	setPosition(prop.position);
}

//test each edge of given polygon with a given line to check if it fully penetrates
std::optional<std::vector<vertecies>> polygon::checkEdges(line cut)
{
	line edge;
	cut.start -= (getPosition());
	cut.end -= (getPosition());
	std::vector<vertecies> shapes(2);


	bool side = 0;			//begin with shape 0
	char changes = 0;
	for (int v = 0; v < getPointCount(); v++)
	{
		edge.setstart(getPoint(v));
		edge.setend(getPoint((v + 1) % getPointCount()));

		auto point = cut.linevline_2(edge);
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
	//??
	//setOrigin(getLocalBounds().width / 2.0f, getLocalBounds().height / 2.0f);
	setPosition(prop.position);
	setFillColor(prop.fillColor);
	setOutlineColor(prop.outlineColor);
	setOutlineThickness(prop.outlineThickness);
}

//test which method is better: that or with cos/sin. (The latter would need a -45d rotation when drawing a square)
void polygon::draw(const float& side)
{
	float step = (360.0f / vertex) * M_PI / 180.0f;
	//setPointCount(vertex);
	sf::Vector2f v(0, 0);
	/*sf::Vector2f v(-side * .5f, -side / (tan(step / 2.0f) * 2.0f));
	setPoint(0, v);*/
	float nx;
	char vc = 0;
	vertecies verts;

	while (vc < vertex)
	{
		nx = v.x * cos(step) - v.y * sin(step);
		v.y = v.x * sin(step) + v.y * cos(step);
		v.x = nx + side;
		//setPoint(vc, v);
		verts.push_back(v);
		vc++;
	}

	//very very BAD:
	*this = polygon(prop, verts);
}


//void polygon::calculateMomentOfInertia()
//{
//	std::cout << "assumes that all shapes deriving from polygon are rectangular[FOR NOW]!!!\n";
//	
//	momentOfInertia = 
//}