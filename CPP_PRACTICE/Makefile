CXX = g++
CXXFLAGS = -Wall -std=c++11

OBJECTS = node.o list.o wrapper.o

stackrecursion: $(OBJECTS)
	$(CXX) -g $(CXXFLAGS) -o $@ $^

clean: 
	rm -f *.o wrapper
$(OBJECTS): node.h list.h
