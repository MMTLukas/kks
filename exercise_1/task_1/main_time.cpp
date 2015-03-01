#include <iostream>
#include <time.h>
#include <unistd.h>
using namespace std;

int main(){
	time_t start = time(NULL);
	sleep(1);
	time_t end = time(NULL);
	cout << end - start << endl;
	return 0;	
}