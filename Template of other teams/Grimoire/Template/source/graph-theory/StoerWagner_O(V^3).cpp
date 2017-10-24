/*
 * Stoer Wagner 全局最小割 O(V ^ 3)
 * 1base, 点数n, 邻接矩阵edge[MAXN][MAXN]
 * 返回值为全局最小割
 */

int StoerWagner() {
	static int v[MAXN], wage[MAXN];
	static bool vis[MAXN];
	
	for (int i = 1; i <= n; ++i) v[i] = i;
	
	int res = INF;
	
	for (int nn = n; nn > 1; --nn) {
		memset(vis, 0, sizeof(bool) * (nn + 1));
		memset(wage, 0, sizeof(int) * (nn + 1));
		
		int pre, last = 1; // vis[1] = 1;
		
		for (int i = 1; i < nn; ++i) {
			pre = last; last = 0;
			for (int j = 2; j <= nn; ++j) if (!vis[j]) {
				wage[j] += edge[v[pre]][v[j]];
				if (!last || wage[j] > wage[last]) last = j;
			}
			vis[last] = 1;
		}
		
		res = std::min(res, wage[last]);
		
		for (int i = 1; i <= nn; ++i) {
			edge[v[i]][v[pre]] += edge[v[last]][v[i]];
			edge[v[pre]][v[i]] += edge[v[last]][v[i]];
		}
		v[last] = v[nn];
	}
	return res;
}
