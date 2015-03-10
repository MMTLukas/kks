#include <cstdlib>
#include "MinHeap.h"
#include <time.h>
#include <algorithm>
#include <vector>

bool comp(const double& a, const double& b) {
    return b < a;
}

unsigned measureOwnImplementation(unsigned n){
    timespec timeStart, timeEnd;
    MinHeap *minHeap = new MinHeap(n);
    clock_gettime(CLOCK_REALTIME, &timeStart);
    
    for(unsigned i = 0; i < n; i++){
        minHeap->push(rand() % n);
    }
    
    clock_gettime(CLOCK_REALTIME, &timeEnd);
    delete minHeap;
    return timeEnd.tv_nsec - timeStart.tv_nsec;
}

unsigned measureSTLImplementation(unsigned n){
    timespec timeStart, timeEnd;
    
    vector<double> v;
    
    clock_gettime(CLOCK_REALTIME, &timeStart);
    for(unsigned i = 0; i < n; i++) {
        v.push_back(rand() % n);
        std::push_heap(v.begin(), v.end(), comp);
    }
    clock_gettime(CLOCK_REALTIME, &timeEnd);

    return timeEnd.tv_nsec - timeStart.tv_nsec;
}

double mean(double *times){
    double value = 0;
    short length = sizeof(times)/sizeof(double);
    for(int i = 0; i < length; i++){
        value += times[i];
    }
    return value/length;
}

int main() {
    short amountMeasures = 20;
    srand(time(NULL));

    FILE * pFile;
    pFile = fopen ("data/results.dat","w");
    
    cout<<"Is measuring MinHeap-Push duration..."<<endl;
    for(unsigned i = 100; i <= 10000000; i = i * 10){
        double timesOwn[amountMeasures];
        double timesSTL[amountMeasures];
        
        for(int j = 0; j<amountMeasures; j++){
            timesOwn[j] = measureOwnImplementation(i);
            timesSTL[j] = measureSTLImplementation(i);
        }
        
        fprintf(pFile, "n\t%d\tOWN\t%f\tSTL\t%f\n", i, mean(timesOwn), mean(timesSTL));
    }
    
    cout<<"Successfully run through. File written."<<endl;
    
    fclose (pFile);
    return EXIT_SUCCESS;
}

