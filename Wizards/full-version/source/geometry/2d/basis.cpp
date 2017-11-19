int sign(DB x) {
	return (x > eps) - (x < -eps);
}
DB msqrt(DB x) {
	return sign(x) > 0 ? sqrt(x) : 0;
}

struct Point {
	DB x, y;
	Point rotate(DB ang) const {  // 逆时针旋转 ang 弧度
		return Point(cos(ang) * x - sin(ang) * y,
				cos(ang) * y + sin(ang) * x);
	}
	Point turn90() const {  // 逆时针旋转 90 度
		return Point(-y, x);
	}
	Point unit() const {
		return *this / len();
	}
};
DB dot(const Point& a, const Point& b) {
	return a.x * b.x + a.y * b.y;
}
DB det(const Point& a, const Point& b) {
	return a.x * b.y - a.y * b.x;
}
#define cross(p1,p2,p3) ((p2.x-p1.x)*(p3.y-p1.y)-(p3.x-p1.x)*(p2.y-p1.y))
#define crossOp(p1,p2,p3) sign(cross(p1,p2,p3))
bool isLL(const Line& l1, const Line& l2, Point& p) {  // 直线与直线交点
	DB s1 = det(l2.b - l2.a, l1.a - l2.a),
	   s2 = -det(l2.b - l2.a, l1.b - l2.a);
	if (!sign(s1 + s2)) return false;
	p = (l1.a * s2 + l1.b * s1) / (s1 + s2);
	return true;
}
bool onSeg(const Line& l, const Point& p) {  // 点在线段上
	return sign(det(p - l.a, l.b - l.a)) == 0 && sign(dot(p - l.a, p - l.b)) <= 0;
}
Point projection(const Line & l, const Point& p) {
	return l.a + (l.b - l.a) * (dot(p - l.a, l.b - l.a) / (l.b - l.a).len2());
}
DB disToLine(const Line& l, const Point& p) {  // 点到*直线*距离
	return fabs(det(p - l.a, l.b - l.a) / (l.b - l.a).len());
}
DB disToSeg(const Line& l, const Point& p) {  // 点到线段距离
	return sign(dot(p - l.a, l.b - l.a)) * sign(dot(p - l.b, l.a - l.b)) == 1 ? disToLine(l, p) : std::min((p - l.a).len(), (p - l.b).len());
}
// 圆与直线交点
bool isCL(Circle a, Line l, Point& p1, Point& p2) {
	DB x = dot(l.a - a.o, l.b - l.a),
	   y = (l.b - l.a).len2(),
	   d = x * x - y * ((l.a - a.o).len2() - a.r * a.r);
	if (sign(d) < 0) return false;
	Point p = l.a - ((l.b - l.a) * (x / y)), delta = (l.b - l.a) * (msqrt(d) / y);
	p1 = p + delta; p2 = p - delta;
	return true;
}
//圆与圆的交面积
DB areaCC(const Circle& c1, const Circle& c2) {
	DB d = (c1.o - c2.o).len();
	if (sign(d - (c1.r + c2.r)) >= 0) return 0;
	if (sign(d - std::abs(c1.r - c2.r)) <= 0) {
		DB r = std::min(c1.r, c2.r);
		return r * r * PI;
	}
	DB x = (d * d + c1.r * c1.r - c2.r * c2.r) / (2 * d),
		t1 = acos(x / c1.r), t2 = acos((d - x) / c2.r);
	return c1.r * c1.r * t1 + c2.r * c2.r * t2 - d * c1.r * sin(t1);
}
// 圆与圆交点
bool isCC(Circle a, Circle b, P& p1, P& p2) {
	DB s1 = (a.o - b.o).len();
	if (sign(s1 - a.r - b.r) > 0 || sign(s1 - std::abs(a.r - b.r)) < 0) return false;
	DB s2 = (a.r * a.r - b.r * b.r) / s1;
	DB aa = (s1 + s2) * 0.5, bb = (s1 - s2) * 0.5;
	P o = (b.o - a.o) * (aa / (aa + bb)) + a.o;
	P delta = (b.o - a.o).unit().turn90() * msqrt(a.r * a.r - aa * aa);
	p1 = o + delta, p2 = o - delta;
	return true;
}
// 求点到圆的切点，按关于点的顺时针方向返回两个点
bool tanCP(const Circle &c, const Point &p0, Point &p1, Point &p2) {
	double x = (p0 - c.o).len2(), d = x - c.r * c.r;
	if (d < eps) return false; // 点在圆上认为没有切点
	Point p = (p0 - c.o) * (c.r * c.r / x);
	Point delta = ((p0 - c.o) * (-c.r * sqrt(d) / x)).turn90();
	p1 = c.o + p + delta;
	p2 = c.o + p - delta;
	return true;
}
// 求圆到圆的外共切线，按关于 c1.o 的顺时针方向返回两条线
vector<Line> extanCC(const Circle &c1, const Circle &c2) {
	vector<Line> ret;
	if (sign(c1.r - c2.r) == 0) {
		Point dir = c2.o - c1.o;
		dir = (dir * (c1.r / dir.len())).turn90();
		ret.push_back(Line(c1.o + dir, c2.o + dir));
		ret.push_back(Line(c1.o - dir, c2.o - dir));
	} else {
		Point p = (c1.o * -c2.r + c2.o * c1.r) / (c1.r - c2.r);
		Point p1, p2, q1, q2;
		if (tanCP(c1, p, p1, p2) && tanCP(c2, p, q1, q2)) {
			if (c1.r < c2.r) swap(p1, p2), swap(q1, q2);
			ret.push_back(Line(p1, q1));
			ret.push_back(Line(p2, q2));
		}
	}
	return ret;
}
// 求圆到圆的内共切线，按关于 c1.o 的顺时针方向返回两条线
std::vector<Line> intanCC(const Circle &c1, const Circle &c2) {
	std::vector<Line> ret;
	Point p = (c1.o * c2.r + c2.o * c1.r) / (c1.r + c2.r);
	Point p1, p2, q1, q2;
	if (tanCP(c1, p, p1, p2) && tanCP(c2, p, q1, q2)) { // 两圆相切认为没有切线
		ret.push_back(Line(p1, q1));
		ret.push_back(Line(p2, q2));
	}
	return ret;
}
bool contain(vector<Point> polygon, Point p) { // 判断点 p 是否被多边形包含，包括落在边界上
	int ret = 0, n = polygon.size();
	for(int i = 0; i < n; ++ i) {
		Point u = polygon[i], v = polygon[(i + 1) % n];
		if (onSeg(Line(u, v), p)) return true;  // Here I guess.
		if (sign(u.y - v.y) <= 0) swap(u, v);
		if (sign(p.y - u.y) > 0 || sign(p.y - v.y) <= 0) continue;
		ret += sign(det(p, v, u)) > 0;
	}
	return ret & 1;
}
// 用半平面 (q1,q2) 的逆时针方向去切凸多边形
std::vector<Point> convexCut(const std::vector<Point>&ps, Point q1, Point q2) {
	std::vector<Point> qs; int n = ps.size();
	for (int i = 0; i < n; ++i) {
		Point p1 = ps[i], p2 = ps[(i + 1) % n];
		int d1 = crossOp(q1,q2,p1), d2 = crossOp(q1,q2,p2);
		if (d1 >= 0) qs.push_back(p1);
		if (d1 * d2 < 0) qs.push_back(isSS(p1, p2, q1, q2));
	}
	return qs;
}
// 求凸包
std::vector<Point> convexHull(std::vector<Point> ps) {
	int n = ps.size(); if (n <= 1) return ps;
	std::sort(ps.begin(), ps.end());
	std::vector<Point> qs;
	for (int i = 0; i < n; qs.push_back(ps[i ++]))
		while (qs.size() > 1 && sign(det(qs[qs.size() - 2], qs.back(), ps[i])) <= 0)
			qs.pop_back();
	for (int i = n - 2, t = qs.size(); i >= 0; qs.push_back(ps[i --]))
		while ((int)qs.size() > t && sign(det(qs[qs.size() - 2], qs.back(), ps[i])) <= 0)
			qs.pop_back();
	return qs;
