#include "Physics/physics.h"
#include "Physics/rigidBody.h"
#include "debug.h"

//checkEdges moved to the polygon code
//test each edge of given polygon with a given line to check if it fully penetrates


//go through the array of all polygon in the scene, check collision with given line and cut them into pieces if it occured
void cutShapes(std::vector<rigidBody>& bodies, line& cut)
{
#ifdef DETAILED_DEBUG
	static uint32_t callCount = 0;
	std::cout << "call count = " << ++callCount << std::endl;
#endif

	float offset = 5.0f;

	//=========================================================LINE CODE=======================================================================
	sf::Vector2f lineV = cut.end - cut.start;
	sf::Vector2f direction;
	//=========================================================LINE CODE=======================================================================

	sf::Vector2f poi1;		//first  point of impact
	sf::Vector2f poi2;		//second point of impact
	sf::Vector2f forceSpot;
	float strength = 25.f;
	sf::Vector2f force;

	auto it = bodies.begin();

	while (it != bodies.end())
	{
		//auto verts = it->poly.checkEdges(cut);
		auto verts = it->poly / cut;			//does same thing as above, but with operator overloading

		if (verts)
		{
			polygon p1;				//side 0
			polygon p2;				//side 1

			p1 = polygon(it->poly.prop, verts.value()[0]);
			//p1.setFillColor(sf::Color::Red);						//DEBUG --> highlight with red new part containing Point A(top-left)

			p2 = polygon(it->poly.prop, verts.value()[1]);
			//p2.setFillColor(sf::Color::Green);					//DEBUG -->	highlight with green the other half of divieded polygon
							
			//calculate cut spots:
			poi1 = verts.value()[1][0];
			poi2 = verts.value()[1][verts.value()[1].size() - 1];

			direction = math::normalizedRejection((it->poly.getPosition() + it->poly.getPoint(0)) - cut.start, lineV);		//construct a direction vector perpendicular to the line, pointing in direction of first																										point of divided shape
			direction *= strength;

			rigidBody rb1(p1, .5f);
			rigidBody rb2(p2, .5f);

			//pick the point closest to the cutting line's begining:
			sf::Vector2f furthestToStart = (math::dotProduct(poi2 - poi1, cut.end - cut.start) > 0.0f ? poi2 : poi1);	
			furthestToStart += it->poly.getPosition();

#ifdef VIS_DEBUG
			line toPoint({0, 0}, furthestToStart, sf::Color::Blue, 1);
			debugLines.push_back(toPoint);
#endif
			//delete shape that was cut
			it = bodies.erase(it);
			//add two new chunks that were created and apply forces to them
			it = bodies.emplace(it, rb1);
			it->addForce(direction, furthestToStart);
			it = bodies.emplace(it, rb2);
			it->addForce(-direction, furthestToStart);
			it += 2;	//iterator is pointing to the last added body(which lies before the first body), since 2 bodies are added iterator must be offset by 2 so that same shapes arent cut infinite times
		}
		else
			it++;
	}

	//reset line:
	cut.resetLine();
}

physics::physics(const std::vector<rigidBody>& newbodies)
	: bodies(newbodies)		{}

void physics::simulate()
{
	for (rigidBody& rb : bodies)
		rb.update(fElapsedTime);
}

void physics::addBody(const rigidBody& newbody)
{
	bodies.push_back(newbody);
}

void physics::addBodies(const std::vector<rigidBody>& newbodies)
{
	//concatonate two vectors by moving newbodies not copying them.
	bodies.insert(bodies.end(),
		std::make_move_iterator(newbodies.begin()),
		std::make_move_iterator(newbodies.end()));
}

void physics::addPolygonsAsBodies(const std::vector<polygon>& newbodies)
{
	fInfo("addPolygonAsBodies", "physics struct", "address the implementation");
	//concatonate two vectors by moving newbodies not copying them.
	bodies.insert(bodies.end(),
		std::make_move_iterator(newbodies.begin()),
		std::make_move_iterator(newbodies.end()));
}

void physics::printBodies()
{
	for (const auto& i : bodies)
	{
		print(i.linearVelocity);
		print(i.force);
		std::cout << "angularVelocity = " << i.angularVelocity << std::endl;
		std::cout << "torque = " << i.torque << std::endl;
		std::cout << "mass = " << i.mass << "kg\n";
		logS;
	}
}

