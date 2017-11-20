void SPFA(int *dist) {
    static int line[maxn + 5];
    static bool hash[maxn + 5];
    int f = 0, r = 0;
    for(int i = 1; i <= N; i++) if(dist[i] < inf) line[r] = i, hash[i] = true, r = (r + 1) % (N + 1);
    while(f != r) {
        int t = line[f]; hash[t] = false, f = (f + 1) % (N + 1);
        for(int i = head[t]; i ; i = edge[i].next) {
            int v = edge[i].v, dt = dist[t] + edge[i].w;
            if(dt < dist[v]) {
                dist[v] = dt;
                if(!hash[v]) {
                    if(dist[v] < dist[line[f]]) f = (f + N) % (N + 1), line[f] = v;
                    else line[r] = v, r = (r + 1) % (N + 1);
                    hash[v] = true;
                }
            }
        }
    }
}
void solve()
{
    for(int i = 1; i <= S; i++) {
        for(int j = 1; j <= N; j++)
            for(int k = (i - 1) & i; k ; k = (k - 1) & i) G[i][j] = std::min(G[i][j], G[k][j] + G[k ^ i][j]);
        SPFA(G[i]);
    }
}
