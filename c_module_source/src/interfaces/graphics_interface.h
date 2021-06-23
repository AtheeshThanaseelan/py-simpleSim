#pragma once
#include <array>

class graphics_interface
{
    public:
    virtual void add_line(std::array<float, 6> line) = 0;
    virtual void update() = 0;
};