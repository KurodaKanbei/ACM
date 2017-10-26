typedef __int128 J; // 坐标 |1e9| 就要用 int128 来判断
struct Line {
	bool include(P a) const { return (a - s) * d >= 0; } // 严格去掉 =
	bool include(Line a, Line b) const {
		J l1(a.d * b.d);
		if(!l1)	return true;
		J x(l1 * (a.s.x - s.x)), y(l1 * (a.s.y - s.y));
		J l2((b.s - a.s) * b.d);
		x += l2 * a.d.x; y += l2 * a.d.y;
		J res(x * d.y - y * d.x);
		return l1 > 0 ? res >= 0 : res <= 0; // 严格去掉 =
	}
};
bool HPI(vector<Line> v) { // 返回 v 中每个射线的右侧的交是否非空
	sort(v.begin(), v.end());// 按方向排极角序
	{ // 同方向取最严格的一个
		vector<Line> t; int n(v.size());
		for(int i(0), j; i < n; i = j) {
			LL mx(-9e18); int mxi;
			for(j = i; j < n && v[i].d * v[j].d == 0; j++) {
				LL tmp(v[j].s * v[i].d);
				if(tmp > mx)
					mx = tmp, mxi = j;
			}
			t.push_back(v[mxi]);
		}
		swap(v, t);
	}
	deque<Line> res;
	bool emp(false);
	for(auto i : v) {
		if(res.size() == 1) {
			if(res[0].d * i.d == 0 && !i.include(res[0].s))	{
				res.pop_back();
				emp = true;
			}
		} else if(res.size() >= 2) {
			while(res.size() >= 2u && !i.include(res.back(), res[res.size() - 2])) {
				if(i.d * res[res.size() - 2].d == 0 || !res.back().include(i, res[res.size() - 2])) {
					emp = true;
					break;
				}
				res.pop_back();
			}
			while(res.size() >= 2u && !i.include(res[0], res[1])) res.pop_front();
		}
		if(emp) break;
		res.push_back(i);
	}
	while (res.size() > 2u && !res[0].include(res.back(), res[res.size() - 2])) res.pop_back();
	return !emp;// emp: 是否为空, res 按顺序即为半平面交
}
