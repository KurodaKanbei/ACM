// 求圆与直线的交点
bool isCL(Circle a, Line l, P &p1, P &p2) { 
	D x = (l.s - a.o) % l.d,
		y = l.d.sqrlen(),
		d = x * x - y * ((l.s - a.o).sqrlen() - a.r * a.r);
	if (sign(d) < 0) return false;
	P p = l.s - x / y * l.d, delta = sqrt(max((D)0., d)) / y * l.d;
	p1 = p + delta, p2 = p - delta;
	return true;
}
// 求圆与圆的交面积
D areaCC(const Circle &c1, const Circle &c2) {
	D d = (c1.o - c2.o).len();
	if (sign(d - (c1.r + c2.r)) >= 0) {
		return 0;
	}
	if (sign(d - abs(c1.r - c2.r)) <= 0) {
		D r = min(c1.r, c2.r);
		return r * r * pi;
	}
	D x = (d * d + c1.r * c1.r - c2.r * c2.r) / (2 * d),
		   t1 = acos(min(1., max(-1., x / c1.r))), t2 = acos(min(1., max(-1., (d - x) / c2.r)));
	return c1.r * c1.r * t1 + c2.r * c2.r * t2 - d * c1.r * sin(t1);
}
// 求圆与圆的交点，注意调用前要先判定重圆
bool isCC(Circle a, Circle b, P &p1, P &p2) { 
	D s1 = (a.o - b.o).len();
	if (sign(s1 - a.r - b.r) > 0 || sign(s1 - abs(a.r - b.r)) < 0) return false;
	D s2 = (a.r * a.r - b.r * b.r) / s1;
	D aa = (s1 + s2) * 0.5, bb = (s1 - s2) * 0.5;
	P o = aa / (aa + bb) * (b.o - a.o) + a.o;
	P delta = sqrt(max(0., a.r * a.r - aa * aa)) * (b.o - a.o).zoom(1).rev();
	p1 = o + delta, p2 = o - delta;
	return true;
}
// 求点到圆的切点，按关于点的顺时针方向返回两个点, rev 必须是 (-y, x)
bool tanCP(const Circle &c, const P &p0, P &p1, P &p2) {
	D x = (p0 - c.o).sqrlen(), d = x - c.r * c.r;
	if (d < eps) return false; // 点在圆上认为没有切点
	P p = c.r * c.r / x * (p0 - c.o);
	P delta = (-c.r * sqrt(d) / x * (p0 - c.o)).rev();
	p1 = c.o + p + delta;
	p2 = c.o + p - delta;
	return true;
}
// 求圆到圆的外共切线，按关于 c1.o 的顺时针方向返回两条线, rev 必须是 (-y, x)
vector<Line> extanCC(const Circle &c1, const Circle &c2) {
	vector<Line> ret;
	if (sign(c1.r - c2.r) == 0) {
		P dir = c2.o - c1.o;
		dir = (c1.r / dir.len() * dir).rev();
		ret.push_back(Line(c1.o + dir, c2.o - c1.o));
		ret.push_back(Line(c1.o - dir, c2.o - c1.o));
	} else {
		P p = 1. / (c1.r - c2.r) * (-c2.r * c1.o + c1.r * c2.o);
		P p1, p2, q1, q2;
		if (tanCP(c1, p, p1, p2) && tanCP(c2, p, q1, q2)) {
			if (c1.r < c2.r) swap(p1, p2), swap(q1, q2);
			ret.push_back(Line(p1, q1 - p1));
			ret.push_back(Line(p2, q2 - p2));
		}
	}
	return ret;
}
// 求圆到圆的内共切线，按关于 c1.o 的顺时针方向返回两条线, rev 必须是 (-y, x)
vector<Line> intanCC(const Circle &c1, const Circle &c2) {
	vector<Line> ret;
	P p = 1. / (c1.r + c2.r) * (c2.r * c1.o + c1.r * c2.o);
	P p1, p2, q1, q2;
	if (tanCP(c1, p, p1, p2) && tanCP(c2, p, q1, q2)) { // 两圆相切认为没有切线
		ret.push_back(Line(p1, q1 - p1));
		ret.push_back(Line(p2, q2 - p2));
	}
	return ret;
}
bool contain(vector<P> poly, P p) { // 判断点 p 是否被多边形包含，包括落在边界上
	int ret = 0, n = poly.size();
	for(int i = 0; i < n; ++ i) {
		P u = poly[i], v = poly[(i + 1) % n];
		if (onSeg(p, u, v)) return true; // 在边界上
		if (sign(u.y - v.y) <= 0) swap(u, v);
		if (sign(p.y - u.y) > 0 || sign(p.y - v.y) <= 0) continue;
		ret += sign((v - p) * (u - p)) > 0;
	}
	return ret & 1;
}
vector<P> convexCut(const vector<P>&ps, Line l) { // 用半平面 (s,d) 的逆时针方向去切凸多边形
	vector<P> qs; 
	int n = ps.size();
	for (int i = 0; i < n; ++i) {
		Point p1 = ps[i], p2 = ps[(i + 1) % n];
		int d1 = sign(l.d * (p1 - l.s)), d2 = sign(l.d * (p2 - l.s));
		if (d1 >= 0) qs.push_back(p1);
		if (d1 * d2 < 0) qs.push_back(isLL(Line(p1, p2 - p1), l));
	}
	return qs;
}
