#pragma once
#include "object_interface.h"
#include "graphics_interface.h"

class utility_interface
{
    public:
    virtual void draw(graphics_interface* gfxprovider);
};