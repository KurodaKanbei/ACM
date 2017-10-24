//从一个奇度点dfs，sqn即为回路/路径
//first存点，second存边的编号，正反边编号一致
//清空cur、used数组
void getCycle(int u)
{
	for(int &i=cur[u]; i < (int)adj[u].size(); ++ i) {
		int id = adj[u][i].second;
		if (used[id]) continue;
		used[id] = true;
		getCycle(adj[u][i].first);
	}
	sqn.push_back(u);
}

