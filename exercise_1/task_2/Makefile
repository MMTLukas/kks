CXXFLAGS = -Wall -g
CXX = g++
CONFIG = config.p
RESULT = result.png

all: build run clean

build:
	$(CXX) $(CXXFLAGS) -o heap MinHeap.cpp main.cpp
	
run:
	./heap

clean: 
	rm -rf heap

plot:
	gnuplot $(CONFIG) > $(RESULT)
