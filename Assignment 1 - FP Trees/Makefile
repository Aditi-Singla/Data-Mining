CC = g++
CXXFLAGS = -std=c++11 -I include/

BUILD_TYPE = debug

ifeq ($(BUILD_TYPE), debug)
	CXXFLAGS += -g
else
	CXXFLAGS += -o3 -march=native
endif

all : src/*.cpp
	$(CC) src/*.cpp $(CXXFLAGS) -o fpm

clean : 
	rm -f fpm *.txt callgrind*
