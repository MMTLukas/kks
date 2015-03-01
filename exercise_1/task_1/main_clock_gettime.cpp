#include <iostream>
#include <time.h>
#include <unistd.h>
using namespace std;

int main(){
	timespec tpStart, tpEnd;

	clock_gettime(CLOCK_REALTIME, &tpStart);
	sleep(3);
	clock_gettime(CLOCK_REALTIME, &tpEnd);
	
	cout << tpEnd.tv_sec - tpStart.tv_sec << endl;
	cout << tpEnd.tv_nsec - tpStart.tv_nsec << endl;
	return 0;	
}