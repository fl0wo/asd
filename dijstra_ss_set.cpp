#include <bits/stdc++.h>
#define INF 999999999
using namespace std;
#define max_nn 10000+1

/*
Example in.txt
2 1
1 2
1 2 1
*/

typedef long long ll;
vector <vector < pair<ll,ll> > > grafo(max_nn);
set <pair <ll,ll> > coda;
vector <ll> d(max_nn,LLONG_MAX);
vector <bool> b(max_nn,false);

ll n,m,s,f,i,da,a,peso;

void input();

void init_ss(){
    d[s] = 0;
	b[s] = true;
	coda.insert(make_pair(0,s));
}

void relax(ll da,ll verso, ll peso){
    if(d[verso]>peso){
        if(b[verso]) coda.erase(coda.find(make_pair(d[verso],verso)));
        else b[verso]=true;
        d[verso]=peso;
        coda.insert(make_pair(d[verso],verso));
    }
}

int main(){
    input();

    init_ss();

	ll x,y,z;

	while(!coda.empty()){
		auto it=coda.begin();
		x = (*it).second;
		coda.erase(it);
		
		// single source single destination ???
		if(x==f){
		    cout << d[f];
		    return 0;
		}

		for(i=0;i<grafo[x].size();i++){
			y = grafo[x][i].second;
			z = grafo[x][i].first;
			//relax
			relax(x,y,d[x]+z);
		}
	}

    cout << d[f];

     return 0;
}

void input(){
    freopen("in.txt","r",stdin);
    cin.tie(0);
    cin>>n>>m>>s>>f;
	s--;
	f--;
	while(m--){
        cin>>a>>da>>peso;
		a--;
		da--;
		grafo[a].push_back(make_pair(peso,da));
	}
}
