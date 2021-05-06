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

vpii g[MAXN];
int N,E;
bool visited[MAXN];

void dfs(int v) {
    if(visited[v])return;

    visited[v]=1;

    cout << v << endl;

    FOREACH(u,g[v])
        dfs(u.first);
}

void input();

int main(){
    input();
    REP(i,N)
        dfs(i);
}

void input(){
    freopen("in.txt","r",stdin);
    cin.tie(0);
    cin>>N>>E;

    REP(i,E){
        char da,a;
        int w;
        cin>>da>>a>>w;
        da-=CHAR_OFFSET;
        a-=CHAR_OFFSET;
        g[da].pb(mp(a,w)); // oriented
        //g[a].pb(mp(da,w)); // non oriented
    }
}
