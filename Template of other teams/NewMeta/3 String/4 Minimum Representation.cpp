std::string find(std::string s) {
	int i, j, k, l, n = s.length(); s += s;
	for(i = 0, j = 1; j < n;) {
		for (k = 0; k < n && s[i + k] == s[j + k]; k++);
		if (k >= n) break;
		if (s[i + k] < s[j + k]) j += k + 1; // 如果求最大表示，换成 '>'
		else l = i + k, i = j, j = max(l, j) + 1;
	}
	return s.substr(i, n); // 可以通过求循环节来得到所有位置
}
