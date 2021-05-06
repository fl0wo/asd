#include<bits/stdc++.h>
#define MAXN 200
#define INF 2e8
#define pb push_back
#define mp make_pair
#define FOR(i,a,b) for(int i=a;i<=b;++i)
#define FOREACH(i,b) for(auto i : b)
#define REP(i,n) FOR(i,0,n-1)
#define CHAR_OFFSET 'a'
using namespace std;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<vi> vvi;
typedef vector<pii> vpii;

struct edge {
    int w = INF, to = -1;
    bool operator<(edge const& o) const {
        return w<o.w;
    }
};


int key[MAXN]; // valore del peso minimo dell arco che collega u all albero in costruzione
int pi[MAXN]; // predecessore di u nel grafo che si sta costruendo
bool visited[MAXN]; // mi dice se quel nodo l'abbiamo già visitato

int N,E;
vector<edge> g[MAXN];
set<edge> Q;


void input();

// O(log N)
int extractMin(set<edge> &Q){
    int v = Q.begin()->to;
    Q.erase(Q.begin());
    return v;
}

// O(N log M)
// N =|V| e M = |E|
int main(){
    input();

    // MST radicato in ROOT
    int ROOT = 0;
    int ans=0;

    // O(n)
    REP(i,N)
        key[i]=+INF;

    key[ROOT]=0; // per arrivare a ROOT ci metto 0
    pi[ROOT]=-1; // il padre di ROOT non esiste

    set<edge> Q; // Min Heap (implementato come BST)

    // peso 0 per andare al nodo ROOT perche parto da ROOT
    Q.insert({0,ROOT});

    // O(N)
    while(!Q.empty()){

        // Estraggo il nodo minimo (inizialmente root)
        // O(log M)
        int u=extractMin(Q);

        // Una volta estratto non dovrò più
        visited[u]=1;

        FOREACH(adj,g[u]){

            int v = adj.to;
            int w = adj.w;

            if(!visited[v] && w < key[v]){
                Q.erase({key[v], v});  // Aggiorno la coda

                key[v] = w; // Modifico il peso per arrivare a v
                pi[v] = u; // Modifico il parent per arrivare a v

                Q.insert({key[v], v}); // Aggiorno la coda
            }
        }
    }

    REP(i,N){
        if(pi[i]!=-1){
            cout << i << " " << pi[i] << " -> " <<  key[i] << endl;
            ans+=key[i];
        }
    }

    cout << ans << endl;

    return 0;
}



void input(){
    /*
        a b c d e f g h i
        0 1 2 3 4 5 6 7 8
    */
    freopen("in.txt","r",stdin);
    cin.tie(0);
    cin>>N>>E;

    REP(i,E){
        char da,a;
        int w;
        cin>>da>>a>>w;
        da-=CHAR_OFFSET;
        a-=CHAR_OFFSET;
        g[da].pb({w,a}); // oriented
        g[a].pb({w,da}); // non oriented
    }
}

