struct Event {
	P p; D ang; int delta;
	Event (P p = Point(0, 0), D ang = 0, int delta = 0) : p(p), ang(ang), delta(delta) {}
};
bool operator < (const Event &a, const Event &b) { return a.ang < b.ang; }
void addEvent(const Circle &a, const Circle &b, vector<Event> &evt, int &cnt) {
	D d2 = (a.o - b.o).sqrlen(), dRatio = ((a.r - b.r) * (a.r + b.r) / d2 + 1) / 2,
	  pRatio = sqrt(max((D)0., -(d2 - sqr(a.r - b.r)) * (d2 - sqr(a.r + b.r)) / (d2 * d2 * 4)));
	P d = b.o - a.o, p = d.rot(pi / 2),
	  q0 = a.o + d * dRatio + p * pRatio,
	  q1 = a.o + d * dRatio - p * pRatio;
	D ang0 = (q0 - a.o).ang(), ang1 = (q1 - a.o).ang();
	evt.emplace_back(q1, ang1, 1); evt.emplace_back(q0, ang0, -1);
	cnt += ang1 > ang0;
}
bool issame(const Circle &a, const Circle &b) { return sign((a.o - b.o).len()) == 0 && sign(a.r - b.r) == 0; }
bool overlap(const Circle &a, const Circle &b) { return sign(a.r - b.r - (a.o - b.o).len()) >= 0; }
bool intersect(const Circle &a, const Circle &b) { return sign((a.o - b.o).len() - a.r - b.r) < 0; }
int C;
Circle c[N];
double area[N];
void solve() { // 返回覆盖至少 k 次的面积
	memset(area, 0, sizeof(D) * (C + 1));
	for (int i = 0; i < C; ++i) {
		int cnt = 1;
		vector<Event> evt;
		for (int j = 0; j < i; ++j) if (issame(c[i], c[j])) ++cnt;
		for (int j = 0; j < C; ++j)
			if (j != i && !issame(c[i], c[j]) && overlap(c[j], c[i]))
				++cnt;
		for (int j = 0; j < C; ++j)
			if (j != i && !overlap(c[j], c[i]) && !overlap(c[i], c[j]) && intersect(c[i], c[j]))
				addEvent(c[i], c[j], evt, cnt);
		if (evt.empty()) area[cnt] += PI * c[i].r * c[i].r;
		else {
			sort(evt.begin(), evt.end());
			evt.push_back(evt.front());
			for (int j = 0; j + 1 < (int)evt.size(); ++j) {
				cnt += evt[j].delta;
				area[cnt] += det(evt[j].p, evt[j + 1].p) / 2;
				D ang = evt[j + 1].ang - evt[j].ang;
				if (ang < 0) ang += PI * 2;
				area[cnt] += ang * c[i].r * c[i].r / 2 - sin(ang) * c[i].r * c[i].r / 2;
}	}	}	}
