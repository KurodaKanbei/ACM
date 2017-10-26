// 把串 s 划分成 lyndon words，s1, s2, s3, ..., sk
// 每个串都严格小于他们的每个后缀，且串大小不增
// 如果求每个前缀的最小后缀，取最后一次 k 经过这个前缀的右边界时的信息更新。
// 如果求每个前缀的最大后缀，更改大小于号，并且取第一次 k 经过这个前缀的信息更新。
void lynDecomp() {
	vector<string> ss;
	for (int i = 0; i < n; ) {
		int j = i, k = i + 1; //mnsuf[i] = i;
		for (; k < n && s[k] >= s[j]; k++) {
			if (s[k] == s[j]) j++; // mnsuf[k] = mnsuf[j] + k - j;
			else j = i; // mnsuf[k] = i;
		}
		for (; i <= j; i += k - j) ss.push_back(s.substr(i, k - j));
	}
}
