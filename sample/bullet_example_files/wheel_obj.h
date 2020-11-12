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

#include "..\base_utils.h"

class wheel_obj 
{
public:
	float wheelRadius = 0.5f;
	float wheelWidth = 0.4f;

	btRigidBody* m_carChassis;

	int m_wheelInstances[4];

	class btTriangleIndexVertexArray* m_indexVertexArrays;

	btVector3* m_vertices;

	btCollisionShape* m_wheelShape;

	wheel_obj(world* world);

	void run(key_controller controller);

	btHinge2Constraint* pHingeStore[4];
};
