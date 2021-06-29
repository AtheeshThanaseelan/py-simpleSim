#include <iostream>
#include <vector>
#include <array>
#include "export_btDebug.h"


std::vector<float> export_btDebug::getLines()
{
	return lines;
}

void export_btDebug::update()
{
	lines.clear();
}

void export_btDebug::add_line(std::array<float, 6> line)
{
	//lines.push_back(line);
}

export_btDebug::export_btDebug()
{
	m_debugMode = 1;
}

void   export_btDebug::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
	lines.push_back(from.x());
	lines.push_back(from.y());
	lines.push_back(from.z());
	lines.push_back(to.x());
	lines.push_back(to.y());
	lines.push_back(to.z());
	std::cout<<lines.size()<<std::endl;
	//std::cout<<"poh\n";
}

void   export_btDebug::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) {}

void   export_btDebug::reportErrorWarning(const char* warningString) {}

void   export_btDebug::draw3dText(const btVector3& location, const char* textString) {}

void   export_btDebug::setDebugMode(int debugMode) {	m_debugMode = debugMode;}

int    export_btDebug::getDebugMode() const { return m_debugMode; }


