#include "irrlicht.h"
#include <array>
irr_gfx::irr_gfx(IEventReceiver* ok)
{
	device = createDevice(video::EDT_OPENGL,
		dimension2d<u32>(800, 600), 32, false, false, true, ok);
	driver = device->getVideoDriver();
	scenemgr = device->getSceneManager();
	//guienv = device->getGUIEnvironment();
	device->setWindowCaption(L"Sample Program");
	//env = device->getGUIEnvironment();

	ICameraSceneNode* cameraNode;
	cameraNode = scenemgr->addCameraSceneNodeFPS(NULL, 20.0f, 0.02f);
	cameraNode->setPosition(vector3df(0, 10, -70));

	//Make plane
	IAnimatedMesh* hillPlaneMesh = scenemgr->addHillPlaneMesh("base",
		core::dimension2d<f32>(10, 10),
		core::dimension2d<u32>(100, 100), 0, 0,
		core::dimension2d<f32>(0, 0),
		core::dimension2d<f32>(100, 100));

	ISceneNode* irr_planeNode = scenemgr->addAnimatedMeshSceneNode(hillPlaneMesh);
	irr_planeNode->setMaterialTexture(0, driver->getTexture("../textures/ground.jpg"));
	irr_planeNode->setMaterialFlag(video::EMF_LIGHTING, false);
	irr_planeNode->setPosition(core::vector3df(0, -5, 0));

}

irr_gfx::~irr_gfx()
{
	device->closeDevice();
	device->run();
	device->drop();
	//delete device;
}

void irr_gfx::update()
{
	driver->beginScene(true, true, video::SColor(180, 0, 0, 255));
	scenemgr->drawAll();
	driver->endScene();
}

IMeshSceneNode* irr_gfx::getBox()
{
	std::array<float, 3> size{ 1,1,1 };
	IMeshSceneNode* cubeNode = scenemgr->addCubeSceneNode(1.0f, 0, 0, vector3df(0, 0, 0), vector3df(0, 0, 0), vector3df(size[0] * 2, size[1] * 2, size[2] * 2));
	cubeNode->setMaterialType(EMT_SOLID);
	cubeNode->setMaterialTexture(0, driver->getTexture("../textures/box.jpg"));
	cubeNode->setMaterialFlag(video::EMF_LIGHTING, false);
	cubeNode->setVisible(true);
	return cubeNode;
}

bool irr_inp::OnEvent(const SEvent& event)
{
	// Remember whether each key is down or up
	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

	return false;
}

bool irr_inp::IsKeyDown(EKEY_CODE keyCode) const
{
	return KeyIsDown[keyCode];
}
/*
void clear(EKEY_CODE keyCode)
{
	KeyIsDown[keyCode] = false;
}
*/

irr_inp::irr_inp()
{
	for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
		KeyIsDown[i] = false;
}