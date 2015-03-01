#include <iostream>
#include <time.h>
#include <cstdint>
#include <inttypes.h>
#include <unistd.h>
using namespace std;

int64_t getCPUCount(unsigned int loword, unsigned int hiword){
	int a=10, b;
	__asm("_emit 0x0f\n\t"
		"_emit 0x31\n\t"
		"mov %0, edx\n\t"
		"mov %1, eax"
		:/* */
		:"a"(loword), "b"(hiword)
	);

	return ( (int64_t) hiword << 32) + loword;
}

int main(){
	unsigned int hi = 0, lo = 0;

	double start = getCPUCount(lo, hi);
	sleep(3);
	double end = getCPUCount(lo, hi);
	
	cout << end - start << endl;
	return 0;	
}