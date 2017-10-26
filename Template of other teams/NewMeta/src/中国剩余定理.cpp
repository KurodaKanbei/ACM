inline void euclid(const LL & a, const LL &b, LL &x, LL &y) {
	if (b == 0) x = 1, y = 0;
	else euclid(b, a % b, y, x), y -= a / b * x;
}
void combine(LL r1, LL m1, LL &r2, LL &m2, LL d) {
	if(m1 > m2) swap(r1, r2), swap(m1, m2);
	LL x, y;
	euclid(m1, m2, x, y);
	m1 /= d;
	LL tmp((r1 - r2) / d * y % m1);
	if(tmp < 0) tmp += m1;
	r2 += tmp * m2;
	m2 *= m1;
}
inline bool crt(int n, const vector<LL> & r, const vector<LL> & m, LL & rem, LL & mod) {
	rem = 0; mod = 1;
	for (int i = 0; i < (int)r.size(); ++i) {
		LL div(gcd(mod, m[i]));
		if ((r[i] - rem) % div) {
			return false;
		}
		combine(r[i], m[i], rem, mod, div);
	}
	return true;
}
