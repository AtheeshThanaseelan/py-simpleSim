INC=-I/usr/include/bullet
LIB=-Lexternal -Lobjects -Lutilities

all: main

main2: main2.cpp
	gcc -Wall -o main main2.cpp

main: main.cpp
	cd external && $(MAKE)
	cd utility && $(MAKE)
	cd objects && $(MAKE)

	gcc -Wall -I/usr/include/bullet -L/usr/lib -o main main.cpp external/*.o objects/*.o utility/*.o  \
		-lstdc++ -lm -lIrrlicht \
		-lLinearMath \
		/usr/lib/libBullet*

		

clean:
	cd external && $(MAKE) clean
	cd utility && $(MAKE) clean
	cd objects && $(MAKE) clean
	rm main
	
