#pragma once
#include <optional>
#include "SFML/Graphics.hpp"
#include "ninjamath.h"
#include "polygon.h"


struct forcesphere
{

};

struct rigidBody
{
	//later should be private:
public:
	float mass;
	sf::Vector2f linearVelocity;
	float angularVelocity;
	//float angularAcceleration;
	float torque;
	sf::Vector2f force;
	float momentOfInertia;
	//add more
	polygon poly;

	rigidBody();

	rigidBody(const polygon& poly_in);

	rigidBody(const polygon& poly_in, const float& mass_in);


	void addForce(const sf::Vector2f& force_in, const sf::Vector2f& effector, bool inWorldSpace = 1);

	void addForce(const sf::Vector2f& fDirection, const float& fStrength, const sf::Vector2f& effector, bool inWorldSpace = 1);

	void placeForce(const sf::Vector2f& force_in, sf::Vector2f arm, const forcesphere& area);

	operator polygon() const { return poly; }

	//implement later:
	/*void addImpulse(const sf::Vector2f& impulse)
	{

	}

	void addImpulse(const sf::Vector2f& iDirection, const float& iStrength)
	{

	}*/

	void update(const float& elapsedTime);

private:
	void scaleArm(sf::Vector2f& arm);

	//fuction that check line vs edge collision: here or the polygon?

	//void move(const sf::Vector2f& v)
	//{
	//	//std::cout << "it behaves like moving center of mass!\n";
	//	prop.position = v + getPosition();
	//	setPosition(prop.position);
	//}

	//void rotate(const float& a)
	//{
	//	for (int v = 0; v < getPointCount(); v++)
	//		setPoint(v, math::rotate(getPoint(v), a));
	//}
};