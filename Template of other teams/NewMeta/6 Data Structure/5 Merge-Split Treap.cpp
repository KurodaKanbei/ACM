// 合并两个历史版本在构造数据下深度会不断退化, 可达 log 的几十倍 .
#define nil mem
struct Node {int fit; Node *l, *r; Key key; Val val, vals;
} mem[mxv] = {{0, nil, nil}}; int sz; using ptr = Node*;
#define NEW(arg...) new(mem+ ++sz)Node{rand(),nil,nil,arg}
ptr down(ptr x) {x = COPY(x); if (x->laz) {...} return x;}
pair<ptr,ptr> split(ptr x, Key key) {
    ptr t; if (x == nil) return {nil, nil}; x = down(x);
    return x->key > key // x->l->sz+1>n  key(n 个 ) 在左边
        ? (tie(t, x->l)=split(x->l, key), mp(t, renew(x)))
        : (tie(x->r, t)=split(x->r, key), mp(renew(x),t));
}
ptr merge(ptr x, ptr y) {
    if (x == nil) return y; if (y == nil) return x;
    return x->fit < y->fit // rand() % (X.sz+Y.sz) < X.sz
        ? (x = down(x), x->r = merge(x->r, y), renew(x))
        : (y = down(y), y->l = merge(x, y->l), renew(y));
}
