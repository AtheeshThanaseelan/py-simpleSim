#pragma once
#include <irrlicht/irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class irr_gfx
{
public:
	IrrlichtDevice* device;
	IVideoDriver* driver;
	ISceneManager* scenemgr;

	irr_gfx(IEventReceiver* ok);

	~irr_gfx();

	IMeshSceneNode* getBox();

	void update();
};

class irr_inp : public IEventReceiver
{
public:
	bool KeyIsDown[KEY_KEY_CODES_COUNT];

	bool OnEvent(const SEvent& event);

	bool IsKeyDown(EKEY_CODE keyCode) const;
	/*
	void clear(EKEY_CODE keyCode);
	*/

	irr_inp();
};