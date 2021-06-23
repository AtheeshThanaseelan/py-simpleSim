#include <iostream>
#include <chrono>
#include <thread>


#include "host.h"
#include "interfaces/physics_interface.h"
#include "drivers/bPhysics/bPhysics.h"
#include "drivers/irrlicht/irr_debug_draw.h"

#include "utility/region.h"
//what is the main thing
	//world
	//bt_body


//how do things communicate
	//drivers
		//open window or speak through cmd
		//attach different ones
	//objects
		//add to world
		//communicate through


//design
	//bphys
		//main world and everything: interface to world
		//objects: box, etc
	//irr
		//graphics handler
	//world
		//object wrapper (interfaces)
		//world wrapper (interfaces)
	//tui
		//tui
	//utilities




//2
	//


void test1()
{
	//host* main_host = new host();

	#ifdef gfx
		irr_btDebug* g = new irr_btDebug();
		physics_interface* phys = new bPhysics(g);
	
	#else
		physics_interface* phys = new bPhysics(nullptr);

	#endif

	//object_interface* t_obj = phys->addobj(-1);		
	object_interface* obj = phys->addobj(3);		

	std::array<std::array<int, 2>, 4> vertices = {{{0,0},{0,2},{2,2},{2,0}}};
	std::array<int, 2> point = {{1,1}};
	region* reg = new region(vertices);
	reg->check(point);
	for(int i =0; i<1*20;i++)
	{
		//reg->draw(g);
		phys->update();
		std::cout<<obj->getTransform_qat()[5]<<std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		//g->update();
	}

	delete phys;
}

void test2()
{
	host* h = new host();
	h->setPhys(new bPhysics(nullptr));
	//h->addObject(3);
	//std::cout<<"host \n";
	for(int i =0; i<1*20;i++)
	{
		h->update();
		//std::cout<<h->getObject(0)->getTransform_qat()[5]<<std::endl;
		//std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
}

int main()
{
	test2();

    return 0;
}