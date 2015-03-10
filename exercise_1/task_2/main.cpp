#include <cstdlib>
#include "MinHeap.h"
#include <time.h>
#include <algorithm>

bool comp(const int& a, const int& b) {
    return b < a ? true : false;
}

unsigned measureOwnImplementation(unsigned n){
    timespec timeStart, timeEnd;
    clock_gettime(CLOCK_REALTIME, &timeStart);

    MinHeap *minHeap = new MinHeap(n);
    for(unsigned i = 0; i < n; i++){
        minHeap->push(rand() % n);
    }

    clock_gettime(CLOCK_REALTIME, &timeEnd);
    return timeEnd.tv_nsec - timeStart.tv_nsec;
}

unsigned measureSTLImplementation(unsigned n){
    timespec timeStart, timeEnd;
    clock_gettime(CLOCK_REALTIME, &timeStart);

    double *heapData = new double[n];
    for(unsigned i = 0; i < n; i++) {
        heapData[i] = rand() % n;
    }
    std::make_heap(heapData, heapData + n, comp);

    clock_gettime(CLOCK_REALTIME, &timeEnd);
    delete[] heapData;
    return timeEnd.tv_nsec - timeStart.tv_nsec;
}

int main() {
    srand(time(NULL));

    for(unsigned i = 100; i <= 10000000; i = i * 10){
        unsigned time = measureOwnImplementation(i);
        cout << "n\t" << i << "\t" << time << "\tOWN" << endl;
    }

    for(unsigned i = 100; i <= 10000000; i = i * 10){
        unsigned time = measureSTLImplementation(i);
        cout << "n\t" << i << "\t" << time << "\tSTL" << endl;
    }

    return EXIT_SUCCESS;
}

