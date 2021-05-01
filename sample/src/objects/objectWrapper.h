#pragma once
#include <array>
#include <vector>
#include <string>
#include "../external/bPhysics.h"
#include "../external/irrlicht.h"


class worldComposite;

enum direction { up, down, front, back, l_left, l_right, y_left, y_right, neutral };

class objExport
{
public:

	btRigidBody* bt_body;
	IMeshSceneNode* irr_body;
	worldComposite* world;

	virtual void direct(direction dir);
	virtual std::array<float, 7> getTransform_qat();
	virtual std::string getProperties();
	virtual void setTransform_qat(std::array<float, 7> ok);
	virtual void update();

	objExport(btRigidBody* bt_body, IMeshSceneNode* irr_body);
	objExport(btRigidBody* bt_body);
	objExport(worldComposite* world);
	//~objExport();

	//Expose information and controls to python
	//Basic Controls(Up down left right)
	//Position get & sets
	//Data structure for python to interpret
	//Misc. Information (object specific)
};
