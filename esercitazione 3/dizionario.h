typedef struct dizionario *Dizionario;
typedef struct elem *Elem;

Dizionario crea();
void inserisci(Dizionario d, int k, int val);
void cancella(Dizionario d, Elem e);
Elem cerca(Dizionario d, int k);
int numChiavi(Dizionario d);
int leggiChiave(Dizionario d, Elem e);
int leggiInfo(Dizionario d, Elem e);
void stampa(Dizionario d);
