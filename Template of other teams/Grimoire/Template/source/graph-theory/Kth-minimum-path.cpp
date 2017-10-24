//需保证GivenEdge里面边的顺序和Edge中一样
//两个优先队列要考虑大根还是小根
//heap总是小根堆
//dij不能求正权最长路
//INF or -INF

typedef long long LL;
MAXN, MAXK, MAXN, INF //int or LL, it depends
const int MAXNODE = MAXN + MAXM * 2;   // m + nlgm ???
bool used[MAXN];
int n, m, cnt, S, T, Kth, N;// m is number of all edges
int rt[MAXN], seq[MAXN], adj[MAXN], from[MAXN], dep[MAXN];
LL dist[MAXN], w[MAXM], ans[MAXK];

struct GivenEdge {  //edge given from origin input
    int u, v, w;
    GivenEdge() {};
    GivenEdge(int _u, int _v, int _w): u(_u), v(_v), w(_w) {};
} edge[MAXM];

struct Edge {
    int v, nxt, w;
    Edge() {};
    Edge(int _v, int _nxt, int _w): v(_v), nxt(_nxt), w(_w) {};
} e[MAXM];

inline void addedge(int u, int v, int w) {
    e[++cnt] = Edge(v, adj[u], w); adj[u] = cnt;
}

inline void dij(int S) {  //dij in original graph, spfa if needed
    for (int i = 1; i <= N; ++i) {
        dist[i] = INF;
        dep[i] = INF;
        used[i] = false;
        from[i] = 0;
    }
    static priority_queue<pair<LL, int>, vector<pair<LL, int> >, greater<pair<LL, int> > > hp;
    while (!hp.empty()) hp.pop();
    hp.push(make_pair(dist[S] = 0, S));
    dep[S] = 1;
    while (!hp.empty()) {
        pair<LL, int> now = hp.top();
        int u = now.second;
        hp.pop();
        if (used[u]) {
        	continue;
        } else {
        	used[u] = true;
        }
        for (int p = adj[u]; p; p = e[p].nxt) {
            int v = e[p].v;
            if (dist[u] + e[p].w < dist[v]) {  //different when max or min
                dist[v] = dist[u] + e[p].w;
                dep[v] = dep[u] + 1;
                from[v] = p;
                hp.push(make_pair(dist[v], v));
            }
        }
    }
    for (int i = 1; i <= m; ++i) w[i] = 0;
    for (int i = 1; i <= N; ++i)
        if (from[i]) w[from[i]] = -1;
    for (int i = 1; i <= m; ++i) {
        if (~w[i] && dist[edge[i].u] < INF && dist[edge[i].v] < INF) {
            w[i] = -dist[edge[i].u] + (dist[edge[i].v] + edge[i].w);　　//different when max or min
        } else {
        	w[i] = -1;
        }
    }
}

inline bool cmp_dep(int p, int q) {
    return dep[p] < dep[q];
}

struct Heap {
    LL key;
    int id, lc, rc, dist;
    Heap() {};
    Heap(LL k, int i, int l, int r, int d): key(k), id(i), lc(l), rc(r), dist(d) {};
    inline void clear() {
    	key = 0;
    	id = lc = rc = dist = 0;
    }
} hp[MAXNODE];

inline int merge_simple(int u, int v) {
    if (!u) return v;
    if (!v) return u;
    if (hp[u].key > hp[v].key) {
        swap(u, v);
    }
    hp[u].rc = merge_simple(hp[u].rc, v);
    if (hp[hp[u].lc].dist < hp[hp[u].rc].dist) {
        swap(hp[u].lc, hp[u].rc);
    }
    hp[u].dist = hp[hp[u].rc].dist + 1;
    return u;
}

inline int merge_full(int u, int v) {
    if (!u) return v;
    if (!v) return u;
    if (hp[u].key > hp[v].key) {
        swap(u, v);
    }
    int nownode = ++cnt;
    hp[nownode] = hp[u];
    hp[nownode].rc = merge_full(hp[nownode].rc, v);
    if (hp[hp[nownode].lc].dist < hp[hp[nownode].rc].dist) {
        swap(hp[nownode].lc, hp[nownode].rc);
    }
    hp[nownode].dist = hp[hp[nownode].rc].dist + 1;
    return nownode;
}

priority_queue<pair<LL, int>, vector<pair<LL, int> >, greater<pair<LL, int> > > Q;

int main() {
	scanf("%d%d%d", &n, &m, &Kth);
	for (int i = 1; i <= m; ++i) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		edge[i] = {u, v, w};
	}
	N = ;
    S = ;
    T = ;
    memset(adj, 0, sizeof(*adj) * (N + 1));
    cnt = 0;
    for (int i = 1; i <= m; ++i) {
    	addedge(edge[i].v, edge[i].u, edge[i].w); // important!!! reverse the edge
    }
    dij(T); 
    if (dist[S] == INF) {   //must judge before building heaps; -INF if max kth
    	...
    	return 0;
    }
    for (int i = 1; i <= N; ++i) {
        seq[i] = i;
    }
    sort(seq + 1, seq + N + 1, cmp_dep);

	cnt = 0;
	memset(adj, 0, sizeof(*adj) * (N + 1));
	memset(rt, 0, sizeof(*rt) * (N + 1));
    for (int i = 1; i <= m; ++i) {
        addedge(edge[i].u, edge[i].v, edge[i].w);
    }
	rt[T] = cnt = 0;  // now cnt is total nodes in heaps 
	hp[0].dist = -1;
	for (int i = 1; i <= N; ++i) {
		int u = seq[i], v = edge[from[u]].v;
		rt[u] = 0;
		for (int p = adj[u]; p; p = e[p].nxt) {
		    if (~w[p]) {
		        hp[++cnt] = Heap(w[p], p, 0, 0, 0);
		        rt[u] = merge_simple(rt[u], cnt);
		    }
		}
		if (i == 1) continue;
		rt[u] = merge_full(rt[u], rt[v]);
	}
	while (!Q.empty()) Q.pop();
	Q.push(make_pair(dist[S], 0));
	edge[0].v = S;
	for (int kth = 1; kth <= Kth; ++kth) {
		if (Q.empty()) {
		    ans[kth] = -1;
		    continue;
		}
		pair<LL, int> now = Q.top(); Q.pop();
		ans[kth] = now.first;
		int p = now.second;
		if (hp[p].lc) {
		    Q.push(make_pair(+hp[hp[p].lc].key + now.first - hp[p].key, hp[p].lc));//different when max or min
		}
		if (hp[p].rc) {
		    Q.push(make_pair(+hp[hp[p].rc].key + now.first - hp[p].key, hp[p].rc));//different when max or min
		}
		if (rt[edge[hp[p].id].v]) {
		    Q.push(make_pair(hp[rt[edge[hp[p].id].v]].key + now.first, rt[edge[hp[p].id].v]));//different when max or min
		}
	}
	...
	for (int i = 1; i <= cnt; ++i) {
		hp[i].clear();
	}
}
