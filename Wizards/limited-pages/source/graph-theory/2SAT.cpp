int rev(int x) {
	return (x & 1) ? x + 1 : x - 1;
}
bool dfs(int x) {
	if(used[x]) return true;
	if(used[rev(x)]) return false;
	used[x] = true, vis.push_back(x);
	for(int i = 0; i < vec[x].size(); i++)
		if(!dfs(vec[x][i])) return false;
	return true;
}
bool check(int x) {
	bool res = dfs(x);
	vis.clear();
	for(int i = 0; i < vis.size(); i++) used[vis[i]] = false;
	return res;
}
bool work() {
	bool ans = true;
	for(int i = 1; i <= n; i++) {
		if(check(2 * i - 1)) dfs(2 * i - 1);
		else if(check(2 * i))  dfs(2 * i);
		else { ans = false; break; }
	}
	return ans;
}
