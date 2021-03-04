/*
Dato un nodo faccio una post order per eliminare prima tutte le foglie
poi risalendo faccio il free anche del nodo corrente.
Tempo O(n) dove n e' il numero di nodi interni + esterni del sottoalbero x
 */
void delall(Node x){
    if(!x)return;
    delall(x->left);
    delall(x->right);
    free(x);
}

/*
Questo metodo restituisce l'albero corrente, modificandolo man mano.
Complessita' temporale : O(n)
Nel peggiore dei casi, tutti i nodi sono maggiori di k, quindi andrebbero eliminati tutti.

Se non si dovesse cancellare fisicamente le chiavi ma solo logicamente?
Il tempo di esecuzione passerebbe da lineare a logaritmico.
la funzione delall(x) non andrebbe piu chiamata, e basterebbe impostare u->right=NULL

In questo modo visitando l'albero lungo l'altezza avremmo lo stesso risultato.
Tempo : O(h)
O(n) nel caso di un albero completamente sbilanciato dove h=n

In entrambi i casi Spazio : O(1)
*/
Node f(Node u,int k){
    if(!u) return NULL; // se null return null
    if(u->key>k){               // se la current key e' maggiore di k tutta la parte di dx e' da buttare
        delall(u->right);       // elimino i nodi di dx
        return f(u->left,k);    // ripeto l operazione, spostandomi a sx
    }
    u->right=f(u->right,k); // metto in questione la parte dx dell albero...
    return u; // forse spostandomi a dx trovero' un num > k
}

void eliminaMaggioriK(Tree t, int k) {
    t->root=f(t->root,k); // modifico il root in base al risultato di quella funzione
}