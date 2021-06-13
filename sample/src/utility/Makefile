INC=-I/usr/include/bullet

all: irr_debug_draw range_finder region utilities

irr_debug_draw: irr_debug_draw.cpp
	gcc -Wall $(INC) -c irr_debug_draw.cpp

range_finder: range_finder.cpp
	gcc -Wall $(INC) -c range_finder.cpp

region: region.cpp
	gcc -Wall $(INC) -c region.cpp

utilities: utilities.cpp	
	gcc -Wall $(INC) -c utilities.cpp

clean:
	rm irr_debug_draw.o range_finder.o region.o utilities.o
