/*
Soluzione :
Vado alla ricerca di un nodo contenente K, se lo trovo, a quel punto
guardo spostandomi sia a sx che a dx.

Complessita' Temporale : O(h) 
Visito l'albero lungo l'altezza, avendo un BST posso evitare la visita di tutti i nodi.
Nel caso peggiore (bst completamente sbilanciato) abbiam h=n quindi O(n) o O(h)

Spazio O(1) perche' non viene allocata memoria aggiuntiva.
 */
int f(Node x,int k){
    if(!x)return 0;
    if(x->key==k) return 1 + f(x->left,k) + f(x->right,k);
    if(x->key>k) return f(x->left,k);
    else return f(x->right,k);
}
int contaOcc(Tree t, int k) {
    return f(t->root,k);
}