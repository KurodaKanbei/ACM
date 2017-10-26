// 注意，无法处理小于四点的退化情况
struct Point;
Point a[33];
Point intersect(const Plane & a, const Plane & b, const Plane & c) {
	Point c1(a.nor.x, b.nor.x, c.nor.x), c2(a.nor.y, b.nor.y, c.nor.y), c3(a.nor.z, b.nor.z, c.nor.z), c4(a.m, b.m, c.m);
	return 1 / ((c1 * c2) % c3) * Point((c4 * c2) % c3, (c1 * c4) % c3, (c1 * c2) % c4);
}
bool in(const Point & a, const Circle & b) {
	return sign((a - b.o).len() - b.r) <= 0;
}
vector<Point> vec;
Circle calc() {
	if (vec.empty()) {
		return Circle(Point(0, 0, 0), 0);
	} else if(1 == (int)vec.size()) {
		return Circle(vec[0], 0);
	} else if(2 == (int)vec.size()) {
		return Circle(0.5 * (vec[0] + vec[1]), 0.5 * (vec[0] - vec[1]).len());
	} else if(3 == (int)vec.size()) {
		double r((vec[0] - vec[1]).len() * (vec[1] - vec[2]).len() * (vec[2] - vec[0]).len() / 2 /
				fabs(((vec[0] - vec[2]) * (vec[1] - vec[2])).len()));
		return Circle(intersect(Plane(vec[1] - vec[0], 0.5 * (vec[1] + vec[0])),
				    Plane(vec[2] - vec[1], 0.5 * (vec[2] + vec[1])),
					Plane((vec[1] - vec[0]) * (vec[2] - vec[0]), vec[0])), r);
	} else {
		Point o(intersect(Plane(vec[1] - vec[0], 0.5 * (vec[1] + vec[0])),
					Plane(vec[2] - vec[0], 0.5 * (vec[2] + vec[0])),
					Plane(vec[3] - vec[0], 0.5 * (vec[3] + vec[0]))));
		return Circle(o, (o - vec[0]).len());
	}
}
Circle miniBall(int n) {
	Circle res(calc());
	for(int i(0); i < n; i++) {
		if(!in(a[i], res)) {
			vec.push_back(a[i]);
			res = miniBall(i);
			vec.pop_back();
			if (i) { Point tmp(a[i]); memmove(a + 1, a, sizeof(Point) * i); a[0] = tmp; }
		}
	}
	return res;
}
int main() {
	for(;;) {
		int n; scanf("%d", &n);
		if (!n) break;
		for(int i(0); i < n; i++) {
			a[i].scan();
		}
		sort(a, a + n);
		n = unique(a, a + n) - a;
		vec.clear();
		printf("%.10f\n", miniBall(n).r);
	}
}
