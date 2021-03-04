
 
#define INF 2e9
 
// Dato x crea un Node con key=x
Node c(int x){
    Node u = (Node) malloc(sizeof(struct node));
    u->key=x;
    u->left=NULL;
    u->right=NULL;
    return u;
}

/**
Funzione che ti restituisce BST valido con una postorder=v, NULL se impossibile.
Inizialmente M=INF m=-INF
M e m sono rispettivamente il limite MAX e il limite min che un nodo x puo avere
durante una ricorsione.

Mano a mano che mi sposto a sx so che da questo momento tutti i nodi che incontro dovranno essere <
di root->key. Quindi se vado a sinistra imposto M = u->key.
Se vado a dx imposto m=u->key, perche' non posso avere nodi < di m.

Il discorso e' :

Se mi trovo nel sottoramo SX e ho sforato il limite di M (MAX), allora devo assolutamente tornare su
(nella stack trace della ricorsione) e provare a far settare quel valore ad un padre (fino a degenerare arrivando al root)

Se invece dovessi trovarmi in un sottoramo DX e volessi tornare in un sottoramo SX (quindi u->key < m (min))
Ecco che sforerei la mia postOrder.

Quindi doAble=0
e returno NULL.

Anche in questo caso l'algoritmo e' efficente.
Complessita' Temporale : O(n) lineare.
Visita preorder, visito un nodo al piu' una volta.
Spazio O(1) costante
*/
Node f(int v[],int d,int* i,int M,int m,int* doAble){
    if(*i>=d || v[*i]>=M || !(*doAble))return NULL;
    if(v[*i]<m){
        *doAble=0;
        return NULL;
    }
    Node u = c(v[*i]);
    (*i)++;
    u->left = f(v,d,i,u->key,m,doAble);
    u->right = f(v,d,i,M,u->key,doAble);
    return u;
}

Tree preOrder(int v[], int dim) {
    Tree t = (Tree) malloc(sizeof(struct tree));
    int i=0,doAble=1;
    t->root=f(v,dim,&i,INF,-INF,&doAble);
    if(!doAble) return NULL; // se non e' fattibile, returno NULL
    else return t;
}

// poco efficente O(n*n)
// ogni volta trovo i min e i max rispetto ad x 
// faccio i 2 array small e big...
Node f2(int v[],int d){
    if(d==0)return NULL;
    Node u = c(v[0]);
    int small[d],big[d],l=0,r=0;
    
    for(int i=0;i<d;i++){
        if(v[i]>v[0]) big[r++]=v[i];
        if(v[i]<v[0]) small[l++]=v[i];
    }
    u->left = f2(small,l);
    u->right = f2(big,r);
    return u;
}