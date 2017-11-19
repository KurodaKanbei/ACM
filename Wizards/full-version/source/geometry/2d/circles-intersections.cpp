struct Event {
	Point p;
	double ang;
	int delta;
	Event (Point p = Point(0, 0), double ang = 0, double delta = 0) : p(p), ang(ang), delta(delta) {}
};
bool operator < (const Event &a, const Event &b) {
	return a.ang < b.ang;
}
void addEvent(const Circle &a, const Circle &b, vector<Event> &evt, int &cnt) {
	double d2 = (a.o - b.o).len2(),
		   dRatio = ((a.r - b.r) * (a.r + b.r) / d2 + 1) / 2,
		   pRatio = sqrt(-(d2 - sqr(a.r - b.r)) * (d2 - sqr(a.r + b.r)) / (d2 * d2 * 4));
	Point d = b.o - a.o, p = d.rotate(PI / 2),
		  q0 = a.o + d * dRatio + p * pRatio,
		  q1 = a.o + d * dRatio - p * pRatio;
	double ang0 = (q0 - a.o).ang(),
		   ang1 = (q1 - a.o).ang();
	evt.push_back(Event(q1, ang1, 1));
	evt.push_back(Event(q0, ang0, -1));
	cnt += ang1 > ang0;
}
bool issame(const Circle &a, const Circle &b) { return sign((a.o - b.o).len()) == 0 && sign(a.r - b.r) == 0; }
bool overlap(const Circle &a, const Circle &b) { return sign(a.r - b.r - (a.o - b.o).len()) >= 0; }
bool intersect(const Circle &a, const Circle &b) { return sign((a.o - b.o).len() - a.r - b.r) < 0; }
Circle c[N];
double area[N];  // area[k] -> area of intersections >= k.
Point centroid[N];
bool keep[N];
void add(int cnt, DB a, Point c) {
	area[cnt] += a;
	centroid[cnt] = centroid[cnt] + c * a;
}
void solve(int C) {
	for (int i = 1; i <= C; ++ i) {
        area[i] = 0;
        centroid[i] = Point(0, 0);
    }
	for (int i = 0; i < C; ++i) {
		int cnt = 1;
		vector<Event> evt;
		for (int j = 0; j < i; ++j) if (issame(c[i], c[j])) ++cnt;
		for (int j = 0; j < C; ++j) {
			if (j != i && !issame(c[i], c[j]) && overlap(c[j], c[i])) {
				++cnt;
			}
		}
		for (int j = 0; j < C; ++j) {
			if (j != i && !overlap(c[j], c[i]) && !overlap(c[i], c[j]) && intersect(c[i], c[j])) {
				addEvent(c[i], c[j], evt, cnt);
			}
		}
		if (evt.size() == 0u) {
			add(cnt, PI * c[i].r * c[i].r, c[i].o);
		} else {
			sort(evt.begin(), evt.end());
			evt.push_back(evt.front());
			for (int j = 0; j + 1 < (int)evt.size(); ++j) {
				cnt += evt[j].delta;
				add(cnt, det(evt[j].p, evt[j + 1].p) / 2, (evt[j].p + evt[j + 1].p) / 3);
				double ang = evt[j + 1].ang - evt[j].ang;
				if (ang < 0) {
					ang += PI * 2;
				}
                if (sign(ang) == 0) continue;
                add(cnt, ang * c[i].r * c[i].r / 2, c[i].o +
                    Point(sin(ang1) - sin(ang0), -cos(ang1) + cos(ang0)) * (2 / (3 * ang) * c[i].r));
				add(cnt, -sin(ang) * c[i].r * c[i].r / 2, (c[i].o + evt[j].p + evt[j + 1].p) / 3);
			}
		}
	}
    for (int i = 1; i <= C; ++ i)
		if (sign(area[i])) {
			centroid[i] = centroid[i] / area[i];
		}
}
