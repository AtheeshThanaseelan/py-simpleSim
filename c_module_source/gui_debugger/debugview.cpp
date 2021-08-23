#include "debugview.h"
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

std::vector<std::array<float, 6>> lines;
IrrlichtDevice* device;
IVideoDriver* driver;
ISceneManager* scenemgr;
ICameraSceneNode* cameraNode;

void debugview::setCamAng(std::array<float,3> pos)
{
	cameraNode->setRotation(vector3df(pos[0],pos[1],pos[2]));
}

void debugview::setCamPos(std::array<float,3> pos)
{
	cameraNode->setPosition(vector3df(pos[0],pos[1],pos[2]));
}


void debugview::add_line(std::array<float, 6> line)
{
	lines.push_back(line);
}

void debugview::update()
{
	driver->beginScene(true, true, video::SColor(180, 0, 0, 255));

	for (long unsigned int i = 0; i < lines.size(); i++)
	{
		vector3df start{ lines.at(i)[0],lines.at(i)[1],lines.at(i)[2] };
		vector3df end{ lines.at(i)[3],lines.at(i)[4],lines.at(i)[5] };

		SMaterial m;
		m.Lighting = false;
		m.Thickness = 7.5f;
		driver->setMaterial(m);
		driver->setTransform(video::ETS_WORLD, core::matrix4());
		driver->draw3DLine(start, end, SColor(0, 180, 0, 255));
	}

	scenemgr->drawAll();

	driver->endScene();

	device->run();
}

void debugview::clear_lines()
{
	lines.clear();
}

debugview::debugview()
{
	device = createDevice(video::EDT_BURNINGSVIDEO,
		dimension2d<u32>(800, 600), 32, false, false, false);
	driver = device->getVideoDriver();
	scenemgr = device->getSceneManager();
	//guienv = device->getGUIEnvironment();
	device->setWindowCaption(L"Sample Program");
	//env = device->getGUIEnvironment();

	cameraNode = scenemgr->addCameraSceneNode(NULL);
	cameraNode->setPosition(vector3df(0, 10, -30));

	std::cout << "begin" << std::endl;
}

int main() 
{
	debugview* d = new debugview();

}