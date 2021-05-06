#include<bits/stdc++.h>
#define MAXN 200
#define INF 2e8
#define pb push_back
#define mp make_pair
#define node second
#define w first
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

// Disjoint Union Set (without rank)
vi p; // parents

// O(1)
void MAKE_SET(int x) {
    p[x] = x;
}

// O(log N)
int FIND_SET(int x) {
    if(p[x]==x)return x;
    return p[x]=FIND_SET(p[x]);
}

// O(log N)
void UNION_SET(int x, int y) {
    x = FIND_SET(x);
    y = FIND_SET(y);
    if(x!=y)p[x]=y; // union
}

// Edges
struct edge {
    int u,v,w;
    bool operator<(edge const& b) {
        return w<b.w;
    }
};

vector<edge> edges;
int N,E;

void input();


// O(M log M) Kruskal
int main(){
    input();

    int cost = 0;
    vector<edge> pi; // sottoalbero libero MST

    // O(n)
    REP(i,N+1)
        MAKE_SET(i);

    // O(M * log M) M = |E|
    sort(edges.begin(), edges.end());

    // O(M)
    FOREACH(e, edges)
        if(FIND_SET(e.u)!=FIND_SET(e.v)){ // O(log M)
            cost += e.w;
            pi.push_back(e);
            UNION_SET(e.u,e.v);
        }



    cout << "cost : " << cost << endl;
    FOREACH(e, pi)
        cout << ((char)(e.u+CHAR_OFFSET))  << "-" << ((char)(e.v+CHAR_OFFSET)) << " : " << e.w <<endl;

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

    p.resize(N+1);

    REP(i,E){
        char da,a;
        int w;
        cin>>da>>a>>w;
        da-=CHAR_OFFSET;
        a-=CHAR_OFFSET;

        //g[da].pb(mp(a,w)); // oriented
        //g[a].pb(mp(da,w)); // non oriented
        edges.pb({da,a,w}); // edges
    }
}


