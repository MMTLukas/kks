#include <iostream>
#include <time.h>
#include <unistd.h>
using namespace std;

int main(){
	sleep(10);
	cout << clock() << endl << clock()/CLOCKS_PER_SEC<< endl;
	return 0;	
}