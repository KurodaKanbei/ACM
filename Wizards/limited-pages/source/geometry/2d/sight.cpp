#include <bits/stdc++.h>

using namespace std;

const int N = 510;
const double eps = 1e-3;

struct Point {
	double x, y;
	Point() {}
	Point(double x, double y): x(x), y(y) {}
	void read() {
		scanf("%lf %lf", &x, &y);
	}
	void print() const {
		printf("%.10f %.10f\n", x, y);
	}
};

Point p[N];
Point A, B;
int n, dfn;
int g[N][N], vis[N][N], f[N][N], v[N][N];

Point operator + (const Point & a, const Point & b) {
	return Point(a.x + b.x, a.y + b.y);
}

Point operator - (const Point & a, const Point & b) {
	return Point(a.x - b.x, a.y - b.y);
}

Point operator * (const Point & a, double p) {
	return Point(a.x * p, a.y * p);
}

Point operator / (const Point & a, double p) {
	return Point(a.x / p, a.y / p);
}

double Cross(const Point & a, const Point & b) {
	return a.x * b.y - a.y * b.x;
}

double Dot(const Point & a, const Point & b) {
	return a.x * b.x + a.y * b.y;
}

int dcmp(double x) {
	if (fabs(x) < eps) return 0;
	return x < 0 ? -1 : 1;
}

Point Get(const Point & P, const Point & v, const Point & Q, const Point & w) {
	Point u = P - Q;
	double t = Cross(w, u) / Cross(v, w);
	return P + v * t;
}

int OnLine(const Point & a, const Point & b, const Point & c) {
	return dcmp(Cross(b - a, b - c)) == 0 && dcmp(Dot(b - a, b - c)) < 0;
}

int C(const Point & P, const Point & A, const Point & Q, const Point & B) {
	Point C = Get(P, A - P, Q, Q - B);
	return OnLine(Q, C, B);
}

int Onleft(const Point & a, const Point &b, const Point & c) {
	return dcmp(Cross(b - c, a - c)) > 0;
}

int visible(int x, int y) {
	int P = (x + n - 1) % n, Q = (x + 1) % n;
	Point u = p[y] - p[x], v = p[x] - p[P], w = p[x] - p[Q];
	if (Onleft(p[Q], p[x], p[P])) {
		return dcmp(Cross(v, u)) > 0 && dcmp(Cross(w, u)) < 0;
	} else {
		return !(dcmp(Cross(v, u)) < 0 && dcmp(Cross(w, u)) > 0);
	}
}

int solve(int x, int y) {
	if (vis[x][y] == dfn) return g[x][y];
	vis[x][y] = dfn;
	if (x == y || y == x + 1) return g[x][y] = 1;
	for (int i = x; i + 1 <= y; i++) {
		if (C(p[x], p[y], p[i], p[i + 1])) return g[x][y] = 0;
	}
	for (int i = x + 1; i < y; i++) {
		if (OnLine(p[x], p[i], p[y])) {
			return g[x][y] = solve(x, i) && solve(i, y);
		}
	}
	if (!visible(x, y) || !visible(y, x)) return g[x][y] = 0;
	return g[x][y] = 1;
}

void DP(int x, int y) {
	if (v[x][y] == dfn || x > y) return;
	v[x][y] = dfn;
	if (x == y) {
		f[x][y] = 1;
		return;
	}
	DP(x + 1, y);
	DP(x, y - 1);
	f[x][y] = max(f[x][y - 1], f[x + 1][y]);
	if (g[x][y] == 0) {
		int z = x;
		while(!g[z][y] && z < y) ++z;
		DP(x, z - 1);
		DP(z + 1, y);
		f[x][y] = max(f[x][y], f[x][z - 1] + f[z + 1][y]);
	}
}

vector<int> ans;

void DFS(int x, int y) {
	if (x > y) return;
	if (x == y) {
		ans.push_back(x);
		return;
	}
	if (f[x][y] == f[x][y - 1]) {
		DFS(x, y - 1);
	} else if (f[x][y] == f[x + 1][y]) {
		DFS(x + 1, y);
	} else {
		int z = x;
		while (!g[z][y] && z < y) ++z;
		DFS(x, z - 1);
		DFS(z + 1, y);
	}
}

int main() {
	freopen("hide.in", "r", stdin);
	freopen("hide.out", "w", stdout);
	while (scanf("%d", &n) && n) {
		++dfn;
		for (int i = 0; i < n; i++) {
			p[i].read();
		}
		for (int i = 1; i < n; i++) {
			for (int j = i; j < n; j++) {
				g[i][j] = solve(i, j);
			}
		}
		DP(1, n - 1);
		cout << f[1][n - 1] << endl;
		ans.clear();
		DFS(1, n - 1);
		for (int i = 0; i < ans.size(); i++) {
			printf("%d%c", ans[i] + 1, i + 1 < ans.size() ? ' ' : '\n');
		}
	}
	return 0;
}
