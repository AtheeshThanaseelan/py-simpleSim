#pragma once
#include <array>


class debugview
{
public:

	debugview();

	void add_line(std::array<float, 6> line);

	void clear_lines();

	void update();

	void setCamPos(std::array<float,3> pos);

	void setCamAng(std::array<float,3> pos);

};