// Complexity is $ O(pq + q^2 \log_2 p) $
int calcsgn(LL x) { return (x % 8 <= 2 || x % 8 == 7) ? 1 : -1; } // 计算mod 4的答案
// $ 1 \leq n \leq 1000, p^q \leq 1000$ 测试通过, fastpo 是 LL LL LL 参数
LL f(LL n, LL p, LL q) {
	LL mod(fastpo(p, q, INT64_MAX));
	LL phi(mod / p * (p - 1));
	static LL pre[1111111];
	pre[0] = 1;
	for(int i(1); i <= p * (q + 1); i++) pre[i] = i % p == 0 ? pre[i - 1] : pre[i - 1] * i % mod;
	LL res(1);
	LL u(n / p), v(n % p);
	for(int j(1); j < q; j++) {
		__int128 alpha(1);
		for(int i(j + 1); i < q; i++) alpha = alpha * (u - i) / (j - i);
		for(int i(j - 1); i >= 0; i--) alpha = alpha * (u - i) / (j - i);
		alpha = (alpha % phi + phi) % phi;
		res = res * fastpo(pre[j * p + v] % mod * fastpo(pre[v], phi - 1, mod) % mod * fastpo(pre[j * p], phi - 1, mod) % mod, alpha, mod) % mod;
	}
	int sgn(calcsgn(u * 2));
	int r(max((LL)1, q / 2 + 1));
	for(int j(1); j <= r; j++) {
		__int128 beta(1);
		for(int i(j + 1); i <= r; i++) beta = beta * (u - i) / (j - i);
		for(int i(j - 1); i > -j; i--) beta = beta * (u - i) / (j - i);
		beta *= u + j;
		for(int i(-j - 1); i >= -r; i--) beta = beta * (u - i) / (j - i);
		assert(beta % (j + u) == 0);
		beta /= u + j;
		beta = (beta % phi + phi) % phi;
		if(beta % 2)
			sgn *= calcsgn(j * 2);
		res = res * fastpo(pre[j * p], beta, mod) % mod;
	}
	if(p == 2) res = (res * sgn + mod) % mod;
	res = res * pre[v] % mod;
	return res;
}
