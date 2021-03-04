#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char* ltrim(char*);
char* rtrim(char*);

int parse_int(char*);



#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)

void merge(int arr[], int l, int m, int r); // funzione aux per il mergesort
void mergeSort(int arr[], int l, int r); // mergesort O(nlogn)

/**
Ricerca binaria di un elemento in un vettore ordinato, nel range (l,r)
Se target non e' presente returna -1, altrimenti l'indice nell array.
Complessita' O(log2(r-l))
Sapendo che l<r< v.size
*/
int binarysearch(int v[],int l,int r,int target){
    int mid;
    while(l<=r){
        mid=l+(r-l)/2;
        if(v[mid]==target)return mid;
        if(v[mid]>target) r=mid-1;
        else l=mid+1;
    }
    return -1;
}

/**
1) Ordino l'array in ordine ascendente
2) Itero l'array, per ogni numero trovo il numero per la quale sommato
    mi darebbe K (profittoProg)
    target = K - v[i]
    
3) Per ogni elemento dell array faccio una ricerca binaria per verificare
    di trovare un numero target, per la quale somma fa K.
    Se lo trovo, incremento X, e salto tutti i prossimi N numeri uguali ad X
    adiacenti al numero nella quale mi trovo. (in questo modo avro' solo coppie distinte.)
    
Complessita' : 
O(n log n) ordinamento
O(n log n) for + ricerca binaria per ogni elemento

Quindi : Time O(n log n) Space O(1) 


NB : ANDARE GIU' PER VEDERE UNA SOLUZIONE Time O(n) Space O(n)
    
    

Ottimizzazioni che abbassano exec time (ma non complessita') : 
1) Dato un numero X, la binary search la faccio solo al lato destro rispetto ad X
    In questo modo trovo solo numeri maggiori di X che sommati ad X fanno K.
    Facendolo sempre verso Dx evito il rischio di trovare ridondanze (coppie gia' trovate)
    
2) Se mi trovo in un numero X>profittoProg/2, restituisco il risultato.
    Non puo' esistere un numero maggiore di X che sommato ad X da K se X e' > della meta' di K.

3) Nel caso avessi trovato un numero X e la sua coppia con target, salto velocemente tutti
    i prossimi N numeri uguali ad X adiacenti ad esso nell array.
    In questo modo evito tutti i duplicati (nel caso ci siano 3 3 3 9 9 9 , trovato il primo
    salto gli altri.)
4) Per lo stesso motivo del punto 2, se target e' < X allora e' inutile fare la ricerca. 
    (il punto 2 gia' copre anche questo caso.)

*/
int contaCoppie(int v[], int dim, int profittoProg){
    int ans=0;
    mergeSort(v,0,dim-1);
    for(int i=0;i<dim-1;i++){
        if(v[i]>profittoProg/2) return ans;
        int target= profittoProg - v[i];
        if(target<v[i])continue;
        int index=binarysearch(v,i+1,dim,target);
        int thisIsABadNumber=v[i];
        while(i<dim && v[i]==thisIsABadNumber)i++;
        i--;
        if(index>0) ans++;
    }
    return ans;
}

int maxOf(int v[],int dim);
int minOf(int v[],int dim);

int contaCoppieLineare(int v[], int dim, int profittoProg){
    
    int ans=0;
    int maxx=10000; //maxOf(v,dim) + abs(profittoProg);
    int minxx=-10000; //minOf(v,dim) + abs(profittoProg);
    minxx=minxx<0?-minxx:0;
    
    int fpos[maxx],fneg[minxx];
    
    for(int i=0;i<maxx;i++)fpos[i]=0;
    for(int i=0;i<minxx;i++)fneg[i]=0;

    for(int i=0;i<dim;i++)
        if(v[i]>=0)
            fpos[v[i]]++;
        else
            fneg[-v[i]]++; 
    /**
        + - = K 
        + + = K 
        - - = K
        - + = K
    */
    for(int i=0;i<dim;i++){
        int target=profittoProg-v[i];

        if(target>=0){
            if(fpos[target]>0){
                ans++;
                fpos[target]=0;
                if(v[i]>=0) fpos[v[i]]=0;
            }  
        }else{
            if(fneg[-target]>0){
                ans++;
                fneg[-target]=0;
                if(v[i]<0) fneg[v[i]]=0;
            }  
        }
      
    }
    
    return ans;
}


int maxOf(int v[],int dim){
    int x=-INT_MAX;
    for(int i=0;i<dim;i++)
        x=max(x,v[i]);
    return x;
}

int minOf(int v[],int dim){
    int x=+INT_MAX;
    for(int i=0;i<dim;i++)
        x=min(x,v[i]);
    return x;
}

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
// Merge Sort Function in C 
void mergeSort(int arr[], int l, int r) {
  if (l < r) {
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
  }
}

int main()