#include<bits/stdc++.h>
#define MAXN 200
#define INF 2e8
#define pb push_back
#define mp make_pair
#define node second
#define w first
#define FOR(i,a,b) for(int i=a;i<=b;++i)
#define REP(i,n) FOR(i,0,n-1)
using namespace std;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<vi> vvi;


struct disj{
    int cap;
    int p[MAXN]; // tree parental
    int r[MAXN]; // rank

    disj(int cap){
        this->cap=cap;
    }

    void MAKESET(int x){
        p[x]=x;
        r[x]=1;
    }

    int FINDSET(int x){
        if(p[x]==x)return x;
        int par = FINDSET(p[x]);
        // path compression
        p[x]=par;
        return par;
    }

    void UNION(int x,int y){
        x = FINDSET(x);
        y = FINDSET(y);

        if(r[x]>r[y])
			p[y]=x;
		else
			p[x]=y;

		if(r[x]==r[y])
			r[y]++;
    }

    void printGroups(){
        set<int> s;
        REP(i,cap){
            int x = FINDSET(i);
            s.insert(x);
        }
        for(int x : s){
            cout<<"{ ";
            REP(i,cap){
                int y = FINDSET(i);
                if(x==y) cout<<i<<" ";
            }
            cout<<"}\n";
        }
    }
};

int main(){

    disj d(10);

    REP(i,10)
        d.MAKESET(i);

    d.UNION(1,5);
    d.UNION(5,6);
    d.UNION(7,8);
    d.UNION(2,9);
    d.UNION(1,8);

    d.printGroups();

    return 0;
}
