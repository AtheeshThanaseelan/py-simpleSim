/*
Bullet Continuous Collision Detection and Physics Library
Copyright (c) 2003-2015 Erwin Coumans  http://continuousphysics.com/Bullet/
This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it freely,
subject to the following restrictions:
1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

/*
* This file is NOT by the Bullet Physics development team
*
* It is ALTERED
*/
#pragma once
#include "..\base_utils.h"
#include "..\object_utils.h"
class wheel_obj : public main_obj
{
public:
	float wheelRadius = 0.5f;
	float wheelWidth = 0.4f;

	btRigidBody* m_carChassis;
	ISceneNode* irr_body;

	btCompoundShape* compound;

	world* obj_world;

	btCollisionShape* m_wheelShape;
	btHinge2Constraint* pHingeStore[4];
	btRigidBody* pBodyB[4];
	ISceneNode* pNode[4];

	wheel_obj(world* world);
	~wheel_obj();
	void forward();
	void stop();
};
