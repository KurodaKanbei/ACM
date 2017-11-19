void getInv(int *a, int *b, int n) {
	static int tmp[MAXN];
	b[0] = fpm(a[0], MOD - 2, MOD);
	for (int c = 2, M = 1; c < (n << 1); c <<= 1) {
		for (; M <= 3 * (c - 1); M <<= 1);
		meminit(b, c, M);
		meminit(tmp, c, M);
		memcopy(tmp, a, 0, c);
		DFT(tmp, M, 0);
		DFT(b, M, 0);
		for (int i = 0; i < M; i++) {
			b[i] = 1ll * b[i] * (2ll - 1ll * tmp[i] * b[i] % MOD + MOD) % MOD;
		}
		DFT(b, M, 1);
		meminit(b, c, M);
    }
}
