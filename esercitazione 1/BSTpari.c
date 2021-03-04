#include <stdlib.h>
#include "tree.h"
#include "BSTpari.h"

Node build(Node r){
    if(r==NULL)return NULL;

    Node thisParent;

    if(r->key %2 != 0){
        thisParent = build(r->left);
    }else{
        thisParent = malloc(sizeof(struct node));
        thisParent->key=r->key;
        thisParent->left=build(r->left);
    }

    if(thisParent!=NULL)
        thisParent->right=build(r->right);
    else
        thisParent = build(r->right);

    return thisParent;
}

Tree BSTpari(Tree t){
    Tree ans=malloc(sizeof(struct tree));
    ans->root=build(t->root);
	return ans;
}
