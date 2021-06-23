#pragma once
//#include "../objects/objectWrapper.h"
//#include "utilities.h"
#include <array>

class range_finder
{
public:
	//worldComposite* m_world;
	//btRigidBody* m_attachedBody;
	std::array<float, 3> m_from_points{ -3,0,0 };
	std::array<float, 3> m_to_points{ 1,0,0 };

	range_finder(std::array<float, 3> from_points,std::array<float, 3> to_points);
	void update();
	//std::array<float,3> getResults();

};