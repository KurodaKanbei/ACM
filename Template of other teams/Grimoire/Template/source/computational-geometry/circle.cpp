struct C{
	P o;
	double r;
	C(){}
	C(P _o,double _r):o(_o),r(_r){}
};
// 求圆与直线的交点
//turn90() P(-y,x)
double fix(double x){return x>=0?x:0;}
bool intersect(C a, L l, P &p1, P &p2) { 
	double x = ((l.a - a.o)^ (l.b - l.a)),
		y = (l.b - l.a).len2(),
		d = x * x - y * ((l.a - a.o).len2() - a.r * a.r);
	if (sgn(d) < 0) return false;
	d = max(d, 0.0);
	P p = l.a - ((l.b - l.a) * (x / y)), delta = (l.b - l.a) * (sqrt(d) / y);
	p1 = p + delta, p2 = p - delta;
	return true;
}
// 求圆与圆的交点，注意调用前要先判定重圆
bool intersect(C a, C b, P &p1, P &p2) { 
	double s1 = (a.o - b.o).len();
	if (sgn(s1 - a.r - b.r) > 0 || sgn(s1 - fabs(a.r - b.r)) < 0) return false;
	double s2 = (a.r * a.r - b.r * b.r) / s1;
	double aa = (s1 + s2) * 0.5, bb = (s1 - s2) * 0.5;
	P o = (b.o - a.o) * (aa / (aa + bb)) + a.o;
	P delta = (b.o - a.o).norm().turn90() * sqrt(fix(a.r * a.r - aa * aa));
	p1 = o + delta, p2 = o - delta;
	return true;
}
// 求点到圆的切点，按关于点的顺时针方向返回两个点
bool tang(const C &c, const P &p0, P &p1, P &p2) {
	double x = (p0 - c.o).len2(), d = x - c.r * c.r;
	if (d < eps) return false; // 点在圆上认为没有切点
	P p = (p0 - c.o) * (c.r * c.r / x);
	P delta = ((p0 - c.o) * (-c.r * sqrt(d) / x)).turn90();
	p1 = c.o + p + delta;
	p2 = c.o + p - delta;
	return true;
}
// 求圆到圆的外共切线，按关于 c1.o 的顺时针方向返回两条线
vector<L> extan(const C &c1, const C &c2) {
	vector<L> ret;
	if (sgn(c1.r - c2.r) == 0) {
		P dir = c2.o - c1.o;
		dir = (dir * (c1.r / dir.len())).turn90();
		ret.push_back(L(c1.o + dir, c2.o + dir));
		ret.push_back(L(c1.o - dir, c2.o - dir));
	} else {
		P p = (c1.o * -c2.r + c2.o * c1.r) / (c1.r - c2.r);
		P p1, p2, q1, q2;
		if (tang(c1, p, p1, p2) && tang(c2, p, q1, q2)) {
//			if (c1.r < c2.r) swap(p1, p2), swap(q1, q2);
			ret.push_back(L(p1, q1));
			ret.push_back(L(p2, q2));
		}
	}
	return ret;
}
// 求圆到圆的内共切线，按关于 c1.o 的顺时针方向返回两条线
vector<L> intan(const C &c1, const C &c2) {
	vector<L> ret;
	P p = (c1.o * c2.r + c2.o * c1.r) / (c1.r + c2.r);
	P p1, p2, q1, q2;
	if (tang(c1, p, p1, p2) && tang(c2, p, q1, q2)) { // 两圆相切认为没有切线
		ret.push_back(L(p1, q1));
		ret.push_back(L(p2, q2));
	}
	return ret;
}
