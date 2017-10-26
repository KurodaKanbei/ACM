#include <bits/stdc++.h>

using namespace std;

pair<int, int> factor(int n) {
	pair<int, int> ret = {-1, -1};
	for (int i = 2; i <= n; i++) {
		if (n % i == 0) {
			if (ret.first != -1) return {-1, -1};
			ret.first = i;
			ret.second = 0;
			while (n % i == 0) {
				ret.second++;
				n /= i;
			}
		}
	}
	return ret;
}

int assume(int n) {
	if (n == 4) return -1;
	pair<int, int> d = factor(n);
	if (d.first == -1 && n % 2 == 0) {
		d = factor(n / 2);
	}
	if (d.first == -1 || d.first == 2) {
		return 1;
	}
	return -1;
}

int test(int n) {
	int ret = 1;
	for (int i = 1; i <= n; i++) {
		if (__gcd(i, n) == 1) {
			ret = 1LL * ret * i % n;
		}
	}
	if (ret == n - 1) return -1;
	if (ret != 1) assert(false);
	return 1;
}

int main() {
	for (int i = 105000; ; i++) {
		if (i % 1000 == 0) printf("i = %d\n", i);
		assert(assume(i) == test(i));
	}
	return 0;
}
