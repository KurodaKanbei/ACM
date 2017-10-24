//solve(s, n, raw_g): s is the root and base accords to base of raw_g
//idom[x] will be x if x does not have a dominator,and will be -1 if x is not reachable from s.

struct dominator_tree {
	int base, dfn[N], sdom[N], idom[N], id[N], f[N], fa[N], smin[N], stamp;
	Graph *g;
	void predfs(int u) {
		id[dfn[u] = stamp++] = u;
		for (int i = g -> adj[u]; ~i; i = g -> nxt[i]) {
			int v = g -> v[i];
			if (dfn[v] < 0) {
				f[v] = u;
				predfs(v);
			}
		}
	}
	int getfa(int u) {
		if (fa[u] == u) return u;
		int ret = getfa(fa[u]);
		if (dfn[sdom[smin[fa[u]]]] < dfn[sdom[smin[u]]]) 
			smin[u] = smin[fa[u]];
		return fa[u] = ret;
	}
	void solve (int s, int n, Graph *raw_graph) {
		g = raw_graph;
		base = g -> base;
		memset(dfn + base, -1, sizeof(*dfn) * n);
		memset(idom + base, -1, sizeof(*idom) * n);
		static Graph pred, tmp;
		pred.init(base, n);
		for (int i = 0; i < n; ++i) {
			for (int p = g -> adj[i + base]; ~p; p = g -> nxt[p])
				pred.ins(g -> v[p], i + base);
		}
		stamp = 0; tmp.init(base, n); predfs(s);
		for (int i = 0; i < stamp; ++i) {
			fa[id[i]] = smin[id[i]] = id[i];
		}
		for (int o = stamp - 1; o >= 0; --o) {
			int x = id[o];
			if (o) {
				sdom[x] = f[x];
				for (int i = pred.adj[x]; ~i; i = pred.nxt[i]) {
					int p = pred.v[i];
					if (dfn[p] < 0) continue;
					if (dfn[p] > dfn[x]) {
						getfa(p);
						p = sdom[smin[p]];
					}
					if (dfn[sdom[x]] > dfn[p]) sdom[x] = p;
				}
				tmp.ins(sdom[x], x);
			}
			while (~tmp.adj[x]) {
				int y = tmp.v[tmp.adj[x]];
				tmp.adj[x] = tmp.nxt[tmp.adj[x]];
				getfa(y);
				if (x != sdom[smin[y]]) idom[y] = smin[y];
				else idom[y] = x;
			}
			for (int i = g -> adj[x]; ~i; i = g -> nxt[i]) 
				if (f[g -> v[i]] == x) fa[g -> v[i]] = x;
		}
		idom[s] = s;
		for (int i = 1; i < stamp; ++i) {
			int x = id[i];
			if (idom[x] != sdom[x]) idom[x] = idom[idom[x]];
		}
	}
};
