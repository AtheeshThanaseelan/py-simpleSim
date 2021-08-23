//enum direction { up, down, front, back, l_left, l_right, y_left, y_right, neutral };
#pragma once
#include <array>
#include <vector>
#include <string>
#include "bPhysics.h"
#include "../../interfaces/object_interface.h"

class bP_obj: public object_interface
{
public:

	btRigidBody* bt_body;
	void direct(direction dir){};
	std::array<float, 7> getTransform_qat()
    {
        std::array<float, 7> transform_qat{};
        transform_qat[0] = bt_body->getWorldTransform().getRotation().getW();
        transform_qat[1] = bt_body->getWorldTransform().getRotation().getX();
        transform_qat[2] = bt_body->getWorldTransform().getRotation().getY();
        transform_qat[3] = bt_body->getWorldTransform().getRotation().getZ();

        transform_qat[4] = bt_body->getWorldTransform().getOrigin().getX();
        transform_qat[5] = bt_body->getWorldTransform().getOrigin().getY();
        transform_qat[6] = bt_body->getWorldTransform().getOrigin().getZ();
        return transform_qat;
    }
	std::string getProperties()
    {
        std::string ok = "";

        return ok;
    }
    void setProperties(std::string props)
    {
        if(props == "nograv")
        {
            bt_body->setGravity(btVector3(0,0,0));
        }
        if(props == "static")
        {
            bt_body->setMassProps(btScalar(0),btVector3(0,0,0));
        }
    }
	void setTransform_qat(std::array<float, 7> transform_qat)
    {
        btQuaternion quat;
        quat.setW(transform_qat[0]);
        quat.setX(transform_qat[1]);
        quat.setY(transform_qat[2]);
        quat.setZ(transform_qat[3]);

        btVector3 origin;
        origin.setX(transform_qat[4]);
        origin.setY(transform_qat[5]);
        origin.setZ(transform_qat[6]);

        btTransform trans;
        trans.setRotation(quat);
        trans.setOrigin(origin);

        bt_body->setWorldTransform(trans);
    }
	void update(){};

};
