#pragma once
#include <array>
#include <vector>
#include <string>

#include "interfaces/graphics_interface.h"
#include "interfaces/physics_interface.h"
#include "interfaces/userinput_interface.h"
#include "interfaces/object_interface.h"
#include "interfaces/utility_interface.h"

class host
{
public:

    graphics_interface* m_gfx;
    physics_interface* m_phys;
    userinput_interface* m_usrinp;

    std::vector<object_interface*> objects;

    host();

    void setPhys(physics_interface* newphys);
    void setGfx(graphics_interface* newgfx);
    //void setUsrInp(userinput_interface* newusrinp);

    object_interface* addObject(int index);
    void addUtility(utility_interface* utility);

    object_interface* getObject(int index);

    void update();

    //environment engine
    //set environment



};