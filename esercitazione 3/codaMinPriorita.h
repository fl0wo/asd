typedef struct minHeap * MinHeap;

MinHeap newMinHeap();
int heapEmpty(MinHeap v);
int heapMinimum(MinHeap v);
int heapExtractMin(MinHeap v);
void heapDecreaseKey(MinHeap v, int i, int k);
void heapInsert(MinHeap v, int k);
void heapDelete(MinHeap v, int i);
int heapSearch(MinHeap v, int k);
int heapsize(MinHeap v);
