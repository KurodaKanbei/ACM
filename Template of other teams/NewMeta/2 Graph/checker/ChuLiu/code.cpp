#include <bits/stdc++.h>

using namespace std;

const int N = 1e3 + 7;
typedef long long VAL;
const long long INF = (1LL << 50);

int n, m;
pair<VAL, int> fv[N][N];
int parent[N];

struct DSU {
	int father[N];
	void clear(int n) {
		for (int i = 0; i < n; i++) father[i] = i;
	}
	int find(int u) {
		return father[u] == u ? u
			: father[u] = find(father[u]);
	}
	__inline int& operator [](int u) {
		return father[find(u)];
	}
	void merge(int i, int j) {
		i = find(i), j = find(j);
		if (i != j) father[i] = j;
	}
};

int root;
vector<pair<VAL, int>> G[N];

// O(V^2), add(u, v, w) -> fv[v][u] = {w, v};
// O(ElogE) 只需要使用支持打标记的可并堆维护即可。
// DSU 为并查集，需要重载 []。
VAL chuliu(int s) {
	VAL ret = 0; static DSU v, c; // int rid = 0;
	v.clear(n), c.clear(n);
	for (int u = 0; u < n; ++u) G[u].clear();
	for (int u = 0; u < n; ++u) if (u != s) {
		int uu = u;
		for (;;) { // 不求方案时 VAL e[][]; 即可
			int p = s;
			for (int it = 0; it < n; ++it) if (v[it] != uu)
				p = fv[uu][it] < fv[uu][p] ? it : p;
			if (fv[uu][p].first == INF) return INF;
			ret += fv[uu][p].first, parent[uu] = p;
			// if (p == s) root = fv[uu][p].second; // 实根
			for (int it = 0; it < n; it++) if (it != p && fv[uu][it].first != INF)
				fv[uu][it].first -= fv[uu][p].first;
			if (c[p] != c[u]) { c.merge(u, p); break; }
			// G[p].push_back({fv[uu][p].second, ++rid});
			for (int j = v[p]; j != v[u]; j = v[parent[j]]) {
				// G[parent[j]].push_back({fv[j][parent[j]].second, rid});
				for (int k = 0; k < n; ++k) fv[j][k] = min(fv[j][k], fv[uu][k]);
				uu = v[u] = j;
		}}}
	// ++rid;
	// for (int i = 0; i < n; ++i) if (i != s && v[i] == i) {
	// 	G[parent[i]].push_back({fv[i][parent[i]].second, rid}); }
	return ret;
}

void makeSol(int s) { // 用堆优化Prim构造方案
	static int dist[N];
	fill(dist, dist + n, 2 * n + 1); parent[s] = -1;
	for (multiset<pair<int, int>> h = {{0, s}}; !h.empty();) {
		int u = h.begin()->second; h.erase(h.begin()); dist[u] = 0;
		for (auto e : G[u]) if (e.second < dist[e.first]) {
			int v = e.first;
			h.erase({dist[v], v});
			h.insert({dist[v] = e.second, v});
			parent[v] = u; }}}

long long bak[N][N];

int main() {
	// while (scanf("%d %d", &n, &m) == 2) {
	while (true) {
		n = 1000, m = 10000;
		for (int i = 0; i <= n; i++) {
			for (int j = 0; j <= n; j++) {
				fv[i][j] = make_pair(INF, 0);
				bak[i][j] = INF;
			}
		}
		for (int i = 0; i < m; i++) {
			int s, t;
			long long c;
			// scanf("%d %d %lld", &s, &t, &c);
			s = rand() % n, t = rand() % n; c = rand();
			fv[t][s] = min(fv[t][s], make_pair(c, t));
			bak[t][s] = min(bak[t][s], c);
		}
		for (int i = 0; i < n; i++) {
			fv[i][n] = {INF / 2, i};
			bak[i][n] = INF / 2;
		}
		++n;
		VAL t = chuliu(n - 1);
		if (t >= INF) {
			puts("impossible");
		} else {
			makeSol(n - 1);
			// int root = 0;
			VAL all = 0;
			for (int i = 0; i < n - 1; i++) {
				// cout << parent[i] << endl;
				if (parent[i] == n - 1) root = i;
				all += bak[i][parent[i]];
			}
			assert(all == t);
			printf("%lld %d\n", t - INF / 2, root);
		}
		puts("");
	}
	return 0;
}
