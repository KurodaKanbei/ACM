// O(n^3), 0 base, 最大权匹配
// 不存在的边权值开到 -n * (|MAXV| + 1), INF 为 3n * (|MAXV| + 1)
int n, cost[N][N]; bool vy[N];
int lx[N], ly[N], match[N], slack[N], pre[N];
void augment(int root) {
	fill(vy + 1, vy + n + 1, false);
	fill(slack + 1, slack + n + 1, INF);
	int py; match[py = 0] = root;
	do { vy[py] = true; int x = match[py], delta = INF, yy;
		for (int y = 1; y <= n; y++) if (!vy[y]) {
			if (lx[x] + ly[y] - cost[x][y] < slack[y]) {
				slack[y] = lx[x] + ly[y] - cost[x][y];
				pre[y] = py;
			}
			if (slack[y] < delta) {
				delta = slack[y];
				yy = y;
			}
		}
		for (int y = 0; y <= n; y++) {
			if (vy[y]) {
				lx[match[y]] -= delta;
				ly[y] += delta;
			} else slack[y] -= delta;
		} py = yy;
	} while (match[py] != -1);
	do { int prev = pre[py];
		match[py] = match[prev];
		py = prev;
	} while (py);
}
void KM() {
	for (int i = 1; i <= n; i++) {
		lx[i] = ly[i] = 0; match[i] = -1;
		for (int j = 1; j <= n; j++)
			lx[i] = max(lx[i], cost[i][j]);
	}
	for (int root = 1; root <= n; root++) augment(root);
	// $ answer = \sum_i{lx[i] + ly[i]}$
}
