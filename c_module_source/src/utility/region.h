#pragma once
//#include "utilities.h"
#include "../interfaces/graphics_interface.h"
#include <array>


class region
{
public:
	std::array<std::array<int, 2>, 4> m_vertices;

	region(std::array<std::array<int, 2>, 4> vertices);

	void draw(graphics_interface* gfxprovider);

	void check(std::array <int, 2> point);
};