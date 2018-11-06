CC = g++
CXXFLAGS = -std=c++11
INCLUDE = include/

BUILD_TYPE = test

ifeq ($(BUILD_TYPE), debug)
	CXXFLAGS += -g
else
	CXXFLAGS += -O3
endif

all : src/*.cpp
	$(CC) src/*.cpp $(CXXFLAGS) -I $(INCLUDE) -o fpm

clean : 
	rm -f fpm *.txt callgrind*
