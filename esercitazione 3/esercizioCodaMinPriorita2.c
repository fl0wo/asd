#include <stdlib.h>
#include <stdio.h>
#include "codaMinPriorita.h"

// convenzione numero massimo inseribile
#define MAXK 2147483647


// Manca fixxare la dimensione e fare i realloc
// e commentare tutto


struct minHeap{
  int *elements;
  int heapsize;
  int dim;
};

void swap(int *x, int *y);
void uphefy(MinHeap v,int i);
void downhefy(MinHeap v,int i);

int parent(int i) {return (i-1)/2;}
int left(int i) {return (2*i+1);}
int right(int i) {return left(i)+1;}
int max(int a,int b){return a>b?a:b;}
int min(int a,int b){return a<b?a:b;}
int getAt(MinHeap v,int index);


/*post: restituisce una coda di min-priorita' vuota (heapsize = 0), con dimensione size */
MinHeap newMinHeap(int size){
    MinHeap x= (MinHeap) malloc(sizeof(struct minHeap));
    x->dim=size;
    x->heapsize=0;
    x->elements=malloc(sizeof(int)*size); // da rivedere
    return x;
}


/*post: restituisce >0 se la coda di min-priorita' e' vuota, 0 atrimenti */
int heapEmpty(MinHeap v){
    return v->heapsize==0;
}

/*pre: la coda e' non vuota */
/*post: restituisce la chiave piu' piccola nella coda */
int heapMinimum(MinHeap v){
    return (v->elements[0]);
}

/*pre: la coda e' non vuota */
/*post: elimina e restituisce la chiave piu' piccola nella coda */
int heapExtractMin(MinHeap h){
    int pop;
    pop = h->elements[0];
    h->elements[0] = h->elements[h->heapsize-1]; // or max
    h->heapsize--;
    downhefy(h,0);
    return pop;
}


/*pre: i e' un nodo dell'heap */
/*post: decrementa il valore della chiave dell'elemento in posizione i al valore k (k <= valore corrente dell'elemento in posizione i) */
void heapDecreaseKey(MinHeap v, int i, int k){
    v->elements[i]=k;
    uphefy(v,i);   // log(n)
}

/*post: inserisce l'elemento con chiave k nella coda.  */
void heapInsert(MinHeap h, int k){
    if(h->heapsize<h->dim){
        h->elements[h->heapsize] = k;
        uphefy(h, h->heapsize);
        h->heapsize++;
    }
}


/*pre: i e' un nodo dell'heap */
/*post: cancella l’elemento nel nodo i dalla coda */

void heapDelete(MinHeap v, int i){
    v->elements[i]=MAXK;
    downhefy(v,i);
    v->heapsize--;
}

int heapSearchAux(MinHeap v, int k,int i){
    if(v->elements[i]==k)return i;
    if(v->elements[i]>k) return -1; // appena supero il limite, non ricorro piu'
    return max(heapSearchAux(v,k,right(i)),heapSearchAux(v,k,left(i)));
}

/*post: restituisce un nodo che contiene la chiave k se k e' presente nella coda di min-priorita', -1 altrimenti */
int heapSearch(MinHeap v, int k){
    return heapSearchAux(v,k,0);
}

/* post: restituisce la heapsize della coda di min-priorita' */
int heapsize(MinHeap v){
    return v->heapsize;
}

void uphefy(MinHeap h,int index){
    while(h->elements[parent(index)] > h->elements[index]){
        swap(&(h->elements[index]),&(h->elements[parent(index)]));
        index = parent(index);
    }
}

int negIfOutBounds(MinHeap h,int a){
    return a>=h->heapsize||a<0?-1:a;
}

void downhefy(MinHeap h,int index){
    int min=-1;

    while(min!=index){
        int L = negIfOutBounds(h,left(index));
        int R = negIfOutBounds(h,right(index));
        int P = h->elements[index];

        if(L!=-1 && h->elements[L]<h->elements[index])min=L;
        else min=index;
        if(R!=-1 && h->elements[R]<h->elements[min])min=R;

        if(min!=index){
            swap(&(h->elements[min]),&(h->elements[index]));
            index=min;
        }
    }
}


void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

void printAll(MinHeap v){
    for(int i=0;i<v->heapsize;i++)
        printf("%d ",v->elements[i]);
    printf("\n");
}


void printHeap(int* v,int d,int cap){
    int t=1;
    int r=d;
    int i=0;
    int f=0;
    while(f<d&&i<cap){
        for(int j=0;j<r-t;j++)printf(" ");
        for(int j=0;f<d&&i<cap&&j<t;j++){
            if(v[i]!=MAXK && v[i]!=0){printf("%d ",v[i]);f++;}
            i++;
        }
        printf("\n");
        t*=2;
    }
}

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


int main() {

    MinHeap v = newMinHeap(11);
    heapInsert(v,3);
    heapInsert(v,2);
    heapInsert(v,1);
    heapInsert(v,15);
    heapInsert(v,5);
    heapInsert(v,4);
    heapInsert(v,-2);

    MinHeap h = newMinHeap(9);

    for(int i=1;i<10;i++)
        heapInsert(h,i*2);


    printHeap(v->elements,v->heapsize,v->dim);

    printf("\n\n + \n\n");

    printHeap(h->elements,h->heapsize,h->dim);

    printf("\n\n = \n\n");

    MinHeap mer = intersect(v,h);

    printHeap(mer->elements,mer->heapsize,mer->dim);

/*
    while(v->heapsize>0){
        printHeap(v->elements,v->heapsize,v->dim);
        printf("\n\n min estrect > %d \n",heapExtractMin(v));
        printf("%d elementi rimasti \n", v->heapsize);
    }
*/

    //printHeap(v->elements,v->heapsize,v->dim);

/*  int minPop = heapExtractMin(v);
    int min = heapMinimum(v);
    //heapDecreaseKey(v,0,1);
    heapExtractMin(v);
    int min2 = heapMinimum(v);

    printAll(v);

    printf("primo min %d \n",minPop);
    printf("secondo min %d \n",min);
    printf("terzo min %d \n",min2);
*/
    return 0;
}
