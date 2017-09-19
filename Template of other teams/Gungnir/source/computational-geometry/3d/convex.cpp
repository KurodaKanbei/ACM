__inline P cross(const P& a, const P& b) {
	return P(
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x
        );
}

__inline DB mix(const P& a, const P& b, const P& c) {
	return dot(cross(a, b), c);
}

__inline DB volume(const P& a, const P& b, const P& c, const P& d) {
	return mix(b - a, c - a, d - a);
}

struct Face {
	int a, b, c;
	__inline Face() {}
	__inline Face(int _a, int _b, int _c):
		a(_a), b(_b), c(_c) {}
	__inline DB area() const {
		return 0.5 * cross(p[b] - p[a], p[c] - p[a]).len();
	}
	__inline P normal() const {
		return cross(p[b] - p[a], p[c] - p[a]).unit();
	}
	__inline DB dis(const P& p0) const {
		return dot(normal(), p0 - p[a]);
	}
};

std::vector<Face> face, tmp;  // Should be O(n).
int mark[N][N], Time, n;

__inline void add(int v) {
	++ Time;
	clear(tmp);
	for (int i = 0; i < (int)face.size(); ++ i) {
		int a = face[i].a, b = face[i].b, c = face[i].c;
		if (sign(volume(p[v], p[a], p[b], p[c])) > 0) {
			mark[a][b] = mark[b][a] = mark[a][c] =
				mark[c][a] = mark[b][c] = mark[c][b] = Time;
		}
		else {
			tmp.push_back(face[i]);
		}
	}
	clear(face); face = tmp;
	for (int i = 0; i < (int)tmp.size(); ++ i) {
		int a = face[i].a, b = face[i].b, c = face[i].c;
		if (mark[a][b] == Time) face.emplace_back(v, b, a);
		if (mark[b][c] == Time) face.emplace_back(v, c, b);
		if (mark[c][a] == Time) face.emplace_back(v, a, c);
		assert(face.size() < 500u);
	}
}

void reorder() {
	for (int i = 2; i < n; ++ i) {
		P tmp = cross(p[i] - p[0], p[i] - p[1]);
		if (sign(tmp.len())) {
			std::swap(p[i], p[2]);
			for (int j = 3; j < n; ++ j)
				if (sign(volume(p[0], p[1], p[2], p[j]))) {
					std::swap(p[j], p[3]);
					return;
				}
		}
	}
}

void build_convex() {
	reorder();
	clear(face);
	face.emplace_back(0, 1, 2);
	face.emplace_back(0, 2, 1);
	for (int i = 3; i < n; ++ i)
		add(i);
}
