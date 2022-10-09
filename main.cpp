#include <iostream>
#include "gameVariables.h"
#include "ninjamath.h"
#include "line.h"
#include "shapes.h"
#include "physics.h"
#include "rigidBody.h"

#include "debug.h"


void addForceToClosest(rigidBody* rb, const sf::Vector2f& mPos, bool& should)
{
	static float forceStr = 150.f;
	sf::Vector2f position = rb->poly.getPosition();

	//debug --> draw a line to the closest:
	line toCenter(sf::Color::Green);
	toCenter.setstart(mPos);
	toCenter.setend(position);

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
	//sf::Vector2f forceDirection = {0.0f, -1.0f};
	sf::Vector2f forceDirection = math::normalize(toVertex.end - toVertex.start);

	line toArm(p.getPosition(), p.getPoint(vI) + p.getPosition(), sf::Color::Cyan);
	if (should)
	{
		rb->addForce(forceDirection, forceStr, arm, 0);
		should = 0;
		//forceStr += 10.0f;
	}

	toCenter.draw(window);
	toVertex.draw(window);
	//toArm.draw(window, 1);
}



int main()
{
	//==============================BLADE CODE==============================
	line cut;
	bool hasStart = 0;
	//==============================BLADE CODE==============================

	//===============================POLYGON CODE=============================
	std::vector<rigidBody> shapes;

	float rotation = 0.0f;
	rectangle r1(200, properties(
		sf::Vector2f(wi / 2 - 250 , hi / 2 - 50),
		sf::Color(255, 255, 255, 128),
		sf::Color::White,
		-1.0f
		));

	//rotation test(successful):
	//r1.rotate(45.0f);				//[FIXED]	rotate only takes the vertecies as a reference point. It doesn't modify it. It's a problem since on those vertecies we're operating

	/*sf::RectangleShape ghost({100, 100});
	ghost.setFillColor(sf::Color(0, 0, 0, 0));
	ghost.setOutlineColor(sf::Color::Red);
	ghost.setOutlineThickness(-1.0f);*/
	//ghost.setPosition(r1.prop.position);
	//ghost.setOrigin(50.0f, 50.0f);

	rectangle r2(50, 250, properties(
		sf::Vector2f(150, 250),
		sf::Color(1, 255, 1, 128),
		sf::Color::Green,
		-1.0f
	));

	circle c1(55, properties(
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

	
	//convex polygon:
	polygon sth(13, 150, properties(
		sf::Vector2f(wi / 2 - 120, hi / 2 - 290),
		sf::Color(73, 103, 255, 128.0f),
		sf::Color(100, 44, 255),
		-1.f
	));

	//concave polygon:
	/*polygon sth(properties(
		sf::Vector2f(wi / 2 - 120, hi / 2 - 100),
		sf::Color(73, 103, 255, 128.0f),
		sf::Color(100, 44, 255),
		-1.5f),
		{
			{0.0f, 0.0f},
			{200.0f, 0.0f},
			{100.0f, 70.0f},
			{200.0f, 140.0f},
			{0.0f, 140.0f}
		}
	);*/


	//include all the shapes in array:

	shapes.push_back({r1,  2.f});
	shapes.push_back({r2,  1.f});
	shapes.push_back({c1,  1.5f});
	shapes.push_back({hex, 1.f});
	//shapes.push_back({sth, 10});

	//shapes[0].addForce({ 100, -10 });

	//for (auto i : shapes)
	//{
	//	print(i.linearVelocity);
	//	print(i.force);
	//	std::cout << i.angularVelocity << std::endl;
	//	std::cout << i.torque << std::endl;
	//	std::cout << i.mass << std::endl;
	//	logS;
	//}
	//logS;
	//===============================POLYGON CODE=============================
	
	
	//================================TIMING CODE=============================
	sf::Clock timer;
	//================================TIMING CODE=============================
	


	//================================PHYSICS CODE==============================
	physics pengine(shapes);
	bool shouldAddForce = 0;

	//[DEBUG] add forces based one mouse position:
	rigidBody* closest = nullptr;
	float distance = wi * 2;
	float distance_c;
	sf::Vector2f mPos;
	//================================PHYSICS CODE==============================


	line toCenter;

	while (window.isOpen())
	{
		fElapsedTime = timer.getElapsedTime().asMicroseconds() / 1000000.0f;
		//std::cout << fElapsedTime << std::endl;
		timer.restart();
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::EventType::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();

			//maybe find a better way to lock begining of the line:
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				//std::cout << "left pressed!!\n";
				if (!hasStart)
				{
					cut.setstart({ sf::Mouse::getPosition(window) });
					hasStart = 1;
				}
				cut.setend({ sf::Mouse::getPosition(window) });


				//upadates too fast:
				/*while (hasStart < 2)
				{
					line[hasStart].position = { sf::Mouse::getPosition(window) };
					hasStart++;
				}*/

			}
			else
				hasStart = 0;

			//if (e.mouseButton.button == sf::Mouse::Left && e.type == sf::Event::MouseButtonReleased)
			//{
			//	cut.setstart({ -1.0f, -1.0f });
			//	cut.setend({ -1.0f, -1.0f });
			//	//logS;
			//}

			if (e.key.code == sf::Keyboard::Space)
				if (e.type == sf::Event::EventType::KeyReleased)
					shouldAddForce = !shouldAddForce;
		}

		window.clear();

		mPos = { sf::Mouse::getPosition(window) };
		//mPos = sf::Mouse::getPosition();
		//mPos = { (float)mPos.x, (float)mPos.y };

		//first draw shapes:
		distance = wi * 2;
		for (auto& s : pengine.bodies)
		{	
			window.draw(s);
			//toCenter.setstart(sf::Vector2f(0, 0));
			//toCenter.setend(s.getPosition()/* + shapes[0].getOrigin()*/);
			//toCenter.draw(window);
			 
			//ghost.rotate(150 * dElapsedTime * rot);

			//ghost.setPosition(s.getPosition() - s.getOrigin());
			//ghost.setSize(sf::Vector2f(s.getLocalBounds().width, s.getLocalBounds().height));
			//ghost.setOrigin(sf::Vector2f(s.getLocalBounds().width / 2, s.getLocalBounds().height / 2));
			//window.draw(ghost);
			//s.poly.rotate(150 * fElapsedTime * rot);

			//determin closest shape to the mouse cursor:
			distance_c = math::length(s.poly.getPosition() - mPos);
			if (distance_c < distance)
			{
				distance = distance_c;
				closest = &s;
			}
 		}

		//do:
		addForceToClosest(closest, mPos, shouldAddForce);

		/*if (shapes.size() >= 2)
		{
			int i = 0;
			shapes[i].rotate(150 * fElapsedTime * rot);
			ghost.setPosition(shapes[i].getPosition());
			ghost.rotate(150 * fElapsedTime * rot);
			ghost.setSize(sf::Vector2f( shapes[i].getLocalBounds().width, shapes[i].getLocalBounds().height ));
			ghost.setOrigin(sf::Vector2f( shapes[i].getLocalBounds().width / 2, shapes[i].getLocalBounds().height / 2 ));
			window.draw(ghost);

		}*/
			//toCenter.setstart(sf::Vector2f(0, 0));
			//toCenter.setend(shapes[0].getPosition()/* + shapes[0].getOrigin()*/);
		//ghost.rotate(150.0f * dElapsedTime);
		//then on top of the shapes --> draw line:
		cut.draw(window);
		/*ghost.setPosition(0, 0);
		window.draw(ghost);*/
		//rotation += 1.0f * (rotation <= 360) * dElapsedTime;
		//std::cout << rotation << std::endl;

		//[work-around] check collision only if the lines start and end wont change
		if (!hasStart)
			cutShapes(pengine.bodies, cut);

		//simulate physics:
		pengine.simulate();

		//draw debug lines:
		/*for(auto& l : debugLines)
			l.draw(window);*/

		window.display();
	}
}