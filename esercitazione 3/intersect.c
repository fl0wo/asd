#include <stdio.h>
#include <stdlib.h>
#include "codaMinPriorita.h"

struct minHeap{
  int *elements;
  int heapsize;
  int dim;
};

// O(M log M + N log N)
MinHeap intersect(MinHeap h1, MinHeap h2){
    MinHeap n = newMinHeap(max(h1->heapsize,h2->heapsize));

    while(h1->heapsize>0 && h2->heapsize>0){
        if(heapMinimum(h1)==heapMinimum(h2)){
            heapInsert(n,heapMinimum(h1));
            heapExtractMin(h1);
            heapExtractMin(h2);
        }
        else if(heapMinimum(h1)>heapMinimum(h2))
            heapExtractMin(h2);
        else if(heapMinimum(h1)<heapMinimum(h2))
            heapExtractMin(h1);
    }

    return n;
}
