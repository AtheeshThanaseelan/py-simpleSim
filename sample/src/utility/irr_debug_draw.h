#pragma once
#include "../objects/objectWrapper.h"
#include "utilities.h"
#include <array>

class irr_btDebug : public btIDebugDraw
{
	irr_gfx* gfx;
	int m_debugMode;
public:
	irr_btDebug(irr_gfx* gfx);

	void   drawLine(const btVector3& from, const btVector3& to, const btVector3& color);

	void   drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color);

	void   reportErrorWarning(const char* warningString);

	void   draw3dText(const btVector3& location, const char* textString);

	void   setDebugMode(int debugMode);

	int      getDebugMode() const;

};