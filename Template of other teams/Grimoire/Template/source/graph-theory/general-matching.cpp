// 0-base, match[u] is linked to u
vector<int> lnk[MAXN];
int match[MAXN], Queue[MAXN], pred[MAXN], base[MAXN], head, tail, sta, fin, nbase;
bool inQ[MAXN], inB[MAXN];
inline void push(int u) {
	Queue[tail++] = u; inQ[u] = 1;
}
inline int pop() {
	return Queue[head++];
}
inline int FindCA(int u, int v) {
	static bool inP[MAXN];
	fill(inP, inP + n, false);
	while (1) {
		u = base[u]; inP[u] = 1; 
		if(u == sta) break;
		u = pred[match[u]];
	}
	while (1) {
		v = base[v];
		if (inP[v]) break;
		v = pred[match[v]];
	}
	return v;
}
inline void RT(int u) {
	int v;
	while (base[u] != nbase) {
		v = match[u];
		inB[base[u]] = inB[base[v]] = 1;
		u = pred[v];
		if (base[u] != nbase) pred[u] = v;
	}
}
inline void BC(int u, int v) {
	nbase = FindCA(u, v);
	fill(inB, inB + n, 0);
	RT(u); RT(v);
	if (base[u] != nbase) pred[u] = v;
	if (base[v] != nbase) pred[v] = u;
	for (int i = 0; i < n; ++i)
		if (inB[base[i]]) {
			base[i] = nbase;
			if (!inQ[i]) push(i);
		}
}
bool FindAP(int u) {
	bool found = false;
	for (int i = 0; i < n; ++i) {
		pred[i] = -1; base[i] = i; inQ[i] = 0;
	}
	sta = u; fin = -1; head = tail = 0; push(sta);
	while (head < tail) {
		int u = pop();
		for (int i = (int)lnk[u].size() - 1; i >= 0; --i) {
			int v = lnk[u][i];
			if (base[u] != base[v] && match[u] != v) {
				if (v == sta || match[v] >= 0 && pred[match[v]] >= 0) BC(u, v);
				else if (pred[v] == -1) {
					pred[v] = u;
					if (match[v] >= 0) push(match[v]);
					else {
						fin = v;
						return true;
					}
				}
			} 
		}
	}
	return found;
}
inline void AP() {
	int u = fin, v, w;
	while (u >= 0) {
		v = pred[u]; w = match[v];
		match[v] = u; match[u] = v;
		u = w;
	}
}
inline int FindMax() {
	for (int i = 0; i < n; ++i) match[i] = -1;
	for (int i = 0; i < n; ++i) 
		if (match[i] == -1 && FindAP(i)) AP();
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		ans += (match[i] != -1);
	}
	return ans;
}
