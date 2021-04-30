#pragma once
#include "../objects/objectWrapper.h"

class worldComposite
{
public:
	irr_inp* m_inp;
	irr_gfx* m_gfx;
	bPhysics* m_engine;

	std::vector<objExport*> objects;
	int temp;

	worldComposite(irr_inp* inp, irr_gfx* gfx, bPhysics* engine);
	worldComposite(bPhysics* engine);

	void addObject(objExport* newObj);
	void swapGFX(irr_gfx* gfx);
	bool update();

};

class world_timer
{
public:
	float real_time;
	float time;
	int steps = 0;
	int sub_times = 1;

	//World advanced by 1/60sec, every 3 steps, time advances by 0.05sec. 

	//Advance by regular math & precise steps to account for variable step time

	world_timer(float time = 0);
	void advance();
	float get_time();
};