bool miller_rabin(long long n, int base) {
    long long n2 = n - 1, s = 0;
    while (~n2 & 1) n2 >>= 1, s++;
    long long ret = powmod(base, n2, n);
    if (ret == 1 || ret == n - 1) return true;
    for (s--; s >= 0; s--) {
		if ((ret = mulmod(ret, ret, n)) == n - 1) return true;
	}
    return false; // n is not a strong pseudo prime
}
bool isprime(long long n) {
	static long long base[] = {2,3,5,7,11,13,17,19,23,29,31,37};
	static long long lim[] = {4, 0, 1373653LL, 25326001LL,
        25000000000LL, 2152302898747LL, 3474749660383LL,
        341550071728321LL, 0, 0, 0, 0};
	if (n < 2 || n == 3215031751LL) return 0;
	for(int i = 0; i < 12 && base[i] < n; ++i) {
		if (n < lim[i]) return true;
		if (!miller_rabin(n, base[i])) return false;
	}
	return true;
}
long long f(long long x, long long m) { return (mulmod(x, x, m) + 1) % m; }
long long rho(long long n) {
	if (n == 1 || isprime(n)) return n;
	if (n % 2 == 0) return 2;
	for (int i = 1; ; i ++) {
		long long x = i, y = f(x, n), p = __gcd(y - x, n);
		while (p == 1) { x = f(x, n); y = f(f(y, n), n);
			p = __gcd((y - x + n) % n, n) % n;
		}
		if (p != 0 && p != n) return p;
}} // 分解时需特判 n = 1
