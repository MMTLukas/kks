#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <cmath>
using namespace std;

struct l {
    struct l *n;
};

int main() {
    short exp = 10;
    short expEnd = 28;
    
    FILE * pFile;
    pFile = fopen ("data/results.dat","w");
    
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
        clock_t ticksStart = clock();
        while(current != NULL){
            current = current->n;
        }
        clock_t ticksEnd = clock();
        
        //Delete nodes on cache
        current = start;
        l *next = start;
        for(int k = 0; k < elements; k++) {
            next = current->n;
            delete current;
            current = next;
        }

        unsigned yValue = (ticksEnd - ticksStart) / (i/sizeof(l));
        unsigned xValue = exp;

        fprintf(pFile, "%d\t%d\n", xValue, yValue);
        cout << exp <<endl;
    }
    
    fclose (pFile);  
    cout<<"Successfully run through. File written."<<endl;
    
    return 0;
}
