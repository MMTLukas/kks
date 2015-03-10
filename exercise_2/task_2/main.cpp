#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <cmath>
using namespace std;

clock_t measureCacheAccess(long *values, int length) {
    int value = 0;
    
    clock_t ticksStart = clock();
    for(int i=0;i<length;i++){
        value = values[i];
    }
    clock_t ticksEnd = clock();
    
    return ticksEnd - ticksStart;
}

int main() {
    short exp = 10;
    short expEnd = 27;
    
    FILE * pFile;
    pFile = fopen ("data/results.dat","w");
    
    for(int i = pow(2, exp); i <= pow(2, expEnd); i=pow(2, ++exp)){
        long *values = new long[i];
        
        for(int j=0; j<i; j++){
            values[j] = rand() % 100;
        }
        
        fprintf(pFile, "%d\t%d\n", i, (int)measureCacheAccess(values, i));
        delete[] values;
    }
    
    fclose (pFile);  
    cout<<"Successfully run through. File written."<<endl;
    
    return 0;
}
