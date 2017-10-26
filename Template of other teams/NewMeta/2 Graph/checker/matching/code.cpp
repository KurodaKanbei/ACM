#include <bits/stdc++.h>

using namespace std;

const int N = 222 + 7;
// 0 base, O(V^3)
vector<int> adj[N], q;
int n, mat[N], pred[N], base[N], type[N];
int lca(int u, int v){
	static int visit[N], tick = 0; ++tick;
	for (int i = 0; i < 2; i++, swap(u, v)) {
		for (u = base[u]; ~mat[u]; u = base[pred[mat[u]]]) {
			if (visit[u] == tick) return u;
			visit[u] = tick;
	}} return u;
}
void contract(int u, int v, int o) {
	for (; base[u] != o; v = mat[u], u = pred[v]) {
		pred[u] = v;
		base[u] = base[mat[u]] = o;
		if (type[mat[u]] == 1) {
			type[mat[u]] = 2;
			q.push_back(mat[u]);
	}}
}
bool augment(int start) { // O(V^2)
	for(int i = 0; i < n; ++i)
		pred[i] = -1, base[i] = i, type[i] = 0;
	q.clear();
	type[start] = 2; q.push_back(start);
	for (int head = 0; head < q.size(); head++) {
		int u = q[head];
		for (auto v : adj[u]) {
			if (type[v] == 0) {
				if (mat[v] == -1) {
					for (int tmp; v >= 0; v = tmp, u = pred[v])
						tmp = mat[u], mat[v] = u, mat[u] = v;
					return true;
				}
				pred[v] = u;
				q.push_back(mat[v]);
				type[v] = 1, type[mat[v]] = 2;
			} else if (type[v] == 2 && base[u] != base[v]) {
				int o = lca(u, v);
				contract(u, v, o), contract(v, u, o);
	}}}
	return false;
}
void blossom(){
	int num = 0; fill(mat, mat + n, -1);
	for(int i = 0; i < n; ++i) if (mat[i] == -1)  num += augment(i);
}

int main() {
	scanf("%d", &n);
	int u, v;
	while (scanf("%d %d", &u, &v) == 2) {
		u--, v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	blossom();
	int ans = 0;
	for (int i = 0; i < n; i++) {
		ans += mat[i] != -1;
	}
	printf("%d\n", ans);
	for (int i = 0; i < n; i++) {
		if (mat[i] > i) {
			printf("%d %d\n", i + 1, mat[i] + 1);
		}
	}
	return 0;
}
