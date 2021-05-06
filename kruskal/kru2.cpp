#include<bits/stdc++.h>
using namespace std;
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

#define MAXM 100+1

typedef pair<int, int> iPair;

struct Graph{
	int V, E;
	vector< pair<int, iPair> > edges;

	// Constructor
	Graph(int V, int E)
	{
		this->V = V;
		this->E = E;
	}

	// Utility function to add an edge
	void addEdge(int u, int v, int w)
	{
		edges.push_back({w, {u, v}});
	}

	// Function to find MST using Kruskal's
	// MST algorithm
	int kruskalMST();
};

// To represent Disjoint Sets
struct DisjointSets
{
	int *parent, *rnk;
	int n;

	// Constructor.
	DisjointSets(int n)
	{
		// Allocate memory
		this->n = n;
		parent = new int[n+1];
		rnk = new int[n+1];

		// Initially, all vertices are in
		// different sets and have rank 0.
		for (int i = 0; i <= n; i++)
		{
			rnk[i] = 0;

			//every element is parent of itself
			parent[i] = i;
		}
	}


	int find(int u){
		if (u != parent[u])
			parent[u] = find(parent[u]);
		return parent[u];
	}

	void merge(int x, int y){
		x = find(x), y = find(y);

		if (rnk[x] > rnk[y])
			parent[y] = x;
		else // If rnk[x] <= rnk[y]
			parent[x] = y;

		if (rnk[x] == rnk[y])
			rnk[y]++;
	}
};


int Graph::kruskalMST(){
	int mst_wt = 0;

	sort(edges.begin(), edges.end());

	DisjointSets ds(V);

	vector< pair<int, iPair> >::iterator it;
	for (it=edges.begin(); it!=edges.end(); it++){
		int u = it->second.first;
		int v = it->second.second;

		int set_u = ds.find(u);
		int set_v = ds.find(v);

		if (set_u != set_v){
            char xu = ((char)u+'a');
            char xv = ((char)v+'a');

			cout << xu << " - " << xv << " : " << it->first <<  endl;

			mst_wt += it->first;

			ds.merge(set_u, set_v);
		}
	}

	return mst_wt;
}

inline int bitdiff(string s1,string s2){
    int w=0;
    for(int i=0;i<s1.size();i++)
        w+=s1[i]!=s2[i];
    return w;
}

int main(){
    freopen("in.txt", "r", stdin);

	int N, E;
    cin >> N >> E;
    int V = N;
	Graph g(V,E);

    REP(i,E){
        char da,a;
        int w;
        cin>>da>>a>>w;
        da-=CHAR_OFFSET;
        a-=CHAR_OFFSET;
        g.addEdge(da,a,w);
    }
	int mst_wt = g.kruskalMST();
	cout << mst_wt;
	return 0;
}

