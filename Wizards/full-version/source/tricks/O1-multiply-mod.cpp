// 需要保证 x 和 y 非负
long long mult(long long x, long long y, long long MODN) {
	long long t = (x * y - (long long)((long double)x / MODN * y + 1e-3) * MODN) % MODN;
	return t < 0 ? t + MODN : t;
}
