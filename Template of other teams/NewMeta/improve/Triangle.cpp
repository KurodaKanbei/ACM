P fermat(const P& a, const P& b, const P& c) {
	D ab((b - a).len()), bc((b - c).len()), ca((c - a).len());
	D cosa((b - a) % (c - a) / ab / ca);
	D cosb((a - b) % (c - b) / ab / bc);
	D cosc((b - c) % (a - c) / ca / bc);
	P mid; D sq3(sqrt(3) / 2);
	if(sign((b - a) * (c - a)) < 0) swap(b, c);
	if(sign(cosa + 0.5) < 0) mid = a;
	else if(sign(cosb + 0.5) < 0) mid = b;
	else if(sign(cosc + 0.5) < 0) mid = c;
	else mid = intersection(Line(a, c + (b - c).rot(sq3) - a), Line(c, b + (a - b).rot(sq3) - c));
	return mid;
	// mid 为三角形 abc 费马点, 要求 abc 非退化
	length = (mid - a).len() + (mid - b).len() + (mid - c).len();
	// 以下求法仅在三角形三个角均小于120度时, 可以求出ans为费马点到abc三点距离和
	length = (a - c - (b - c).rot(sq3)).len();
}
Point inCenter(const Point &A, const Point &B, const Point &C) { // 内心
	double a = (B - C).len(), b = (C - A).len(), c = (A - B).len(),
		s = fabs(det(B - A, C - A)),
		r = s / p;
	return (A * a + B * b + C * c) / (a + b + c);
}
Point circumCenter(const Point &a, const Point &b, const Point &c) { // 外心
	Point bb = b - a, cc = c - a;
	double db = bb.len2(), dc = cc.len2(), d = 2 * det(bb, cc);
	return a - Point(bb.y * dc - cc.y * db, cc.x * db - bb.x * dc) / d;
}
Point othroCenter(const Point &a, const Point &b, const Point &c) { // 垂心
	Point ba = b - a, ca = c - a, bc = b - c;
	double Y = ba.y * ca.y * bc.y,
		   A = ca.x * ba.y - ba.x * ca.y,
		   x0 = (Y + ca.x * ba.y * b.x - ba.x * ca.y * c.x) / A,
		   y0 = -ba.x * (x0 - c.x) / ba.y + ca.y;
	return Point(x0, y0);
}
