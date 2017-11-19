int cnt,n,m,dis[N],last[N],a[N],tmp[N],ans[N][N],s,t,mark[N];
struct edge{int to,c,next;}e[N*200];
queue <int> q;
void addedge(int u,int v,int c) {
    e[++cnt].to=v;e[cnt].c=c;
	e[cnt].next=last[u];last[u]=cnt;
    e[++cnt].to=u;e[cnt].c=c;
	e[cnt].next=last[v];last[v]=cnt;
}
bool bfs() {
    memset(dis,0,sizeof(dis));
    dis[s]=2;
    while (!q.empty()) q.pop();
    q.push(s);
    while (!q.empty()) {
        int u=q.front();
        q.pop();
        for (int i=last[u];i;i=e[i].next)
            if (e[i].c&&!dis[e[i].to]) {
                dis[e[i].to]=dis[u]+1;
                if (e[i].to==t) return 1;
                q.push(e[i].to);
            }
    }
    return 0;
}
int dfs(int x,int maxf) {
    if (x==t||!maxf) return maxf;
    int ret=0;
    for (int i=last[x];i;i=e[i].next)
        if (e[i].c&&dis[e[i].to]==dis[x]+1) {
            int f=dfs(e[i].to,min(e[i].c,maxf-ret));
            e[i].c-=f;
            e[i^1].c+=f;
            ret+=f;
            if (ret==maxf) break;
        }
    if (!ret) dis[x]=0;
    return ret;
}
void dfs(int x) {
    mark[x]=1;
    for (int i=last[x];i;i=e[i].next)
        if (e[i].c&&!mark[e[i].to]) dfs(e[i].to);
}
void solve(int l,int r) {
    if (l==r) return;
    s=a[l];t=a[r];
    for (int i=2;i<=cnt;i+=2)
        e[i].c=e[i^1].c=(e[i].c+e[i^1].c)/2;
    int flow=0;
    while (bfs()) flow+=dfs(s,inf);
    memset(mark,0,sizeof(mark));
    dfs(s);
    for (int i=1;i<=n;i++)
        if (mark[i])
            for (int j=1;j<=n;j++)
                if (!mark[j])
            ans[i][j]=ans[j][i]=min(ans[i][j],flow);
    int i=l,j=r;
    for (int k=l;k<=r;k++)
        if (mark[a[k]]) tmp[i++]=a[k];
        else tmp[j--]=a[k];
    for (int k=l;k<=r;k++)
        a[k]=tmp[k];
    solve(l,i-1);
    solve(j+1,r);
}
