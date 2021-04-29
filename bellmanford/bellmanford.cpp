#include<bits/stdc++.h>
#define MAXN 100
#define INF 2e8
#define pb push_back
#define mp make_pair
#define node second
#define w first

#define FOR(i,a,b) for(int i=a;i<=b;++i)
#define REP(i,n) FOR(i,0,n-1)
#define WANT_NEG_CYCLE false

using namespace std;
typedef pair<int,int> pii;
vector<pii> g[MAXN];
int N,E;
int s,f; // source , destination

int d[MAXN]; // distances
int p[MAXN]; // parents

bool negcycle=0;

void input();
void add_neg_cycle();
void ans();

void init_ss(){
    REP(i,N){
        d[i]=INF;
        p[i]=-1;
    }
    d[s]=0; // im already at source.
}

void relax(int u,int v,int w){
    if(d[v]>d[u]+w){ // int overflow
        d[v] = d[u]+w;
        p[v] = u;
    }
}

int main(){
    input();

    init_ss();

    REP(i,N-1)   // n-1 times
        REP(i,N) // all nodes
            for(pii adj:g[i]) // for each node all out-coming edges
                relax(i,adj.node,adj.w);


    // now check if there's negative cycles
    REP(i,N)
        for(pii adj:g[i])
            if(d[adj.node]>d[i]+adj.w)
                negcycle=1;

    ans();
    return 0;
}

void ans(){
    cout << "negcycles = " << negcycle<<"\n";
    cout << "[bellmanford]\nfrom " << s << " to " << f << " w = " << d[f]<<"\n";
    if(negcycle)return;
    int it=f;
    cout << "f : ";
    do{
        cout << it << " <- ";
    }while((it=p[it])!=-1);
    cout << "s";
}

void input(){
    freopen("in.txt","r",stdin);
    cin.tie(0);
    cin>>N>>E>>s>>f;
    REP(i,E){
        int from,to,w;
        cin>>from>>to>>w;
        g[from].pb(mp(w,to));
    }
    if(WANT_NEG_CYCLE)
        add_neg_cycle();
}


void add_neg_cycle(){
    g[0].pb(mp(-1,1));
    g[1].pb(mp(0,0));// from 0 to back 0 between 1 sum = -1
    E+=2; // added 2 more edges of corse
}
