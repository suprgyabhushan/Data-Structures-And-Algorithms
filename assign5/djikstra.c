#include<stdio.h>

 
#define MAX 100001
#define INF (1<<20)
 
struct comp {
    bool operator() (const pii &a, const pii &b) {
        return a.second > b.second;
    }
};
 

int D[MAX];
bool F[MAX];
 
int main(int argc,char *argv[]) {
    int i, u, v, w, sz, nodes, edges, starting;
 	FILE *f;
f=fopen(argv[1],"r");
    // create graph
    fscanf(f,"%d",&edges);
    for(i=0; i<edges; i++) {
        fscanf(f,"%d %d %d", &u, &v, &w);
        G[u].pb(pii(v, w));
        G[v].pb(pii(u, w)); // for undirected
    }
    
 
    // initialize distance vector
    for(i=1; i<=nodes; i++) D[i] = INF;
    D[starting] = 0;
    Q.push(pii(starting, 0));
 
    // dijkstra
    while(!Q.empty()) {
        u = Q.top().first;
        Q.pop();
        if(F[u]) continue;
        sz = G[u].size();
        for(i=0; i<sz; i++) {
            v = G[u][i].first;
            w = G[u][i].second;
            if(!F[v] && D[u]+w < D[v]) {
                D[v] = D[u] + w;
                Q.push(pii(v, D[v]));
            }
        }
        F[u] = 1; // done with u
    }
 
    // result
    for(i=1; i<=nodes; i++) printf("Node %d, min weight = %d\n", i, D[i]);
    return 0;
}
