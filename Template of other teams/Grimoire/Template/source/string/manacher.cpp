//prime is the origin string(0-base)
//-10,-1,-20 are added to s
//length of s is exactly 2 * l + 3
inline void manacher(char prime[]) {
	int l = strlen(prime), n = 0;
	s[n++] = -10;
	s[n++] = -1;
	for (int i = 0; i < l; ++i) {
		s[n++] = prime[i];
		s[n++] = -1;
	}
	s[n++] = -20; f[0] = 1;
	int mx = 0, id = 0;
	for (int i = 1; i + 1 < n; ++i) {
		f[i] = i > mx ? 1 : min(f[id * 2 - i], mx - i + 1);
		while (s[i + f[i]] == s[i - f[i]]) ++f[i];
		if (i + f[i] - 1 > mx) {
			mx = i + f[i] - 1;
			id = i;
		}
	}
}
