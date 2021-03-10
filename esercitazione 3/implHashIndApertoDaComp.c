#include <stdlib.h>
#include <stdio.h>

#include "dizionario.h"
#define HASHSIZE 8
#define HASHAUX 1392838232

#define hash1(k) (k%HASHSIZE)
#define hash2(k) (1+2 * (k % (HASHSIZE - 3) ) )

struct elem{
  int key;
  int info;

  Elem next; // next elemento inserito subito dopo di me
  Elem prec; // precedente elemento inserito subito prima di me
};

/* DEL e' un elemento fittizio che rappresenta un elemento cancellato */
struct dizionario{
  Elem * content;
  int numchiavi;
  Elem DEL;
  Elem LAST_INSERTED; // ultimo elemento inserito
};

int funHash(int val,int i){
    return (hash1(val) + i * hash2(val)) % HASHSIZE;
}

int getHash(Dizionario d,int key){
    int i=0;
    int hash = funHash(key,i);
    while(d->content[hash]!=NULL)
        hash=funHash(key,++i);
    return hash;
}

/*post: restituisce un dizionario vuoto */
Dizionario crea(){
    Dizionario d = (Dizionario) malloc(sizeof(struct dizionario));
    d->content = (Elem*) malloc(sizeof(struct elem) * HASHSIZE);

    for(int i=0;i<HASHSIZE;i++)
        d->content[i]=NULL;
    //memset(d->content,NULL,sizeof(d->content)); // inizialmente tutto a null

    d->numchiavi = 0;

    d->DEL=(Elem) malloc(sizeof(struct elem));
    d->DEL->key=HASHAUX;
    d->DEL->info=HASHAUX;

    d->LAST_INSERTED = NULL;

    return d;
}

/*pre: k non e' presente in d e c'e' spazio in d*/
/*post: associa il valore val alla chiave k nel dizionario d*/
void inserisci(Dizionario d, int k, int val){
    int hash = getHash(d,k);

    d->content[hash] = (Elem) malloc(sizeof(struct elem));
    d->content[hash]->key=k;
    d->content[hash]->info=val;

    d->content[hash]->next=NULL;

    d->content[hash]->prec=d->LAST_INSERTED; // il primo che inserisco il suo precedente e' nullo.

    d->LAST_INSERTED = d->content[hash];

    if(d->content[hash]->prec != NULL) // non e' la prima volta che inserisco
        d->content[hash]->prec->next=d->content[hash];

    d->numchiavi++;
}

/*pre: l'elemento x e' contenuto nel dizionario d*/
/*post: rimuove l'elemento x dal dizionario d */
void cancella(Dizionario d,Elem x){
    int i=0;

    int hash = funHash(x->key,i);

    for(int c=0;c<d->numchiavi;c++){
        if(d->content[hash] &&
           d->content[hash]!=d->DEL &&
           d->content[hash]->key==x->key){

            Elem tmp = d->content[hash];

            if(tmp->next){
                tmp->next->prec = tmp->prec;
                if(tmp->prec)
                    tmp->prec->next = tmp->next;
            }

            d->content[hash]=d->DEL;
            free(tmp);
            return; // appena trovo l'elemento da eliminare, esco.
        }
        hash=funHash(x->key,++i);
    }
    // Non dovrei arrivare qui data la precondizione.
}

/*post: restituisce un elemento con chiave val se esiste, NULL altrimenti */
Elem cerca(Dizionario d, int k){
    int i=0;
    int c=0;
    int hash = funHash(k,i);
    while(c++ < HASHSIZE && d->content[hash]){
        if(d->content[hash]->key==k)
            return d->content[hash];
        hash=funHash(k,++i);
    }
    return NULL;
}

int numChiavi(Dizionario d){
    return d->numchiavi;
}

/*pre: l'elemento x e' contenuto nel dizionario d */
/*post: restituisce la chiave di x*/
int leggiChiave(Dizionario d, Elem x){
    return x->key;
}

/*pre: l'elemento x e' contenuto nel dizionario d */
/*post: restituisce il valore di x*/
int leggiInfo(Dizionario d, Elem x){
    return x->info;
}

/*post: stampa il contenuto del dizionario */
void stampa(Dizionario d){
    for(Elem it = d->LAST_INSERTED;it!=NULL;it=it->prec)            // Nel peggiore dei casi e' lineare, nel migliore e' O(1)
        printf("m[%d]=%d \n",it->key,it->info);
}

void stampaInOrder(Dizionario d){
    Elem it = d->LAST_INSERTED;
    for(;it && it->prec;it=it->prec);
    for(;it!=NULL;it=it->next)
        printf("m[%d]=%d \n",it->key,it->info);
}



/*
ins: 34, 12, 18, 9.
canc 18
find 9
ins 42
*/
int main(){
    Dizionario d = crea();

    inserisci(d,34,-1);
    inserisci(d,12,-2);
    inserisci(d,18,-3);
    inserisci(d,9,-4);

    stampaInOrder(d);

    Elem x = cerca(d,18);

    cancella(d,x);

    stampaInOrder(d);

    return 0;
}


