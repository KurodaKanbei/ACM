vector<int> adj[N], lst[N]; int rk[N], deg[N], tim[N], stmp, n;
vector<int> mcs(int n) {
	fill(deg + 1, deg + n + 1, 0);
	fill(rk + 1, rk + n + 1, 0);
	for (int i = 1; i <= n; i ++) lst[0].push_back(i);
	int ptr(0);
	for (int i = n; i >= 1; i --) {
		int p;
		for(; ;) {
			while (lst[ptr].empty()) ptr--;
			if (rk[lst[ptr].back()]) lst[ptr].pop_back();
			else {
				p = lst[ptr].back(); lst[ptr].pop_back(); break;
			}
		}
		rk[p] = i;
		for(int i : adj[p]) if(!rk[i]) {
			ptr = max(ptr, ++deg[i]);
			lst[deg[i]].push_back(i);
		}
	}
	vector<int> ret(n);
	for(int i = 1; i <= n; i ++) ret[rk[i] - 1] = i;
	return ret;
} // 点从1开始标号, n 为点数, adj 为边表
int main() {
	static vector<vector<int> > chk[N];
	for(int i(0); i <= n; i++) adj[i].clear(), chk[i].clear(), lst[i].clear();
	vector<int> ord = mcs(n); // ord 是完美消除序列当且仅当原图是弦图
	for(int i(0); i < n; i++) {
		int v(ord[i]);
		vector<int> c;
		int mn(n);
		for(int y : adj[v]) if(rk[y] > rk[v]) {
			c.push_back(y);
			mn = min(mn, rk[y]);
		}
		chk[mn - 1].push_back(vector<int>());
		for(int y : c) if(rk[y] > mn) chk[mn - 1].back().push_back(y);
	}
	bool ok(true);
	for(int i(0); i < n && ok; i++) {
		int v(ord[i]);
		++stmp;
		for(int y : adj[v]) tim[y] = stmp;
		for(int j(0); j < (int)chk[i].size() && ok; j++)
			for(int k(0); k < (int)chk[i][j].size() && ok; k++)
				if(tim[chk[i][j][k]] != stmp)
					ok = false;
	}
	assert(ok); // ok 代表是弦图 最小染色数只要从后往前贪心
}
