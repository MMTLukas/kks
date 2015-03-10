#include <iostream>
#include <stdio.h>
using namespace std;

class MinHeap {
    private:
    
        unsigned size;
        unsigned elements;
        double *values;
        
        unsigned leftChildIndex(unsigned index);
        unsigned rightChildIndex(unsigned index);
        unsigned parentIndex(unsigned index);
        unsigned getMinChildIndex(unsigned index);
        double top();
        
    public:
    
        MinHeap(unsigned newSize);
        ~MinHeap();

        void push(double value);
        double pop();
        
        void print();
        
};