void multiply(int &c, int &d, int a, int b, int w, int MOD) {
	int cc = 1LL * a * c % MOD + 1LL * b * d % MOD * w % MOD;
	cc %= MOD;
	int dd = 1LL * a * d % MOD + 1LL * b * c % MOD;
	dd %= MOD;
	c = cc, d = dd;
}
// answers are x and MOD - x
bool solve(int n, int &x, int MOD) {
	if (MOD == 2) { return x = 1, true; }
	if (power(n, MOD / 2, MOD) == MOD - 1) return false;
	int a, w;
	for (a = 0, w = (-n + MOD) % MOD; ; a ++) {
		if ((w = ((1LL * a * a % MOD - n + MOD) % MOD)) == 0) {
			return x = a, true;
		} else if (power(w, MOD / 2, MOD) == MOD - 1) { break; }
	}
	// x = (a + sqrt(w)) ^ ((p + 1) / 2)
	int times = (MOD + 1) / 2;
	int b = 1, c = 1, d = 0;
	while (times) {
		if (times & 1) multiply(c, d, a, b, w, MOD);
		multiply(a, b, a, b, w, MOD);
		times >>= 1;
	}
	return x = c, true;
}
