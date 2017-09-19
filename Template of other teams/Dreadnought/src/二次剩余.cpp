void calcH(int &t, int &h, const int p) {
	int tmp = p - 1; for (t = 0; (tmp & 1) == 0; tmp /= 2) t++; h = tmp;
}
// solve equation x^2 mod p = a
bool solve(int a, int p, int &x, int &y) {
	srand(19920225);
	if (p == 2) { x = y = 1; return true; }
	int p2 = p / 2, tmp = power(a, p2, p);
	if (tmp == p - 1) return false;
	if ((p + 1) % 4 == 0) {
		x = power(a, (p + 1) / 4, p); y = p - x; return true;
	} else {
		int t, h, b, pb; calcH(t, h, p);
		if (t >= 2) {
			do {b = rand() % (p - 2) + 2;
			} while (power(b, p / 2, p) != p - 1);
			pb = power(b, h, p);
		} int s = power(a, h / 2, p);
		for (int step = 2; step <= t; step++) {
			int ss = (((long long)(s * s) % p) * a) % p;
			for (int i = 0; i < t - step; i++) ss = ((long long)ss * ss) % p;
			if (ss + 1 == p) s = (s * pb) % p; pb = ((long long)pb * pb) % p;
		} x = ((long long)s * a) % p; y = p - x;
	} return true; 
}
