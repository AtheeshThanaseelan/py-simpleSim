INC=-I/usr/include/bullet

all: complexObject compoundObject objectWrapper

complexObject: complexObject.cpp
	gcc -Wall $(INC) -c complexObject.cpp

compoundObject: compoundObject.cpp
	gcc -Wall $(INC) -c compoundObject.cpp

objectWrapper: objectWrapper.cpp
	gcc -Wall $(INC) -c objectWrapper.cpp


clean:
	rm complexObject.o compoundObject.o objectWrapper.o
