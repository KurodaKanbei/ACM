/* 
 * Time: O(V ^ 3)
 * Condition: The perfect matching exists.
 * When finding minimum weight matching, change the weight to minus.
 */

bool e[MAXN][MAXN]; // whether the edge exists
// The array e[][] can be replaced by setting the absent edge's weight to -INF.
int val[MAXN][MAXN]; // the weight of the edge

int ex_A[MAXN], ex_B[MAXN];
bool vis_A[MAXN], vis_B[MAXN];
int match[MAXN];
int slack[MAXN];

bool DFS(int now) {
	vis_A[now] = 1;
	for (int i = 1; i <= n; ++i) {
		if (vis_B[i] || !e[now][i]) continue;
		
		int gap = ex_A[now] + ex_B[i] - val[now][i];
		
		if (gap == 0) {
			vis_B[i] = 1;
			if (!match[i] || DFS(match[i])) {
				match[i] = now;
				return 1;
			}
		}
		else slack[i] = std::min(slack[i], gap);
	}
	
	return 0;
}

int KM() {
	memset(match, 0, sizeof match);
	memset(ex_B, 0, sizeof ex_B);
	
	for (int i = 1; i <= n; ++i) {
		ex_A[i] = -INF;
		for (int j = 1; j <= n; ++j) if (e[i][j])
			ex_A[i] = std::max(ex_A[i], val[i][j]);
	}
	
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) slack[j] = INF;
		while (1) {
			memset(vis_A, 0, sizeof vis_A);
			memset(vis_B, 0, sizeof vis_B);
			
			if (DFS(i)) break;
			
			int tmp = INF;
			for (int j = 1; j <= n; ++j) if (!vis_B[j])
				tmp = std::min(tmp, slack[j]);
			for (int j = 1; j <= n; ++j) {
				if (vis_A[j]) ex_A[j] -= tmp;
				if (vis_B[j]) ex_B[j] += tmp;
			}
		}
	}
	
	int res = 0;
	for (int i = 1; i <= n; ++i)
		res += val[match[i]][i];
	return res;
}
