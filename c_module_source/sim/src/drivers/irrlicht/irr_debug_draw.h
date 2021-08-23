#pragma once
#include <array>
#include <bullet/btBulletDynamicsCommon.h>
#include "../../interfaces/graphics_interface.h"


class irr_btDebug : public btIDebugDraw, public graphics_interface
{
	int m_debugMode;

public:
	irr_btDebug();

	void refresh();

	void   drawLine(const btVector3& from, const btVector3& to, const btVector3& color);

	void   drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color);

	void   reportErrorWarning(const char* warningString);

	void   draw3dText(const btVector3& location, const char* textString);

	void   setDebugMode(int debugMode);

	int      getDebugMode() const;

	void add_line(std::array<float, 6> line);
    void update();

};