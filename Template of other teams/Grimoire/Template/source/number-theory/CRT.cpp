inline void fix(LL &x, LL y) {
	x = (x % y + y) % y;
}
bool solve(int n, std::pair<LL, LL> a[],
                  std::pair<LL, LL> &ans) {
	ans = std::make_pair(1, 1);
	for (int i = 0; i < n; ++i) {
		LL num, y;
		euclid(ans.second, a[i].second, num, y);
		LL divisor = std::__gcd(ans.second, a[i].second);
		if ((a[i].first - ans.first) % divisor) {
			return false;
		}
		num *= (a[i].first - ans.first) / divisor;
		fix(num, a[i].second);
		ans.first += ans.second * num;
		ans.second *= a[i].second / divisor; 
		fix(ans.first, ans.second);
	}
	return true;
}
