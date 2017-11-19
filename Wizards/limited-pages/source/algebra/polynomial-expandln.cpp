void getDiff(int *a, int *b, int n) { // 多项式取微分
	for (int i = 0; i + 1 < n; i++) {
		b[i] = 1ll * (i + 1) * a[i + 1] % MOD;
	}
	b[n - 1] = 0;
}
void getInt(int *a, int *b, int n) { // 多项式取积分，积分常数为0
	static int inv[MAXN];
	inv[1] = 1;
	for (int i = 2; i < n; i++) {
		inv[i] = 1ll * (MOD - MOD / i) * inv[MOD % i] % MOD;
	}
	b[0] = 0;
	for (int i = 1; i < n; i++) {
		b[i] = 1ll * a[i - 1] * inv[i] % MOD;
	}
}
void getLn(int *a, int *b, int n) {
	static int inv[MAXN], d[MAXN];
	int M = 1;
	for (; M <= 2 * (n - 1); M <<= 1);
	getInv(a, inv, n);
	getDiff(a, d, n);
	meminit(d, n, M);
	meminit(inv, n, M);
	DFT(d, M, 0); DFT(inv, M, 0);
	for (int i = 0; i < M; i++) {
		d[i] = 1ll * d[i] * inv[i] % MOD;
	}
	DFT(d, M, 1);
	getInt(d, b, n);
}
void getExp(int *a, int *b, int n) {
	static int ln[MAXN], tmp[MAXN];
	b[0] = 1;
	for (int c = 2, M = 1; c < (n << 1); c <<= 1) {
		for (; M <= 2 * (c - 1); M <<= 1);
		int bound = std::min(c, n);
		memcopy(tmp, a, 0, bound);
		meminit(tmp, bound, M);
		meminit(b, c, M);
		getLn(b, ln, c);
		meminit(ln, c, M);
		DFT(b, M, 0);
		DFT(tmp, M, 0);
		DFT(ln, M, 0);
		for (int i = 0; i < M; i++) {
			b[i] = 1ll * b[i] * (1ll - ln[i] + tmp[i] + MOD) % MOD;
		}
		DFT(b, M, 1);
		meminit(b, c, M);
	}
}

