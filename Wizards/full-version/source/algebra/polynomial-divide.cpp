void divide(int n, int m, int *a, int *b, int *d, int *r) { // $n$、$m$分别为多项式$A$（被除数）和$B$（除数）的指数 + 1
	static int M, tA[MAXN], tB[MAXN], inv[MAXN], tD[MAXN];
	for (; n > 0 && a[n - 1] == 0; n--);
	for (; m > 0 && b[m - 1] == 0; m--);
	for (int i = 0; i < n; i++) tA[i] = a[n - i - 1];
	for (int i = 0; i < m; i++) tB[i] = b[m - i - 1];
	for (M = 1; M <= n - m + 1; M <<= 1);
	if (m < M) meminit(tB, m, M);
	getInv(tB, inv, M);
	for (M = 1; M <= 2 * (n - m + 1); M <<= 1);
	meminit(inv, n - m + 1, M);
	meminit(tA, n - m + 1, M);
	DFT(inv, M, 0);
	DFT(tA, M, 0);
	for (int i = 0; i < M; i++) {
		d[i] = 1ll * inv[i] * tA[i] % MOD;
	}
	DFT(d, M, 1);
	std::reverse(d, d + n - m + 1);
	for (M = 1; M <= n; M <<= 1);
	memcopy(tB, b, 0, m);
	if (m < M) meminit(tB, m, M);
	memcopy(tD, d, 0, n - m + 1);
	meminit(tD, n - m + 1, M);
	DFT(tD, M, 0);
	DFT(tB, M, 0);
	for (int i = 0; i < M; i++) {
		r[i] = 1ll * tD[i] * tB[i] % MOD;
	}
	DFT(r, M, 1);
	meminit(r, n, M);
	for (int i = 0; i < n; i++) {
		r[i] = (a[i] - r[i] + MOD) % MOD;
	}
}
