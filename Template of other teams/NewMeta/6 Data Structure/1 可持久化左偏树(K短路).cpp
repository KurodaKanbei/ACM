#define nil mem
struct Node { Node *l, *r, *s; int dist; Val val, laz;
} mem[mxv]={{nil,nil,nil,-1}}; int sz; using ptr = Node*;
#define NEW(arg...) new(mem + ++sz)Node{nil,nil,nil,0,arg}
#define COPY(x) new(mem + ++sz)Node(*(x))
ptr add(ptr x, Val ope) {
    if (x == nil) return nil;
    x = COPY(x); x->val += ope; x->laz += ope; return x; }
ptr down(ptr x) {
    if (x == nil) return nil; x = COPY(x); if (x->laz)
    { x->l = add(x->l, x->laz); x->r = add(x->r, x->laz);
        x->s = add(x->s, x->laz); x->laz = 0; } return x;}
ptr sub_merge(ptr x, ptr y) {
    if (x == nil) return y; if (y == nil) return x;
    if (cmp(y->val, x->val)) swap(x, y);
    x = down(x); x->r = sub_merge(x->r, y);
    if (x->l->dist < x->r->dist) swap(x->l, x->r);
    x->dist = x->r->dist + 1; return x; }
ptr merge(ptr x, ptr y) {
    if (x == nil) return y; if (y == nil) return x;
    if (cmp(y->val, x->val)) swap(x, y); // 小根堆 (less)
    x = down(x); x->s = sub_merge(x->s, y); return x; }
ptr pop(ptr x) { // pop 操作注意仔细计算复杂度
    x = down(x); x = x->s; x = down(x);
    x->s = sub_merge(x->s, sub_merge(x->l, x->r));
    x->l = x->r = nil; return x; }
/* Hint for K 短路 : 先建最短路树, d[x] 表示到 T 的距离
非树边的权值是比最短路多走的距离 . 一条路径用经过了
某些非树边表示。考虑每次可以从最后一条非树边的末端,
新长一条从末端到 T 的路径上出发的权值最小的非树边 ;
或者是删掉最后这条非树边 (pop), 用次小边替代 .
按照非树边的权值建堆 , 需要记录末端点 . 注意判断堆非空 .
priority_queue<dis,end point at where,heap ptr> 
堆里的初值 : {d[S]+root[S].top.len, root[S].top.at, root[S]}
每次两种转移 : if ((root1 = pop(p.heap)) != nil)
{p.dis-p.heap.top.len+root1.top.len,(root1->val).at,root1}
if ((root2 = root[p.at]) != nil)
{p.dis + root2.top.len, (root2 -> val).at, root2} */
