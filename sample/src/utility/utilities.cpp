#include "utilities.h"

worldComposite::worldComposite(irr_inp* inp, irr_gfx* gfx, bPhysics* engine) :m_inp(inp), m_gfx(gfx), m_engine(engine), temp(0) {};


void worldComposite::addObject(objExport* newObj)
{
	objects.push_back(newObj);
	newObj->world = this;
}

void worldComposite::update()
{
	m_gfx->update();
	m_engine->stepPhysics();
	m_gfx->device->run();

	for (objExport* n : objects) {
		n->update();
	}

}

world_timer::world_timer(float time) :time{ time }, real_time{ time } {}
void world_timer::advance()
{
	steps++;
	if (sub_times >= 3)
	{
		sub_times = 1;
		time += 0.05;
	}
	else
	{
		sub_times++;
	}
	real_time += 1.f / 60.f;
}
float world_timer::get_time()
{
	return real_time;
}