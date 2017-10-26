// 如果想求一个字符串相对另外一个字符串的最长公共前缀, 可以把他们拼接起来从而求得
void exkmp(char *s, int *a, int n) {
	a[0] = n; int p = 0, r = 0;
	for (int i = 1; i < n; ++i) {
		a[i] = (r > i) ? min(r - i, a[i - p]) : 0;
		while (i + a[i] < n && s[i + a[i]] == s[a[i]]) ++a[i];
		if (r < i + a[i]) r = i + a[i], p = i;
}}
