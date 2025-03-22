#include <iostream>
#include "gameVariables.h"
#include "ninjamath.h"
#include "line.h"
#include "shapes.h"
#include "physics.h"
#include "rigidBody.h"

//#include <Windows.h>

#include "debug.h"



void addForceToClosest(rigidBody* rb, const sf::Vector2f& mPos, bool& should)
{
	static float forceStr = 150.f;
	sf::Vector2f position = rb->poly.getPosition();

	//debug --> draw a line to the closest shape:
#ifdef VIS_DEBUG

	line toCenter(sf::Color::Green);

	toCenter.setstart(mPos);
	toCenter.setend(position);

	toCenter.draw(window);
#endif // VIS_DEBUG

	line toVertex(sf::Color::Red);
	toVertex.setstart(mPos);

	polygon p = rb->poly;
	float distance = wi;
	float distance_c;
	int vI = 0;
	for (int v = 0; v < p.getPointCount(); v++)
	{
		distance_c = math::length(mPos - p.getPoint(v) - p.getPosition());
		if (distance > distance_c)
		{
			distance = distance_c;
			vI = v;
		}
	}
	toVertex.setend(p.getPoint(vI) + p.getPosition());

	sf::Vector2f arm = p.getPoint(vI);
	sf::Vector2f forceDirection = math::normalize(toVertex.end - toVertex.start);

	line toArm(p.getPosition(), p.getPoint(vI) + p.getPosition(), sf::Color::Cyan);
	if (should)
	{
		rb->addForce(forceDirection, forceStr, arm, 0);
		should = 0;
	}

	//debug -> draw a line to closest vertex
#ifdef VIS_DEBUG

	toVertex.draw(window);

#endif 
}



int main()
{
	//==============================BLADE CODE==============================
	line cut;
	bool hasStart = 0;
	//==============================BLADE CODE==============================

	//===============================POLYGON CODE=============================
	std::vector<rigidBody> shapes;

	rectangle r1(200, properties(
		sf::Vector2f(wi / 2 - 250 , hi / 2 - 50),
		sf::Color(255, 255, 255, 128),
		sf::Color::White,
		-1.0f
		));

	rectangle r2(50, 250, properties(
		sf::Vector2f(150, 250),
		sf::Color(1, 255, 1, 128),
		sf::Color::Green,
		-1.0f
	));

	circle c1(70, properties(
		sf::Vector2f(600, 250),
		sf::Color(1, 1, 255, 128),
		sf::Color::Blue,
		-1.0f
	));


	polygon hex(6, 55, properties(
		sf::Vector2f(850, 250),
		sf::Color(1, 128, 255, 128),
		sf::Color::Magenta,
		-1.0f
	));

	//add all the shapes in array:
	shapes.push_back({r1,  2.f});
	shapes.push_back({r2,  1.f});
	shapes.push_back({c1,  1.5f});
	shapes.push_back({hex, 1.f});

	//===============================POLYGON CODE=============================
	
	
	//================================TIMING CODE=============================
	sf::Clock timer;
	//================================TIMING CODE=============================

	//================================PHYSICS CODE==============================
	physics pengine(shapes);
	bool shouldAddForce = 0;

	//[DEBUG] add forces based on mouse position:
#ifdef _DEBUG

	rigidBody* closest = nullptr;
	float distance = wi * 2;
	float distance_c;

#endif // _DEBUG

	sf::Vector2f mousePos;
	//================================PHYSICS CODE==============================


	line toCenter;

	while (window.isOpen())
	{
		fElapsedTime = timer.getElapsedTime().asMicroseconds() / 1000000.0f;
		while (fElapsedTime < LOCKED_FPS) { fElapsedTime = timer.getElapsedTime().asMicroseconds() / 1000000.0f; }

		timer.restart();
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::EventType::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (!hasStart)
				{
					cut.setstart({ sf::Mouse::getPosition(window) });
					hasStart = 1;
				}
				cut.setend({ sf::Mouse::getPosition(window) });

			}
			else if (hasStart)
			{
				cutShapes(pengine.bodies, cut);
				hasStart = 0;
			}

			if (e.key.code == sf::Keyboard::Space)
				if (e.type == sf::Event::EventType::KeyReleased)
					shouldAddForce = !shouldAddForce;
		}

		window.clear();

		mousePos = { sf::Mouse::getPosition(window) };

		distance = wi * 2;
		
		//first draw shapes:
		for (auto& s : pengine.bodies)
		{	
			window.draw(s);

#ifdef _DEBUG

			//determine closest shape to the mouse cursor:
			distance_c = math::length(s.poly.getPosition() - mousePos);
			if (distance_c < distance)
			{
				distance = distance_c;
				closest = &s;
			}

#endif // _DEBUG
 		}

#ifdef _DEBUG

		if (closest)
			addForceToClosest(closest, mousePos, shouldAddForce);

#endif // _DEBUG

		//then on top of the shapes --> draw line:
		cut.draw(window);

		//simulate physics:
		pengine.simulate();

#ifdef VIS_DEBUG
		//draw debug lines:
		for(const auto& l : debugLines)
			l.draw(window);
#endif
		window.display();
	}
}