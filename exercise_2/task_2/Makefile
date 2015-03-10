CXXFLAGS = -Wall -g
CXX = g++
CONFIG = config.p
RESULT = result.png

all: build run clean

build:
	$(CXX) $(CXXFLAGS) -o main main.cpp
	
run:
	./main

clean: 
	rm -rf main

plot:
	gnuplot $(CONFIG) > $(RESULT)
