// 带插入版本 , 没有写内存回收 , 空间复杂度 $n \log n$ , 
// 如果不需要插入可以大大简化 N 为最大点数, D 为每个点的最大
// 维度 , d 为实际维度 以查找最近点为例 ret 为当前最近点的距离
// 的平方用来剪枝 , 查询 k 近或 k 远的方法类似 注意先 initnull
const ll INF = (int)1e9 + 10;
const int N = 2000000 + 10, D = 5;
const double SCALE = 0.75; int d;
struct poi { int x[D]; } buf[N];
long long dist(const poi &a, const poi &b) {...}
struct node {
    int dep, sz; node *ch[2], *p; poi val, maxv, minv;
    void set(node *t, int d) { ch[d] = t; t->p = this; }
    bool dir() { return this == p->ch[1]; }
    bool balanced(){return (double)max(ch[0]->sz,ch[1]->sz)
                            <= (double)sz * SCALE; }
    void update() {
        sz = ch[0]->sz + ch[1]->sz + 1;
        for(int i = 0; i < d; ++ i) {
            maxv.x[i] = max(val.x[i],
                    max(ch[0]->maxv.x[i], ch[1]->maxv.x[i]));
            minv.x[i] = min(val.x[i],
                    min(ch[0]->minv.x[i], ch[1]->minv.x[i]));
        } }
} nodepool[N], *totnode, *null;
node* newnode(poi p, int dep) {
    node *t = totnode ++; t->ch[0] = t->ch[1] = t->p = null;
    t->dep = dep; t->val = t->maxv = t->minv = p; t->sz = 1;
    return t; } // heap<pair<ll, poi>> ret; int ans_sz;
int ctr; int cmp(const poi &a,const poi &b)
{return a.x[ctr]<b.x[ctr];}
struct KDTree {
    node *root; KDTree() { root = null; } 
    KDTree(poi *a, int n) { root = build(a, 0, n - 1, 0); }
    node *build(poi *a, int l, int r, int dep) {
        if (l > r) return null; ctr = dep;
        int mid = (l + r) >> 1;
        nth_element(a + l, a + mid, a + r + 1, cmp);
        node *t = newnode(a[mid], dep);
        t->set(build(a, l, mid - 1, (dep + 1) % d), 0);
        t->set(build(a, mid + 1, r, (dep + 1) % d), 1);
        t->update(); return t;
    }
    void tranv(node *t, poi *vec, int &tot) {// insert 时要
        if (t == null) return; vec[tot ++] = t->val;
        tranv(t->ch[0],vec,tot); tranv(t->ch[1],vec,tot);
    }
    void rebuild(node *t) {// insert 时要
        node *p = t->p; int tot = 0;
        tranv(t, buf, tot);
        node *u = build(buf, 0, tot - 1, t->dep);
        p->set(u, t->dir());
        for( ; p != null; p = p->p) p->update();
        if (t == root) root = u;
    }
    void insert(poi p) {// insert 时要
        if (root == null) { root = newnode(p, 0); return; }
        node *cur = root, *las = null; int dir = 0;
        for( ; cur != null; ) { las = cur;
            dir = (p.x[cur->dep] > cur->val.x[cur->dep]);
            cur = cur->ch[dir]; }
        node *t = newnode(p, (las->dep+1)%d), *bad=null;
        las->set(t, dir);
        for( ; t != null; t = t->p) {
            t->update(); if (!t->balanced()) bad = t; }
        if (bad != null) rebuild(bad);
    }
    ll calc(poi u, node *t, int d) {
        ll l = t->minv.x[d], r = t->maxv.x[d], x = u.x[d];
        if (x >= l && x <= r) return 0LL;
        ll ret = min(abs(x - l), abs(x - r));
        return ret * ret; // ret
    }
    void updateans(poi u, poi p) { /* 在这里更新答案 */ }
    void query(node *t, poi p) {
        if (t == null) return; updateans(t->val, p);
        ll eval[2] = {calc(p, t->ch[0], t->dep),
                    calc(p, t->ch[1], t->dep)};
        int cho = eval[0] <= eval[1]; // 较优侧先搜
        if(/*eval[cho^1] 可更新 ret*/)query(t->ch[cho^1],p);
        if(/*eval[cho] 可更新 ret*/)query(t->ch[cho], p);
    }
    void query(poi p) { query(root, p); }
};
void initnull(int d) { ::d = d;
    totnode = nodepool; null = totnode ++; null->sz = 0;
    for(int i = 0; i < d; ++ i) {
        null->maxv.x[i] = -INF; null->minv.x[i] = INF; }
}