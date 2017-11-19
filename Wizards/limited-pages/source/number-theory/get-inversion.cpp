void ex_gcd(long long a, long long b, long long &x, long long &y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return;
	}
	long long xx, yy;
	ex_gcd(b, a % b, xx, yy);
	y = xx - a / b * yy;
	x = yy;
}

long long inv(long long x, long long MODN) {
	long long inv_x, y;
	ex_gcd(x, MODN, inv_x, y);
	return (inv_x % MODN + MODN) % MODN;
}
