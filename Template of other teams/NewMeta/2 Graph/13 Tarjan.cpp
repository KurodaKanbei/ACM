int dfn[N], low[N], tot_color, ins[N], color[N];
vector<int> adj[N], stk;
// 无向图割点，割边，边双连通分量
int tarjan(int u, int from) {
	static int tot = 0;
	low[u] = dfn[u] = ++tot;
	stk.push_back(u);
	for (auto v : adj[u]) {
		if (v == from) continue; // 有重边的话，要判断不能走来的时候的边
		low[u] = min(low[u], dfn[v] ? dfn[v] : tarjan(v, u));
		// low[v] > dfn[u] ==> u <-> v 为割边
		// low[v] >= dfn[u] 且 u 不为根，则 u 为割点
	}
	// 若 u 为根，且至少有两个孩子 $v_1, v_2$, 满足 low[v1,v2] >= dfn[u], 则根为割点
	// 如果不用求边双连通分量，可以去掉 stk 部分 和之后的弹栈部分
	if (low[u] == dfn[u]) {
		int t; ++tot_color;
		do { t = stk.back(); stk.pop_back();
			color[t] = tot_color; ins[t] = false;
		} while (t != u);
	} return low[u];
}
// 无向图点双连通分量，注意有向图求不了
// dfn 一开始需要赋值为 0
vector<vector<pair<int, int>> > bcc;
vector<pair<int, int>> stk;
int tarjan(int u, int fu) {
	static int tot = 0;
	low[u] = dfn[u] = ++tot;
	for (auto v : adj[u]) {
		if (v == fu) continue;
		if (dfn[v] < dfn[u]) stk.push_back({u, v});
		if (!dfn[v]) {
			low[u] = min(low[u], tarjan(v, u));
			if (low[v] >= dfn[u]) {
				bcc.push_back({});
				do { bcc.back().push_back(stk.back());
					stk.pop_back();
				} while (bcc.back().back() != make_pair(u, v));
			}
		} else low[u] = min(low[u], dfn[v]);
	} return low[u];
}
