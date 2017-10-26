struct node { node *ch[C], *fail; int cnt;
    node() { memset(ch, NULL, sizeof(ch));
            fail = NULL; cnt = 0; }
} pol[N], *tot = pol, *root;
node* newnode() { *tot = node(); return tot ++; }
void insert(char *t) {
    int n = strlen(t); node *p = root;
    for (int i = 0; i < n; ++ i) {
        int v = val(t[i]);
        if (!p->ch[v]) p->ch[v] = newnode();
        p = p->ch[v]; } p->cnt ++;
}
void BFS() {
    root->fail = root; queue<node*> q;
    q.push(root->fail = root);
    while (!q.empty()) {
        node* x = q.front(); q.pop();
        for (int i = 0; i < C; ++ i) if (x->ch[i]) {
            node *&y = x -> ch[i];
            y->fail = x == root ? root : x->fail->ch[i];
            y->cnt += x->ch[i]->fail->cnt; // 视情况
            q.push(y);
        } else x->ch[i]= x==root?root : x->fail->ch[i];
    }
} // root = newnode();