#pragma once
#include "object_interface.h"

class physics_interface
{
    public:
    //virtual physics_interface(int debug_view) = 0;
    virtual void update() = 0;
    virtual object_interface* addobj(int index) = 0;
    virtual ~physics_interface() {};
};