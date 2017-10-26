#define nil mem
struct Node { Node *l, *r; int dist; Val val; }
    mem[mxv] = {{nil, nil, -1}}; int sz = 0;
#define NEW(arg...) (new(mem + ++sz)Node{nil,nil,0,arg})
//add(x,ope){if(x!=nil){x->val+=ope,x->laz+=ope;}}
//down(x) { if(x->laz) { add(x->l,x->laz);
//              add(x->r,x->laz);x->laz=0;} }
Node *merge(Node *x, Node *y) {
    if (x == nil) return y;
    if (y == nil) return x;
    if (y->val < x->val) swap(x, y); // 默认小根堆
    // down(x); // 朱刘算法下传标记预留位置
    x->r = merge(x->r, y);
    if (x->l->dist < x->r->dist) swap(x->l, x->r);
    x->dist = x->r->dist + 1;
    return x; }
Node *pop(Node *x) {/*down(x);*/return merge(x->l,x->r);}