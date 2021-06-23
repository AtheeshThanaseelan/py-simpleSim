#include "host.h"


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
*/
void host::addObject(int index)
{
    if (m_phys != nullptr)
        objects.push_back(m_phys->addobj(index));
}


object_interface* host::getObject(int index)
{
    if (m_phys != nullptr)
    {
        object_interface* obj = objects.at(index);
        return obj;
    }
    return nullptr;
}

void host::update()
{
    if (m_phys != nullptr)
        m_phys->update();

    if (m_gfx != nullptr)
        m_gfx->update();
}