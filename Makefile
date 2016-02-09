.PHONY: all

EXECUTABLE_NAME = tcalc
CXX             = g++
CXX_FLAGS       = -g -std=c++11 -lncurses -Wall

all: tcalc.cpp
	$(CXX) $(CXX_FLAGS) -o $(EXECUTABLE_NAME) tcalc.cpp
