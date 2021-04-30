#include "irr_debug_draw.h"
#include <iostream>



irr_btDebug::irr_btDebug(irr_gfx* gfx) : gfx{ gfx }
{
	std::cout << "begin" << std::endl;
	m_debugMode = 1;
}

void   irr_btDebug::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
	std::array<float, 6> line;
	line[0] = from.x();
	line[1] = from.y();
	line[2] = from.z();
	line[3] = to.x();
	line[4] = to.y();
	line[5] = to.z();
	gfx->lines.push_back(line);
	/*
	vector3df start{ from.x(),from.y(),from.z() };
	vector3df end{ to.x(),to.y(),to.z() };

	SMaterial m;
	m.Lighting = false;
	m.Thickness = 3.5f;
	gfx->driver->setMaterial(m);
	gfx->driver->setTransform(video::ETS_WORLD, core::matrix4());
	gfx->driver->draw3DLine(start, end, SColor(0, 180, 0, 255));
	*/
}

void   irr_btDebug::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
{
	std::cout << "points" << std::endl;
}

void   irr_btDebug::reportErrorWarning(const char* warningString)
{
	std::cout << warningString << std::endl;
}

void   irr_btDebug::draw3dText(const btVector3& location, const char* textString)
{
	std::cout << textString << std::endl;
}

void   irr_btDebug::setDebugMode(int debugMode)
{
	m_debugMode = debugMode;
}

int      irr_btDebug::getDebugMode() const { return m_debugMode; }
