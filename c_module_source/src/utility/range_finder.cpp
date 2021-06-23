#include "range_finder.h"
#include "../drivers/bPhysics/bPhysics.h"
#include <iostream>
range_finder::range_finder(std::array<float, 3> from_points, std::array<float, 3> to_points,)
	:m_from_points{ from_points }, m_to_points{to_points}
{

}

void range_finder::update()
{
	/*
	if (m_attachedBody != nullptr)
	{
		m_attachedBody->getWorldTransform().getOrigin();
	}
	*/
	btVector3 from(m_from_points[0], m_from_points[1], m_from_points[2]);
	btVector3 to(m_to_points[0], m_to_points[1], m_to_points[2]);
	
	vector3df start{ m_from_points[0], m_from_points[1], m_from_points[2] };
	vector3df end{ m_to_points[0], m_to_points[1], m_to_points[2] };


	SMaterial m;
	m.Lighting = false;
	m.Thickness = 3.f;
	m_world->m_gfx->driver->setMaterial(m);
	m_world->m_gfx->driver->setTransform(video::ETS_WORLD, core::matrix4());
	m_world->m_gfx->driver->draw3DLine(start, end, SColor(180, 50, 0, 255));

	btCollisionWorld::ClosestRayResultCallback  closestResults(from, to);
	m_world->m_engine->dynamicsWorld->rayTest(from, to, closestResults);
	if (closestResults.hasHit())
	{
		std::cout << "---ok----" << std::endl;
		std::cout << closestResults.m_hitPointWorld.getX() << std::endl;
		std::cout << closestResults.m_hitPointWorld.getY() << std::endl;
		std::cout << closestResults.m_hitPointWorld.getZ() << std::endl;

	}
}


