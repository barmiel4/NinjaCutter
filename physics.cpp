#include "physics.h"
#include "rigidBody.h"
#include "debug.h"

//moved to the polygon code
//test each edge of given polygon with a given line to check if it fully penetrates

//std::optional<std::vector<vertecies>> checkEdges(const rigidBody& s, line cut)
//{
//	line edge;
//	cut.start -= (s.getPosition());
//	cut.end   -= (s.getPosition());
//	std::vector<vertecies> shapes(2);
//
//
//	bool side = 0;			//begin with shape 0
//	char changes = 0;
//	for (int v = 0; v < s.getPointCount(); v++)
//	{
//		edge.setstart(s.getPoint(v));
//		edge.setend(s.getPoint((v + 1) % s.getPointCount()));
//
//		auto point = cut.linevline_2(edge);
//		if (point)
//		{
//			changes++;
//			shapes[side].push_back(point.value());
//			side = !side;								//switch sides
//			shapes[side].push_back(point.value());
//		}
//		shapes[side].push_back(s.getPoint((v + 1) % s.getPointCount()));
//	}
//	if (changes == 2)
//		return shapes;
//	return std::nullopt;
//}

//go through the array of all polygon in the scene, check collision with given line and cut them into pieces if it occured
void cutShapes(std::vector<rigidBody>& bodies, line& cut)
{
	auto it = bodies.begin();

	float offset = 5.0f;

	//=========================================================LINE CODE=======================================================================
	sf::Vector2f lineV = cut.end - cut.start;
	sf::Vector2f direction;
	//=========================================================LINE CODE=======================================================================

	sf::Vector2f poi1;		//first  point of impact
	sf::Vector2f poi2;		//second point of impact
	sf::Vector2f forceSpot;
	//sf::Vector2f arm;
	line armVector(sf::Color::Yellow);
	line newEdge(sf::Color::Cyan);
	float r = 0.0f;
	float minr;
	float maxr;
	float strength = 150.0f;
	sf::Vector2f force;


	//scale force for debug:
	//strength *= 0.05f;

	while (it != bodies.end())
	{
		auto verts = it->poly.checkEdges(cut);
		if (verts.has_value())
		{
			polygon p1;				//side 0
			polygon p2;				//side 1


			p1 = polygon(it->poly.prop, verts.value()[0]);
			//p1.setFillColor(sf::Color::Red);						//DEBUG --> highlight with red new part containing Point A(top-left)

			p2 = polygon(it->poly.prop, verts.value()[1]);
			//p2.setFillColor(sf::Color::Green);					//DEBUG -->	highlight with green the other half of divieded polygon

			direction = math::normalizedRejection((it->poly.getPosition() + it->poly.getPoint(0)) - cut.start, lineV);		//construct a direction vector perpendicular to the line, pointing in direction of first																										point of divided shape
				
			//calculate cut spots:
			poi1 = verts.value()[1][0];
			poi2 = verts.value()[1][verts.value()[1].size() - 1];

			//minr = (math::dotProduct(poi2 - poi1, cut.end - cut.start) > 0.0f ? 0.0f : 0.5f);		//check in which direction was the cut made and adjust min r value
			//maxr = minr + 0.5f;
			////r = 0.2f + minr;		//random float between minr and maxr
			//r = 1.0f;		
			//forceSpot = poi2 + r * (poi1 - poi2);

			//pick the point closest to the cutting line's begining:
			sf::Vector2f closestToStart = (math::dotProduct(poi2 - poi1, cut.end - cut.start) < 0.0f ? poi2 : poi1);	
			
			//direction *= 5.0f;
			p1.move(direction);
			p2.move(-direction);

			//direction *= strength;

			//make it so new weigth is calculated automatically:
			rigidBody rb1(p1, 1.0f);
			rigidBody rb2(p2, 1.0f);

			closestToStart += it->poly.getPosition();
			line toPoint({0, 0}, closestToStart, sf::Color::Blue, 1);
			debugLines.push_back(toPoint);

			//experimental version(direction of the line and with 'closest to begin'):
			direction = math::normalize(cut.end - cut.start);
			direction *= strength;
			//std::cout << std::endl << sqrt(math::dotProduct(direction, direction)) << std::endl;

			it = bodies.erase(it);							//delete shape that was cut
			it = bodies.emplace(it, rb1);					//add two new chunks that were created and apply forces to them
			it->addForce(direction, closestToStart);
			it = bodies.emplace(it, rb2);
			it->addForce(direction, closestToStart);
		}
		else
			++it;
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
	for (auto i : bodies)
	{
		print(i.linearVelocity);
		print(i.force);
		std::cout << "angularVelocity = " << i.angularVelocity << std::endl;
		std::cout << "torque = " << i.torque << std::endl;
		std::cout << "mass = " << i.mass << "kg\n";
		logS;
	}
}

