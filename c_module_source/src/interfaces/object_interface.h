#pragma once
#include <array>
#include <string>

enum direction { up, down, front, back, l_left, l_right, y_left, y_right, neutral };

class object_interface
{
    public:

	virtual void direct(direction dir) = 0;
	virtual std::array<float, 7> getTransform_qat() = 0;
	virtual std::string getProperties() = 0;
	virtual void setTransform_qat(std::array<float, 7> transform_qat) = 0;
	virtual void update() = 0;

	//object_interface();
	//~objExport();

	//Expose information and controls to python
	//Basic Controls(Up down left right)
	//Position get & sets
	//Data structure for python to interpret
	//Misc. Information (object specific)

};