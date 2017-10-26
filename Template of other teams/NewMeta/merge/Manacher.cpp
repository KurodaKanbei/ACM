void Manacher(char text[], int n, int palindrome[]) {
	palindrome[0] = 1;
	for (int i = 1, j = 0, i < (n << 1) - 1; ++ i) {
		int p = i >> 1;
		int q = i - p;
		int r = (j + 1 >> 1) + palindrome[j] - 1;
		palindrome[i] = r < q ? 0 : min(r - q + 1, palindrome[(j << 1) - i]);
		while (0 <= p - palindrome[i] && q + palindrome[i] < n && text[p - palindrome[i]] == text[q + palindrome[i]]) {
			palindrome[i] ++;
		}
		if (q + palindrome[i] - 1 > r) { j = i; }
	}
}

// 0 base
void pre_ex_kmp(const string& text, int len, int next[]) {
    int i, ind = 0, k = 1;
    next[0] = len;
    while (ind + 1 < len && text[ind + 1] == text[ind]) ind++;
    next[1] = ind;
    for (i = 2; i < len; i++) {
        if (i <= k + next[k] - 1 && next[i - k] + i < k + next[k]) {
            next[i] = next[i - k];
        } else {
            ind = std::max(0, k + next[k] - i);
            while (ind + i < len && text[ind + i] == text[ind]) ind++;
            next[i] = ind;
            k = i;
        }
    }
}

void ex_kmp(const string &s, int slen, const string &t, int tlen, int extend[]) {
    int i, ind = 0, k = 0;
	static int next[LEN];
    pre_ex_kmp(t, tlen, next);
    while (ind < slen && ind < tlen && t[ind] == s[ind]) ind++;
    extend[0] = ind;
    for (i = 1; i < slen; i++) {
        int p = k + extend[k] - 1, L = next[i - k];
        if ((i - 1) + L < p) {
            extend[i] = L;
        } else {
            ind = std::max(0, p - i + 1);
            while (ind + i < slen && ind < tlen && s[ind + i] == t[ind]) ind++;
            extend[i] = ind;
            k = i;
        }
    }
}
