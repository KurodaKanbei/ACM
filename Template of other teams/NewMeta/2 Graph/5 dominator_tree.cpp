// 1 base, O(m)
int n;
Array dfn, id, pa, semi, idom, p, mn; vector<int> be[N], dom[N]; int cnt;
vector<int> e[N];
void dfs(int x) {
	dfn[x] = ++cnt; id[cnt] = x;
	for (auto i : e[x]) {
		if (!dfn[i]) { dfs(i); pa[dfn[i]] = dfn[x]; }
		be[dfn[i]].pb(dfn[x]);
}}
int get(int x) {
	if (p[x] != p[p[x]]) {
        if (semi[mn[x]] > semi[get(p[x])]) mn[x] = get(p[x]);
		p[x] = p[p[x]];
	}
	return mn[x];
}
void LT() {
	for (int i = cnt; i > 1; --i) {
		for (auto j : be[i]) semi[i] = min(semi[i], semi[get(j)]);
		dom[semi[i]].pb(i);
		int x = p[i] = pa[i];
		for (auto j : dom[x])
			idom[j] = (semi[get(j)] < x ? get(j) : x);
		dom[x] = {};
	}
	for (int i = 2; i <= cnt; ++i) {
		if (idom[i] != semi[i]) idom[i] = idom[idom[i]];
		dom[id[idom[i]]].pb(id[i]); // dom is dominator tree's son list
}}
void build(int s) {
	for (int i = 1; i <= n; ++i) {
		dfn[i] = 0; dom[i] = be[i] = {};
		p[i] = mn[i] = semi[i] = i;
	}
	cnt = 0; dfs(s); LT();
}
