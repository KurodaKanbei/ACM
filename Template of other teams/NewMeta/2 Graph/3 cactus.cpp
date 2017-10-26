int fa[N], ma[N], stmp[N], tim;
bool ins[N], vst[N];
vector<int> adj[N];// ma: 环上右侧的点, fa: 树上的父亲, 或环上左边的点
vector<vector<int> > cycles[N];
void dfs(int v) {
	ins[v] = true; vst[v] = true;
	for(int y : adj[v])
		if(!vst[y]) {
			fa[y] = v;
			dfs(y);
		}else if(ins[y] && y != fa[v]) {
			cycles[y].push_back(vector<int>(1, y));
			int x(v);
			ma[v] = y;
			while(x != y) {
				cycles[y].back().push_back(x);
				if(fa[x] != y)
					ma[fa[x]] = x;
				x = fa[x];
			}
		}
	tim++;
	for(auto & cyc : cycles[v]) for(int y : cyc) {
			stmp[y] = tim;
			if(y != v);// 此处是环上的点
	}
	for(int y : adj[v]) if(y != fa[v] && y != ma[v] && stmp[y] != tim);// 此处是树上的儿子
	ins[v] = false;
}
void sfd(int v) {
	for(auto & cyc : cycles[v]) for(int y : cyc);// 枚举环上的点
	for(auto & cyc : cycles[v]) for(int y : cyc) if(y != v) sfd(y);
	tim++;
	for(auto & cyc : cycles[v]) for(int y : cyc) if(y != v) stmp[y] = tim;
	int tt(tim);
	for(int y : adj[v]) if(y != fa[v] && y != ma[v] && stmp[y] != tt) sfd(y);
}
