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

/*
A simple way to make in work in O(n²) in space
is to use to matrices to store the intermediate values,
(one for k odd, one for k even), and alternate between them.
Then there is no need to make a new proof for
correctness since there is the guarantee that no updated values will be used.
*/

int N,E;
int g[MAXN][MAXN];

//     k     i      j
int d[MAXN][MAXN][MAXN];

void input();
void ans();

int main(){
    input();

    REP(i,N)
        REP(j,N){
            if(i==j) d[0][i][j]=0;
            else if(g[i][j]!=0) d[0][i][j]=g[i][j];
            else d[0][i][j]=INF;
        }

    FOR(k,1,N)
        REP(i,N)
            REP(j,N)
                d[k][i][j]=min(d[k-1][i][j],d[k-1][i][k] + d[k-1][k][j]);

    ans();
    return 0;
}

void input(){
    freopen("in.txt","r",stdin);
    cin.tie(0);
    cin>>N>>E;

    REP(i,E){
        int da,a,w;cin>>da>>a>>w;
        g[da][a]=w;
        // g[a][da]=w; // non oriented?
    }
}

void ans(){
    REP(i,N)
        REP(j,N)
            printf("d[%d][%d]=%d\n",i,j,d[N-1][i][j]);
}
