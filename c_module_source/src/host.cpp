#include "host.h"
#include <iostream>

host::host()
{
    m_gfx = nullptr;
    m_phys = nullptr;

};

void host::setPhys(physics_interface* newphys)
{
    m_phys = newphys;
}
void host::setGfx(graphics_interface* newgfx)
{
    m_gfx = newgfx;
}
//void host::setUsrInp(userinput_interface* newusrinp);


/*
-1: ground
1: box
2: complex(old)
3: compound
DO NOT USE 0
*/
object_interface* host::addObject(int index)
{
    object_interface* o = nullptr;
    if (m_phys != nullptr)
    {
        o = m_phys->addobj(index);
        objects.push_back(o);
    }
    return o; 
}


object_interface* host::getObject(int index)
{
    std::cout<<"pls";
    if (m_phys != nullptr)
    {
        object_interface* obj = objects.at(index);
        std::cout<<"got";
        return obj;
    }
    std::cout<<"none";
    return nullptr;
}

void host::update()
{
    if (m_phys != nullptr)
        m_phys->update();

    if (m_gfx != nullptr)
        m_gfx->update();
}