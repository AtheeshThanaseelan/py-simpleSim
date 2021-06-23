INC=-I/usr/include/bullet
LIB=-Lexternal -Lobjects -Lutilities
+CFLAGS += -Dgfx

all: main

bPhysics: 
	cd drivers/bPhysics && gcc -Wall $(INC) -c bPhysics.cpp
	cd drivers/bPhysics/objects && gcc -Wall $(INC) -c *.cpp

nogfx: bPhysics main2.cpp

	gcc -Wall $(INC) -c host.cpp
	cd utility && gcc -Wall -c region.cpp

	gcc -Wall $(INC) -o main main2.cpp drivers/bPhysics/bPhysics.o host.o drivers/bPhysics/objects/*.o utility/*.o -lstdc++ -lm -lLinearMath \
		-lBullet3Dynamics -lBullet3Collision -lBulletCollision -lBulletDynamics

main: bPhysics main2.cpp

	gcc -Wall $(INC) $(CFLAGS) -c host.cpp
	cd drivers/irrlicht && gcc -Wall $(INC) $(CFLAGS) -c *.cpp
	cd utility && gcc -Wall -c region.cpp
	
	gcc $(CFLAGS) -Wall $(INC) -o main main2.cpp utility/*.o host.o drivers/bPhysics/bPhysics.o drivers/bPhysics/objects/*.o \
		drivers/irrlicht/irr_debug_draw.o -lstdc++ -lm -lIrrlicht -lLinearMath \
		-lBullet3Dynamics -lBullet3Collision -lBulletCollision -lBulletDynamics

debug: main.cpp
	gcc -g -Wall $(INC) -c host.cpp
	
	cd utility && gcc -g -Wall -c region.cpp
	cd drivers/bPhysics && gcc -g -Wall $(INC) $(CFLAGS) -c bPhysics.cpp
	cd drivers/bPhysics/objects && gcc -g -Wall $(INC) $(CFLAGS) -c *.cpp


	gcc -g -Wall $(INC) -o main main2.cpp drivers/bPhysics/bPhysics.o host.o drivers/bPhysics/objects/*.o utility/*.o -lstdc++ -lm -lLinearMath \
		-lBullet3Dynamics -lBullet3Collision -lBulletCollision -lBulletDynamics

debug_gfx: main2.cpp
	cd interfaces/ && gcc -g -Wall $(INC) $(CFLAGS) -c host.cpp
	cd drivers/bPhysics && gcc -g -Wall $(INC) $(CFLAGS) -c bPhysics.cpp
	cd drivers/bPhysics/objects && gcc -g -Wall $(INC) $(CFLAGS) -c *.cpp
	cd drivers/irrlicht && gcc -g -Wall $(INC) $(CFLAGS) -c *.cpp
	cd utility && gcc -g -Wall -c region.cpp
	
	gcc -g $(CFLAGS) -Wall $(INC) -o main main2.cpp utility/*.o interfaces/host.o drivers/bPhysics/bPhysics.o drivers/bPhysics/objects/*.o \
		drivers/irrlicht/irr_debug_draw.o -lstdc++ -lm -lIrrlicht -lLinearMath \
		-lBullet3Dynamics -lBullet3Collision -lBulletCollision -lBulletDynamics
	
wipe:
	cd interfaces && rm -f *.o
	cd drivers/bPhysics && rm -f *.o
	cd drivers/bPhysics/objects && rm -f *.o



clean:
	#cd external && $(MAKE) clean
	#cd utility && $(MAKE) clean
	#cd objects && $(MAKE) clean
	rm main
	
