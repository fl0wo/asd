#include <stdlib.h>
#include "tree.h"
#include "distanzaminima.h"

#define INF 99999999
/*
    bst
    |x-l| |x-r|
*/
int abs(int a){
    //...
}

int minf(int a,int b){
    return a>b?b:a;
}

int maxf(int a,int b){
    return a<b?b:a;
}

int isleaf(Node u){
    return u->left==NULL && u->right==NULL;
}

// O(n)
void f(Node u,int* a,int* min,int* max){
    if(u==NULL)return;
    if(isleaf(u)){
        (*min)=minf(u->key,(*min));
        (*max)=maxf(u->key,(*max));
        return;
    }

    f(u->left,a,min,max);

    //freeze
    int maxL=(*max);

    f(u->right,a,min,max); // ?

    //freeze
    int minR=(*min);

    // info about leafs

    (*a)=minf( *a,abs(u->key-minR));
    (*a)=minf( *a,abs(u->key-maxL));

    (*min)=minf(u->key,(*min)); // yes
    (*max)=maxf(u->key,(*max)); // yes
}

int distanzaminima(Tree t){
    int ans=INF;
    int min=INF,max=-INF;
    f(t->root,&ans,&min,&max);
	return ans;
}
