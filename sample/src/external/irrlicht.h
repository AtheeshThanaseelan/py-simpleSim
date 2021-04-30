#pragma once
#include <irrlicht/irrlicht.h>
#include <array>
#include <vector>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


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

class irr_gfx
{
public:
	IrrlichtDevice* device;
	IVideoDriver* driver;
	ISceneManager* scenemgr;
	irr_inp* m_inp;

	std::vector<std::array<float,6>> lines;

	irr_gfx(irr_inp* keys);

	~irr_gfx();

	IMeshSceneNode* getBox(std::array<float, 3> size = { 1,1,1 }, std::array<float, 3> pos = { 0,0,0 });
	void add_line(std::array<float, 6> line);
	bool update();
};
