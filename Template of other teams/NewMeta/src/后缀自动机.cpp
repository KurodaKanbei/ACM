struct State {
    int len;
    State * parent, * go[2];
    State(int len = 0) : len(len), parent(NULL) {
        memset(go, 0, sizeof(go));
    }
    State * extend(State * , int token);
} node_pool[N * 2], *tot_node, *null = new State();
State * State::extend(State * start, int token) {
    State * p = this;
    State * np = this->go[token] ? null : new (tot_node++) State(this->len + 1);
    while(p && !p->go[token])
        p->go[token] = np, p = p->parent;
    if(!p) np->parent = start;
    else {
        State * q = p->go[token];
        State * bak(p);
        if(p->len + 1 == q->len) {
            np->parent = q;
        } else {
            State * nq = new (tot_node++) State(*q);
            nq->len = p->len + 1;
            np->parent = q->parent = nq;
            while(p && p->go[token] == q) {
                p->go[token] = nq, p = p->parent;
            }
        }
    }
    return np == null ? np->parent : np;
}
void prepare() {
	tot_node = node_pool;
	head = tail = new(tot_node++) State();
	tail = tail->extend(head, token);  // to add one token
}
