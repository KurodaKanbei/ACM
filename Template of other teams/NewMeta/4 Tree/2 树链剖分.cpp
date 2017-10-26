#define fors(i) for (auto i : e[x]) if (i != p)
int cnt; ai s, h, top, pa, dfn /*,hea*/;
int size(int x, int p)
{ s[x] = 1; fors(i) s[x] += size(i, x); return s[x]; }
void dfs(int x, int p, int t) {
	pa[x] = p, top[x] = t, h[x] = h[p] + 1, dfn[x] = ++cnt;
	int y = 0; // int &y = hea[x] = 0;
	fors(i) if (s[y] < s[i]) y = i;
	if (y) dfs(y, x, t);
	fors(i) if (i != y) dfs(i, x, i);
}
void build() { size(1, 0); cnt = 0; dfs(1, 0, 1); }
void path(int x, int y) {
	while (top[x] != top[y])
		if (h[top[x]] >= h[top[y]]) {
			foo(dfn[top[x]], dfn[x]); x = pa[top[x]];
		} else { // swap(x, y); 边权无向时可改用这句 
			foo(dfn[top[y]], dfn[y]); y = pa[top[y]];
		}
	if (dfn[x] < dfn[y]) foo(dfn[x], dfn[y]);
	else foo(dfn[y], dfn[x]); // 边权时注意开闭 
}
void subtree(int x) { foo(dfn[x], dfn[x] + s[x] - 1); }