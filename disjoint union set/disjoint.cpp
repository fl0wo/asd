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
    int t[MAXN]; // tree parental
    int r[MAXN]; // rank

    disj(int cap){
        this->cap=cap;
    }

    void MAKESET(int x){
        t[x]=x;
        r[x]=1;
    }

    int FINDSET(int x){
        if(t[x]==x)return x;
        int p = FINDSET(t[x]);
        // path compression
        t[x]=p;
        return p;
    }

    void UNION(int x,int y){
        int p1 = FINDSET(x);
        int p2 = FINDSET(y);

        if(r[p1]<r[p2]){
            t[p1]=p2; // ascendor union
            r[p2]+=r[p1];
        }else{
            cout << " dioboia " << t[p2] << " : " << t[p1] << endl;
            t[p2]=p1; // ascendor union
            r[p1]+=r[p2];
            cout << " dioboia " << t[p2] << " : " << t[p1] << endl;
        }
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


