int main() {
	static int mu[N], is_prime[N];
	fill(is_prime, is_prime + MAXV, true);
	mu[1] = 1;
	vector<int> primes;
	for (int i = 2; i < MAXV; i++) {
		if (is_prime[i]) {
			primes.push_back(i); mu[i] = -1;
		}
		for (auto p : primes) {
			if (1LL * i * p >= MAXV) break;
			is_prime[p * i] = false;
			if (i % p == 0) {
				mu[i * p] = 0; break;
			} else { mu[i * p] = -mu[i]; }
		}
	}
	return 0;
}
