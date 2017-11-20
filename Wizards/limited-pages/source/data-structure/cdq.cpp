struct Node {
	int x, y, z, idx;
	friend bool operator == (const Node &a,const Node &b) { return a.x == b.x && a.y == b.y && a.z == b.z; }
	friend bool operator < (const Node &a,const Node &b) { return a.y < b.y; }
} triple[maxn];
bool cmpx(const Node &a,const Node &b) {
	if(a.x != b.x) return a.x < b.x;
	if(a.y != b.y) return a.y < b.y;
	return a.z < b.z;
}
void solve(int l,int r) {
	if(l == r) return;
	int mid = (l + r) >> 1;
	solve(l, mid);
	static std::pair<Node,int> Lt[maxn], Rt[maxn];
	int Ls = 0, Rs = 0, pos = 1;
	for(int i = l; i <= mid; i++) Lt[++Ls] = std::make_pair(triple[i], i);
	for(int i = mid + 1; i <= r; i++) Rt[++Rs] = std::make_pair(triple[i], i);
	std::sort(Lt + 1, Lt + Ls + 1);
	std::sort(Rt + 1, Rt + Rs + 1);
	backup.clear();
	for(int i = 1; i <= Rs; i++) {
		while(pos <= Ls && !(Rt[i].first < Lt[pos].first)) {
			insert(Lt[pos].first.z, 1);
			pos++;
		}
		f[Rt[i].second] += query(Rt[i].first.z);
	}
	for(int i = 0; i < backup.size(); i++) pre[backup[i]] = 0;
	solve(mid + 1, r);
}
