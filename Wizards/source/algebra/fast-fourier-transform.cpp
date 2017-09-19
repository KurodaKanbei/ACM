// n 必须是2的次幂
void fft(Complex a[], int n, int f) {
	for (int i = 0; i < n; ++i)
		if (R[i] < i) swap(a[i], a[R[i]]);
	for (int i = 1, h = 0; i < n; i <<= 1, h++) {
		Complex wn = Complex(cos(pi / i), f * sin(pi / i));
		Complex w = Complex(1, 0);
		for (int k = 0; k < i; ++k, w = w * wn) tmp[k] = w; 
		for (int p = i << 1, j = 0; j < n; j += p) {
			for (int k = 0; k < i; ++k) {
				Complex x = a[j + k], y = a[j + k + i] * tmp[k];
				a[j + k] = x + y; a[j + k + i] = x - y;
			}
		}
	}
}
