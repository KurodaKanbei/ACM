const int N = 2005;
int H[N][N], V[N][N];
char s[N], t[N];
int main() {
	gets(s + 1); gets(t + 1);
	int n = (int) strlen(s + 1);
	int m = (int) strlen(t + 1);
	for (int i = 1; i <= m; ++ i) H[0][i] = i;
	for (int i = 1; i <= n; ++ i) {
		for (int j = 1; j <= m; ++ j) {
			if (s[i] == t[j]) {
				H[i][j] = V[i][j - 1];
				V[i][j] = H[i - 1][j];
			} else {
				H[i][j] = max(H[i - 1][j], V[i][j - 1]);
				V[i][j] = min(H[i - 1][j], V[i][j - 1]);
    }}}
	for (int i = 1; i <= m; ++ i) {
		int ans = 0;
		for (int j = i; j <= m; ++ j) {
			ans += H[n][j] < i;
			printf("%d%c", ans, " \n"[j == m]);
		}
	}
}
