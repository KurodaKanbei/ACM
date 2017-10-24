int prepare(int n) {
	int len = 1;
	for (; len <= 2 * n; len <<= 1);
	for (int i = 0; i < len; i++) {
		e[0][i] = Complex(cos(2 * pi * i / len), sin(2 * pi * i / len));
		e[1][i] = Complex(cos(2 * pi * i / len), -sin(2 * pi * i / len));
	}
	return len;
}
void DFT(Complex *a, int n, int f) {
	for (int i = 0, j = 0; i < n; i++) {
		if (i > j) std::swap(a[i], a[j]);
		for (int t = n >> 1; (j ^= t) < t; t >>= 1);
	}
	for (int i = 2; i <= n; i <<= 1)
		for (int j = 0; j < n; j += i)
			for (int k = 0; k < (i >> 1); k++) {
				Complex A = a[j + k];
				Complex B = e[f][n / i * k] * a[j + k + (i >> 1)];
				a[j + k] = A + B;
				a[j + k + (i >> 1)] = A - B;
			}
	if (f == 1) {
		for (int i = 0; i < n; i++)
			a[i].a /= n;
	}
}
