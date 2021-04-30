#include "utilities.h"
#include "irr_debug_draw.h"

worldComposite::worldComposite(irr_inp* inp, irr_gfx* gfx, bPhysics* engine) :m_inp(inp), m_gfx(gfx), m_engine(engine), temp(0) 
{
	if (gfx != nullptr)
	{
		irr_btDebug* drawer = new irr_btDebug(gfx);
		engine->dynamicsWorld->setDebugDrawer(drawer);
	}
};

worldComposite::worldComposite(bPhysics* engine) :m_engine(engine), temp(0){};

void worldComposite::addObject(objExport* newObj)
{
	objects.push_back(newObj);
	newObj->world = this;
}

void worldComposite::swapGFX(irr_gfx* gfx)
{
	m_gfx = gfx;
	if (gfx != nullptr)
	{
		irr_btDebug* drawer = new irr_btDebug(gfx);
		m_engine->dynamicsWorld->setDebugDrawer(drawer);
	}
}

bool worldComposite::update()
{
	bool success = true;
	if (m_gfx != nullptr)
	{
		m_engine->dynamicsWorld->debugDrawWorld();

	}

	m_engine->stepPhysics();

	for (objExport* n : objects) {
		n->update();
	}

	if(m_gfx != nullptr)
	{
		success = m_gfx->update();
	}

	return success;
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