struct Node { // 注意初始化内存池和 null 节点
    int size; Node *ch[2],*p; Key key; Val val,sum,lazy;
    int dir(); void set(Node*,int); void update();
    void relax(); void app(Val);
} nodePool[MAX_NODE],*curNod,*null;
Node *newNode(Key k, Val v) { Node *t=curNod++;t->lazy=0;
    t->size=1; t->key=k; t->ch[0]=t->ch[1]=t->p=null;
    t->sum=t->val=v; return t; }
struct Splay {
    Node *root;Splay(){root=newNode(INF,0); // 有两个哨兵
        root->set(newNode(-INF,0),0); root->update(); }
    void rot(Node *t) {
        Node *p=t->p;int d=t->dir();p->relax();t->relax();
        if(p==root) root=t; p->set(t->ch[!d],d);
        p->p->set(t,p->dir()); t->set(p,!d); p->update();}
    void splay(Node *t,Node *f=null) {
        for(t->relax();t->p!=f;) if(t->p->p==f) rot(t);
            else t->dir()==t->p->dir()?
                (rot(t->p),rot(t)):(rot(t),rot(t));
        t->update(); }
    Node* lower_bound(Key k) {
        Node *p=root, *res=null;
        while (p != null) {p->relax(); int d=p->key < k;
            if (!d) res = p; p=p->ch[d]; } return res;
    }
    Node* getpre(Node *x) { // x 会变成根
        splay(x); x=x->ch[0];
        while (x->relax(), x->ch[1]!=null) x=x->ch[1];
        return x; }
    Node* insert(Key k, Val v) { // 需要保证无重复 key
        Node *p=lower_bound(k); p=getpre(p); Node *t;
        p->set(t=newNode(k, v), 1); splay(p->ch[1]);
        return t; }
    void erase(Node* x) {
        splay(getpre(x), x); x->ch[0]->set(x->ch[1],1);
        (root=x->ch[0])->p=null; root->update();// 未回收
    }
    Node* kth(int k) { // 1 base
        Node *p = root; k ++; // 加上左哨兵大小 1
        while (p != null) { int ls=p->ch[0]->size;
            if (ls + 1 == k) return p; int d = ls < k;
            k -= d * (ls + 1); p=p->ch[d]; } return null;
    }
    Node *pick_by_key(Key l, Key r) { // 左闭右开
        Node *L=getpre(lower_bound(l)), *R=lower_bound(r);
        splay(R); splay(L, R); return L->ch[1];
    }
    Node *pick_by_index(int l, int r) { // 左闭右开
        Node *L=kth(l-1), *R=kth(r);
        splay(R); splay(L, R); return L->ch[1];
    }
};
void initNu(){curNod=nodePool;null=curNod++;null->size=0;}
void Node::set(Node *t,int _d){ ch[_d]=t; t->p=this; }
int Node::dir(){ return this==p->ch[1]; }
void Node::update(){ size=ch[0]->size+ch[1]->size+1;
    sum=ch[0]->sum + ch[1]->sum + val; }
void Node::relax(){
    if(lazy) ch[0]->app(lazy), ch[1]->app(lazy), lazy=0;}
void Node::app(Val c){
    if(this==null) return; lazy+=c; val+=c; sum+=c*size;}
int main() { curNod = nodePool; initNu(); }