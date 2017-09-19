// 凸包中的点按逆时针方向
struct Convex {
	int n;
	std::vector<Point> a, upper, lower;
	void make_shell(const std::vector<Point>& p,
			std::vector<Point>& shell) {  // p needs to be sorted.
		clear(shell); int n = p.size(); 
		for (int i = 0, j = 0; i < n; i++, j++) {
			for (; j >= 2 && sign(det(shell[j-1] - shell[j-2],
							p[i] - shell[j-2])) <= 0; --j) shell.pop_back();
			shell.push_back(p[i]);
		}
	}
	void make_convex() {
		std::sort(a.begin(), a.end());
		make_shell(a, lower); 
		std::reverse(a.begin(), a.end());
		make_shell(a, upper);
		a = lower; a.pop_back();
		a.insert(a.end(), upper.begin(), upper.end());
		if ((int)a.size() >= 2) a.pop_back();
		n = a.size();
	}
	void init(const std::vector<Point>& _a) {
		clear(a); a = _a; n = a.size();
		make_convex();
	}
	void read(int _n) {  // Won't make convex.
		clear(a); n = _n; a.resize(n);
		for (int i = 0; i < n; i++) 
			a[i].read();
	}
	std::pair<DB, int> get_tangent(
			const std::vector<Point>& convex, const Point& vec) {
		int l = 0, r = (int)convex.size() - 2;
		assert(r >= 0);
		for (; l + 1 < r; ) {
			int mid = (l + r) / 2;
			if (sign(det(convex[mid + 1] - convex[mid], vec)) > 0)
				r = mid;
			else l = mid;
		}
		return std::max(std::make_pair(det(vec, convex[r]), r),
				std::make_pair(det(vec, convex[0]), 0));
	}
	int binary_search(Point u, Point v, int l, int r) {
		int s1 = sign(det(v - u, a[l % n] - u));
		for (; l + 1 < r; ) {
			int mid = (l + r) / 2;
			int smid = sign(det(v - u, a[mid % n] - u));
			if (smid == s1) l = mid;
			else r = mid;
		}
		return l % n;
	}
	// 求凸包上和向量 vec 叉积最大的点，返回编号，共线的多个切点返回任意一个
	int get_tangent(Point vec) {
		std::pair<DB, int> ret = get_tangent(upper, vec);
		ret.second = (ret.second + (int)lower.size() - 1) % n;
		ret = std::max(ret, get_tangent(lower, vec));
		return ret.second;
	}
	// 求凸包和直线 u, v 的交点，如果不相交返回 false，如果有则是和 (i, next(i)) 的交点，交在点上不确定返回前后两条边其中之一
	bool get_intersection(Point u, Point v, int &i0, int &i1) {
		int p0 = get_tangent(u - v), p1 = get_tangent(v - u);
		if (sign(det(v - u, a[p0] - u)) * sign(det(v - u, a[p1] - u)) <= 0) {
			if (p0 > p1) std::swap(p0, p1);
			i0 = binary_search(u, v, p0, p1);
			i1 = binary_search(u, v, p1, p0 + n);
			return true;
		}
		else return false;
	}
};
