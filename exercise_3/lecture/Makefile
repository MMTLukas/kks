SHELL=/bin/sh

# try -march=native -fopenmp -O2 -O3
CXX = g++ -g -O0 -Wall

all: me me_prof

me: me.cpp
	$(CXX) -o $@ me.cpp

me_prof: me.cpp
	$(CXX) -pg -o $@ me.cpp

check: me
	./me | cmp correct.txt

time: me
	time ./me

test: me
	valgrind --leak-check=full --show-reachable=yes ./me

prof: prof0

prof0: me_prof
	./me_prof
	gprof me_prof | head -n 15

cg: me
	valgrind --tool=callgrind --dump-instr=yes --collect-jumps=yes  --simulate-cache=yes ./me

clean:
	rm -f me me_prof gmon.out
