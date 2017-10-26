vector<pair<VAL, int>> G[N], fv[N][N];
int n, m, parent[N];
// O(V^2), add(u, v, w) -> fv[v][u] = {w, v};
// O(ElogE) 只需要使用支持打标记的可并堆维护即可
// DSU 为并查集，需要重载 [], 不求方案时 VAL e[][]; 即可
VAL chuliu(int s) {
	VAL ret = 0; static DSU v, c; // int rid = 0;
	v.clear(n), c.clear(n);
	for (int u = 0; u < n; ++u) G[u].clear();
	for (int u = 0; u < n; ++u) if (u != s) {
		int uu = u;
		for (;;) {
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
