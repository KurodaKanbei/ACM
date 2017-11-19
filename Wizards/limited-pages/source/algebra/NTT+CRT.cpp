#define meminit(A, l, r) memset(A + (l), 0, sizeof(*A) * ((r) - (l)))
#define memcopy(B, A, l, r) memcpy(B, A + (l), sizeof(*A) * ((r) - (l)))
void DFT(int *a, int n, int f) { //f=1 逆DFT
	for (register int i = 0, j = 0; i < n; i++) {
		if (i > j) std::swap(a[i], a[j]);
		for (register int t = n >> 1; (j ^= t) < t; t >>= 1);
	}
	for (register int i = 2; i <= n; i <<= 1) {
		static int exp[MAXN];
		exp[0] = 1; exp[1] = fpm(PRT, (MOD - 1) / i, MOD);
		if (f == 1) exp[1] = fpm(exp[1], MOD - 2, MOD);
		for (register int k = 2; k < (i >> 1); k++) {
			exp[k] = 1ll * exp[k - 1] * exp[1] % MOD;
		}
		for (register int j = 0; j < n; j += i) {
			for (register int k = 0; k < (i >> 1); k++) {
				register int &pA = a[j + k], &pB = a[j + k + (i >> 1)];
				register long long B = 1ll * pB * exp[k];
				pB = (pA - B) % MOD;
				pA = (pA + B) % MOD;
			}
		}
	}
	if (f == 1) {
		register int rev = fpm(n, MOD - 2, MOD);
		for (register int i = 0; i < n; i++) {
			a[i] = 1ll * a[i] * rev % MOD;
			if (a[i] < 0) { a[i] += MOD; }
		}
	}
}
// 在不写高精度的情况下合并FFT所得结果对$MOD$取模后的答案
// 值得注意的是，这个东西不能最后再合并，而是应该每做一次多项式乘法就CRT一次
int CRT(int *a) {
	static int x[3];
	for (int i = 0; i < 3; i++) {
		x[i] = a[i];
		for (int j = 0; j < i; j++) {
			int t = (x[i] - x[j] + FFT[i] -> MOD) % FFT[i] -> MOD;
			if (t < 0) t += FFT[i] -> MOD;
			x[i] = 1LL * t * inv[j][i] % FFT[i] -> MOD;
		}
	}
	int sum = 1, ret = x[0] % MOD;
	for (int i = 1; i < 3; i ++) {
		sum = 1LL * sum * FFT[i - 1] -> MOD % MOD;
		ret += 1LL * x[i] * sum % MOD;
		if(ret >= MOD) ret -= MOD;
	}
	return ret;
}
for (int i = 0; i < 3; i++) // inv数组的预处理过程，inverse($x$, $p$)表示求$x$在$p$下逆元
	for (int j = 0; j < 3; j++)
		inv[i][j] = inverse(FFT[i] -> MOD, FFT[j] -> MOD);

