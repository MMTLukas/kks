#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include <stdint.h>
#include <string>
using namespace std;

struct l {
    struct l *n;
    long int pad[NPAD];
};

static inline uint64_t RDTSC() {
  unsigned int hi = 0, lo = 0;
  __asm__ volatile("rdtsc" : "=a" (lo), "=d" (hi));
  return ((uint64_t)hi << 32) | lo;
}

int main() {
    short exp = 10;
    short expEnd = 22;
    
    FILE * pFile;
    string fileNameStr = string("data/results") + to_string(NPAD) + string(".dat");
    pFile = fopen (fileNameStr.c_str(),"w");
    
    for(int i = pow(2, exp); i <= pow(2, expEnd); i=pow(2, ++exp)){
        long elements = 0;
        l *start = new l();
        l *current = start;

        //Create nodes on cache
        for(int j=0; j<i; j++){
            current->n = new l();
            current = current->n;
            elements++;
        }
        
        //Access nodes on cache
        current = start;
        double ticksStart = RDTSC();
        while(current != NULL){
            current = current->n;
        }
        double ticksEnd = RDTSC();
        
        //Delete nodes on cache
        current = start;
        l *next = start;
        for(unsigned k = 0; k < elements; k++) {
            next = current->n;
            delete current;
            current = next;
        }
        
        unsigned yValue = (ticksEnd - ticksStart) / i;
        unsigned xValue = exp;

        fprintf(pFile, "%d\t%d\n", xValue, yValue);
    }
    
    fclose (pFile);  
    cout<<"Successfully run through. File written. NPAD="<<to_string(NPAD)<<endl;
    
    return 0;
}