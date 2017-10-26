#include<cstdio>
#include<cstring>
#include<vector>
#include<cmath>
#include<iostream>
#include<algorithm>

using namespace std;

#define foreach(e, x) for(__typeof(x.begin()) e = x.begin(); e != x.end(); ++ e)

typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int, int> PII;

const int N = 200 + 10;

struct Point
{
	double x, y;
	Point() {}
	Point(double _x, double _y) {
		x = _x; y = _y;
	}
	Point operator - (const Point &that) const {
		return Point(x - that.x, y - that.y);
	}
	double det(const Point &that) const {
		return x * that.y - y * that.x;
	}
	double alpha() {
		return atan2(y, x);
	}
	void read() {
		scanf("%lf%lf", &x, &y);
	}
};

int n, m;
int vis[N][N];
int prev[N][N];
int in[N];
Point point[N], o;
vector<int> adj[N];
vector<int> sqn;

int cmp(const int &u, const int &v)
{
	Point pu = point[u] - o, pv = point[v] - o;
	return pu.alpha() < pv.alpha();
}

double calcArea(vector<int> &ps)
{
	double area = 0;
	for(int i = 0; i < (int)ps.size(); ++ i) {
		int j = i == (int)ps.size() - 1 ? 0 : i + 1;
		area += point[ps[i]].det(point[ps[j]]);
	}
	return area;
}

void dfs(int u, int v)
{
	if (vis[u][v]) return;
	vis[u][v] = true;
	sqn.push_back(u);
	int w = prev[u][v];
	dfs(v, w);
}

void solve()
{
	cin >> n;
	for(int i = 0; i < n; ++ i) {
		adj[i].clear();
	}
	int u, v;
	for(int i = 0; i < n; ++ i) {
		cin >> u; -- u;
		point[u].read();
		int tot; cin >> tot;
		for(int j = 0; j < tot; ++ j) {
			scanf("%d", &v); -- v;
			adj[u].push_back(v);
		}
	}
	cin >> m;

	for(int i = 0; i < n; ++ i) {
		o = point[i];
		sort(adj[i].begin(), adj[i].end(), cmp);
	}

	for(int i = 0; i < n; ++ i) {
		for(int j = 0; j < (int)adj[i].size(); ++ j) {
			vis[i][adj[i][j]] = false;
			int tmp = j == 0 ? adj[i].size() - 1 : j - 1;
			prev[adj[i][j]][i] = adj[i][tmp];
		}
	}

	int ret = 0;
	for(int i = 0; i < n; ++ i) {
		for(int j = 0; j < (int)adj[i].size(); ++ j) {
			int v = adj[i][j];
			if (vis[i][v]) continue;
			sqn.clear();
			dfs(i, v);
			int flag = true;
			if (calcArea(sqn) > 0) {
				memset(in, 0, sizeof in);
				for(int k = 0; k < (int)sqn.size(); ++ k) {
					v = sqn[k];
					if (in[v]) {
						flag = false;
						break;
					}
					in[v] = true;
				}
				if ((int)sqn.size() == m) 
					ret += flag;
			} 
		}
	}
	cout << ret << endl;
}

int main()
{
	int T; cin >> T;
	for(int i = 1; i <= T; ++ i) {
		solve();
	}
	return 0;
}

