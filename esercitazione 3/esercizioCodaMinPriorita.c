#include <stdlib.h>
#include <stdio.h>
#include "codaMinPriorita.h"

// convenzione numero massimo inseribile
// in alternativa si potrebbe tenere traccia del max inserito ed usare quello.
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
int heapExtractMin(MinHeap v){
    int minK = heapMinimum(v);
    heapDelete(v,0);
    return minK;
}


/*pre: i e' un nodo dell'heap */
/*post: decrementa il valore della chiave dell'elemento in posizione i al valore k (k <= valore corrente dell'elemento in posizione i) */
void heapDecreaseKey(MinHeap v, int i, int k){
    v->elements[i]=k;
    uphefy(v,i);   // log(n)
}

/*post: inserisce l'elemento con chiave k nella coda.  */
void heapInsert(MinHeap v, int k){

    if (v->heapsize>=v->dim){
        v->dim*=2;
        // realloc.
    }

    //Inserisco l'elemento alla fine
    v->heapsize++;
    int i=v->heapsize-1;
    v->elements[i]=k;

    printf("%d inserito \n",v->elements[i]);

    if(v->heapsize>1)
        uphefy(v,i);
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

void uphefy(MinHeap v,int i){
    //Risolvo la proprieta' del MinHeap se violata
    while (i&& v->elements[parent(i)] > v->elements[i]){ // se mio padre e' > di me
       swap(&(v->elements[i]), &(v->elements[parent(i)])); // swappo mio padre con me
       i = parent(i); // divento il padre e continuo
    }
}

void downhefy(MinHeap v,int i){
    int lastLeft=0;

    while (i<=v->heapsize){
        if(getAt(v,left(i))<getAt(v,right(i))){
            if(left(i)<=v->heapsize || right(i)<=v->heapsize)
                swap(&(v->elements[i]), &(v->elements[left(i)]));
            i = left(i);
            lastLeft=1;
        }else{
            if(left(i)<=v->heapsize || right(i)<=v->heapsize)
                swap(&(v->elements[i]), &(v->elements[right(i)]));
            i = right(i);
            lastLeft=0;
        }
    }
/*
    i=parent(i);
    if(v->elements[left(i)] == MAXK)
        swap(&(v->elements[left(i)]), &(v->elements[right(i)]));    // lo mantengo COMPLETO LE FOGLIE PIENE A SINISTRA, QUELLE VUOTE A DX
*/
    if(lastLeft && i+1<v->heapsize)
        swap(&(v->elements[i]), &(v->elements[i+1])); // swappo me stesso col fratello di destra
}

int getAt(MinHeap v,int index){
    if(index>v->heapsize || index<0)return MAXK;
    else return v->elements[index];
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


MinHeap intersect(MinHeap h1, MinHeap h2){
    MinHeap n = newMinHeap(h1->heapsize + h2->heapsize);
}


void printHeap(int* v,int d,int cap){
    int t=1;
    int r=d;
    int i=0;
    int f=0;
    while(f<d && i<cap){
        for(int j=0;j< r - t;j++)printf(" ");
        for(int j=0;f<d && i<cap && j<t;j++){
            if(v[i]!=MAXK && v[i]!=0){printf("%d ",v[i]);f++;}
            i++;
        }
        printf("\n");
        t*=2;
        //r/=2;
    }
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

    for(int i=1;i<10;i++)
        heapInsert(v,i*2);

    while(v->heapsize>0){
        printHeap(v->elements,v->heapsize,v->dim);
        printf("\n\n min estrect > %d \n",heapExtractMin(v));
        printf("%d elementi rimasti \n", v->heapsize);
    }


    printHeap(v->elements,v->heapsize,v->dim);

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
