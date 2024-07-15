#include "line.h"
#include "ninjamath.h"
#include "debug.h"


line::line(const sf::Color& color, const bool& de)
{
	start = vert[0].position = { 0.0f, 0.0f };
	end = vert[1].position = { 0.0f, 0.0f };

	vert[0].color = color;
	vert[1].color = color;

	dotend = de;
}

line::line(const sf::Vector2f& start, const sf::Vector2f& end, const sf::Color& color, const bool& de)
{
	this->start = vert[0].position = start;
	this->end = vert[1].position = end;

	vert[0].color = color;
	vert[1].color = color;

	dotend = de;
}

void line::setstart(const sf::Vector2f& start)
{
	this->start = vert[0].position = start;
}

void line::setend(const sf::Vector2f& end)
{
	this->end = vert[1].position = end;
}

void line::offsetBy(const sf::Vector2f& offset)
{
	setstart(start - offset);
	setend(end - offset);
}

float line::direction()
{
	return (end.y - start.y) / (end.x - start.x);
}

float line::yintersect()
{
	return start.y - direction() * start.x;
}

//v1 - ifs
bool line::online(const sf::Vector2f& point)
{
	float sx = start.x < end.x ? start.x : end.x;
	float sy = start.y < end.y ? start.y : end.y;
	float ex = start.x > end.x ? start.x : end.x;
	float ey = start.y > end.y ? start.y : end.y;


	return (point.x >= sx &&
		point.x <= ex &&
		point.y >= sy &&
		point.y <= ey
		);
}

//v2 - cross product
//GONE

//cross product approach
std::optional<sf::Vector2f> line::linevline_2(const line& l)		//2nd input is for debug only!
{
	sf::Vector2f point;
	//this line
	sf::Vector2f p = start;
	sf::Vector2f r = end - start;

	//input line
	sf::Vector2f q = l.start;
	sf::Vector2f s = l.end - l.start;


	sf::Vector2f qmp = q - p;
	float rxs = math::crossZ(r, s);
	float t_n = math::crossZ(qmp, s);		//t's nominator
	float u_n = math::crossZ(qmp, r);		//u's nominator

	float t = t_n / rxs;
	float u = u_n / rxs;

	if (rxs != 0 && (t >= 0 && t <= 1) && (u >= 0 && u <= 1))
		return p + (t * r);

	return std::nullopt;
}

std::optional<sf::Vector2f> line::operator & (const line& l)
{
	//fInfo("operator &", "line", "experiment with the return value");	//use branchless pattern and return some impossible value(or sth)

	//this line
	sf::Vector2f p = start;
	sf::Vector2f r = end - start;

	//input line
	sf::Vector2f q = l.start;
	sf::Vector2f s = l.end - l.start;


	sf::Vector2f qmp = q - p;
	float rxs = math::crossZ(r, s);
	if (!rxs)
		return std::nullopt;

	float t_n = math::crossZ(qmp, s);		//t's nominator
	float u_n = math::crossZ(qmp, r);		//u's nominator

	float t = t_n / rxs;
	float u = u_n / rxs;

	if ((t >= 0 && t <= 1) && (u >= 0 && u <= 1))
	{
		//point = p + (t * r);
		return p + (t * r);
	}
	return std::nullopt;
}


void line::resetLine()
{
	setstart({ -1.0f, -1.0f });
	setend({ -1.0f, -1.0f });
}

void line::draw(sf::RenderWindow& window, bool dotend) const 
{
	window.draw(vert, 2, sf::Lines);

	if (this->dotend)
	{
		sf::CircleShape dot(4.0f);
		dot.setOrigin(dot.getRadius(), dot.getRadius());
		dot.setFillColor(vert[0].color);
		dot.setPosition(end);
		window.draw(dot);
	}
}

