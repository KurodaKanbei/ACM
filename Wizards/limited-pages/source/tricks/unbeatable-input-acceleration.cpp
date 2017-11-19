// getchar()读入优化 << 关同步cin << 此优化
// 用isdigit()会小幅变慢
// 返回 false 表示读到文件尾
namespace Reader {
    const int L = (1 << 15) + 5;
    char buffer[L], *S, *T;
    __inline bool getchar(char &ch) {
        if (S == T) {
            T = (S = buffer) + fread(buffer, 1, L, stdin);
            if (S == T) {
				ch = EOF;
				return false;
			}
        }
		ch = *S++;
		return true;
    }
    __inline bool getint(int &x) {
		char ch; bool neg = 0;
		for (; getchar(ch) && (ch < '0' || ch > '9'); ) neg ^= ch == '-';
		if (ch == EOF) return false;
		x = ch - '0';
		for (; getchar(ch), ch >= '0' && ch <= '9'; )
			x = x * 10 + ch - '0';
		if (neg) x = -x;
		return true;
    }
}
