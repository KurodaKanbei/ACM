bool BFS() {
    for(int i = 1; i <= ind; i++) dep[i] = 0;
    dep[S] = 1, line.push(S);
    while(!line.empty()) {
        int now = line.front(); line.pop();
        for(int i = head[now], p; i ; i = edge[i].next)
            if(edge[i].cap && !dep[p = edge[i].v])
                dep[p] = dep[now] + 1, line.push(p);
    }
    if(dep[T]) {
        for(int i = 1; i <= ind; i++) cur[i] = head[i];
        return true;    
    }
    else return false;
}
int DFS(int a,int flow) {
    if(a == T) return flow;
    int ret = 0;
    for(int &i = cur[a], p; i ; i = edge[i].next)
        if(dep[p = edge[i].v] == dep[a] + 1 && edge[i].cap) {
            int ff = DFS(p, std::min(flow, edge[i].cap));
            flow -= ff, edge[i].cap -= ff;
            ret += ff, edge[i ^ 1].cap += ff;
            if(!flow) break;
        }
	return ret;
}
int solve() {
    int totflow = 0;
    while(BFS()) {
        totflow += DFS(S, INF);
    }
    return totflow;
}
