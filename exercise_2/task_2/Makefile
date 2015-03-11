CXXFLAGS = -Wall -g -std=c++11
CXX = g++
CONFIG = config.p
RESULT = result.png

all: build run plot clean

build:
	$(CXX) $(CXXFLAGS) -o cache0 main.cpp -DNPAD=0
	$(CXX) $(CXXFLAGS) -o cache7 main.cpp -DNPAD=7
	$(CXX) $(CXXFLAGS) -o cache15 main.cpp -DNPAD=15
	$(CXX) $(CXXFLAGS) -o cache31 main.cpp -DNPAD=31
	
run:
	./cache0
	./cache7
	./cache15
	./cache31

plot:
	gnuplot $(CONFIG) > $(RESULT)

clean:
	rm -f ./cache0
	rm -f ./cache7
	rm -f ./cache15
	rm -f ./cache31