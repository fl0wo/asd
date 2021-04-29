#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MAXN 10000

/*
Example in.txt
2 1
1 2
1 2 1
*/

typedef pair<int,ll> pil;
vector<vector<pair<int,ll>>> graph(MAXN);
vector<ll> dist(MAXN,1e16);
vector<int> parent;
vector<bool> visited(MAXN,false);
deque<int> q;
ll n,m,a,b,c,s,u;

#define pc(x) putchar(x)
#define gc() getchar()

void input(){
    freopen("in.txt","r",stdin);
    //freopen("output.txt","w",stdout);

    cin >> n >>m>>s>>u;

    s--;
    u--;

    while(m--){
        cin>>a>>b>>c;
        a--;b--;
        graph[a].push_back(make_pair(b,c));
    }
}

void init_ss(){
    dist[s]=0;
    q.push_back(s);
}

void relax(ll da,ll verso,ll peso){
    if (dist[verso] > peso){
        dist[verso] = peso;
        //  parent[verso] = da;
        if(!visited[verso]) q.push_front(verso);
        else q.push_back(verso);
        visited[verso]=1;
    }
}

int main(){
    input();
    init_ss();
    
    while(!q.empty()){
        int v = q.front();
        visited[v] = 1;
        q.pop_front();
        
        for(pil adj : graph[v]){
            ll verso = adj.first;
            ll peso = adj.second;
            relax(v,verso,dist[v]+peso);
        }
    }
    cout << (dist[u]);
    return 0;
}
