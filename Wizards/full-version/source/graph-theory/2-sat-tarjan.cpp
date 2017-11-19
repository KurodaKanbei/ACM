template<class TAT>void checkmin(TAT &x,TAT y)
{
	if(y < x) x = y;
}
void tarjan(int u)
{
	dfn[u] = low[u] = ++dt;
	flag[u] = true;
	stk.push(u);
	
	for(int i = 0; i < vec[u].size(); i++)
	{
		int v = vec[u][i];
		
		if(!dfn[v])
		{
			tarjan(v);
			checkmin(low[u], low[v]);
		}
		else if(flag[v])
		{
			checkmin(low[u], dfn[v]);
		}
	}
	
	if(low[u] == dfn[u])
	{
		++bcnt;
		while(stk.top() != u)
		{
			block[stk.top()] = bcnt;
			flag[stk.top()] = false;
			stk.pop();
		}
		
		block[u] = bcnt;
		flag[u] = false;
		stk.pop();
	}
}
bool solve()
{
		for(int i = 1; i <= 2 * n; i++)
			if(!dfn[i]) tarjan(i);
		
		bool ans = true;
		
		for(int i = 1; i <= n; i++)
			if(block[2 * i] == block[2 * i - 1])
			{
				ans = false;
				break;	
			}
      
    return ans;
}
