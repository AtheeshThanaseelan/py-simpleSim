INC=-I/usr/include/bullet

all: bPhysics irrlicht

bPhysics: bPhysics.cpp
	gcc -Wall $(INC) -c bPhysics.cpp

irrlicht: irrlicht.cpp
	gcc -Wall $(INC) -c irrlicht.cpp

clean:
	rm bPhysics.o irrlicht.o
