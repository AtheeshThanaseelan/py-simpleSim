#include "irr_debug_draw.h"
#include <irrlicht/irrlicht.h>
#include <iostream>
#include <vector>
#include <array>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

std::vector<std::array<float,6>> lines;
	IrrlichtDevice* device;
	IVideoDriver* driver;
	ISceneManager* scenemgr;

class irr_inp : public IEventReceiver
{
	public:
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
	irr_inp()
	{
		for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
			KeyIsDown[i] = false;
	}

	bool OnEvent(const SEvent& event)
	{
		// Remember whether each key is down or up
		if (event.EventType == irr::EET_KEY_INPUT_EVENT)
			KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

		return false;
	}

	bool IsKeyDown(EKEY_CODE keyCode) const
	{
		return KeyIsDown[keyCode];
	}
	/*
	void clear(EKEY_CODE keyCode);
	*/
};

void irr_btDebug::add_line(std::array<float, 6> line)
{
	lines.push_back(line);
}

void irr_btDebug::update()
{
	driver->beginScene(true, true, video::SColor(180, 0, 0, 255));
	
	for (long unsigned int i=0; i < lines.size(); i++)
	{
		vector3df start{ lines.at(i)[0],lines.at(i)[1],lines.at(i)[2] };
		vector3df end{ lines.at(i)[3],lines.at(i)[4],lines.at(i)[5] };

		SMaterial m;
		m.Lighting = false;
		m.Thickness = 3.5f;
		driver->setMaterial(m);
		driver->setTransform(video::ETS_WORLD, core::matrix4());
		driver->draw3DLine(start, end, SColor(0, 180, 0, 255));
	}
	lines.clear();
	
	scenemgr->drawAll();

	driver->endScene();

	device->run();
}

irr_btDebug::irr_btDebug()
{
	IEventReceiver* ok = new irr_inp();
	device = createDevice(video::EDT_BURNINGSVIDEO,
		dimension2d<u32>(800, 600), 32, false, false, false,ok);
	driver = device->getVideoDriver();
	scenemgr = device->getSceneManager();
	//guienv = device->getGUIEnvironment();
	device->setWindowCaption(L"Sample Program");
	//env = device->getGUIEnvironment();

	ICameraSceneNode* cameraNode;
	cameraNode = scenemgr->addCameraSceneNodeFPS(NULL, 20.0f, 0.02f);
	cameraNode->setPosition(vector3df(0, 10, -30));

	std::cout << "begin" << std::endl;
	m_debugMode = 1;
}

void irr_btDebug::refresh()
{
	//this->update();
	driver->beginScene(true, true, video::SColor(180, 0, 0, 255));
	
	for (long unsigned int i=0; i < lines.size(); i++)
	{
		vector3df start{ lines.at(i)[0],lines.at(i)[1],lines.at(i)[2] };
		vector3df end{ lines.at(i)[3],lines.at(i)[4],lines.at(i)[5] };

		SMaterial m;
		m.Lighting = false;
		m.Thickness = 3.5f;
		driver->setMaterial(m);
		driver->setTransform(video::ETS_WORLD, core::matrix4());
		driver->draw3DLine(start, end, SColor(0, 180, 0, 255));
	}
	lines.clear();
	
	scenemgr->drawAll();

	driver->endScene();

	device->run();
}

void   irr_btDebug::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
	std::array<float, 6> line;
	line[0] = from.x();
	line[1] = from.y();
	line[2] = from.z();
	line[3] = to.x();
	line[4] = to.y();
	line[5] = to.z();
	lines.push_back(line);
}

void   irr_btDebug::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
{
	std::cout << "points" << std::endl;
}

void   irr_btDebug::reportErrorWarning(const char* warningString)
{
	std::cout << warningString << std::endl;
}

void   irr_btDebug::draw3dText(const btVector3& location, const char* textString)
{
	std::cout << textString << std::endl;
}

void   irr_btDebug::setDebugMode(int debugMode)
{
	m_debugMode = debugMode;
}

int    irr_btDebug::getDebugMode() const { return m_debugMode; }


