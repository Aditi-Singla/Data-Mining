CC = g++
CXXFLAGS = -std=c++11 -I include/ -I boost_libs/include -I boost_libs/lib -DNDEBUG

BUILD_TYPE = test

ifeq ($(BUILD_TYPE), debug)
	CXXFLAGS += -g
else
	CXXFLAGS += -O3
endif

all : src/*.cpp
	$(CC) src/*.cpp $(CXXFLAGS) -o cluster

clean : 
	rm -f cluster *.txt callgrind*
