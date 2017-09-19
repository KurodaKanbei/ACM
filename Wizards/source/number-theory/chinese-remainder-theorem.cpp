// 返回 (ans, M)，其中ans是模M意义下的解
std::pair<long long, long long> CRT(const std::vector<long long>& m, const std::vector<long long>& a) {
	long long M = 1, ans = 0;
	int n = m.size();
	for (int i = 0; i < n; i++) M *= m[i];
	for (int i = 0; i < n; i++) {
		ans = (ans + (M / m[i]) * a[i] % M * inv(M / m[i], m[i])) % M;  // 可能需要大整数相乘取模
	}
	return std::make_pair(ans, M);
}
