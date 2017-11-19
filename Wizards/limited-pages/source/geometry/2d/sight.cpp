int C(const Point & P, const Point & A, const Point & Q, const Point & B) {
	Point C = GetIntersection(P, A - P, Q, Q - B);
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
