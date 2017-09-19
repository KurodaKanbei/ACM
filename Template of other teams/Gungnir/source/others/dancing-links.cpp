struct Node {
	Node *l, *r, *u, *d, *col;
	int size, line_no;
	Node() {
		size = 0; line_no = -1;
		l = r = u = d = col = NULL;
	}
} *root;

void cover(Node *c) {
	c->l->r = c->r; c->r->l = c->l;
	for (Node *u = c->d; u != c; u = u->d)
		for (Node *v = u->r; v != u; v = v->r) {
			v->d->u = v->u;
			v->u->d = v->d;
			-- v->col->size;
		}
}

void uncover(Node *c) {
	for (Node *u = c->u; u != c; u = u->u) {
		for (Node *v = u->l; v != u; v = v->l) {
			++ v->col->size;
			v->u->d = v;
			v->d->u = v;
		}
	}
	c->l->r = c; c->r->l = c;
}

std::vector<int> answer;
bool search(int k) {
	if (root->r == root) return true;
	Node *r = NULL;
	for (Node *u = root->r; u != root; u = u->r)
		if (r == NULL || u->size < r->size)
			r = u;
	if (r == NULL || r->size == 0) return false;
	else {
		cover(r);
		bool succ = false;
		for (Node *u = r->d; u != r && !succ; u = u->d) {
			answer.push_back(u->line_no);
			for (Node *v = u->r; v != u; v = v->r)  // Cover row
				cover(v->col);
			succ |= search(k + 1);
			for (Node *v = u->l; v != u; v = v->l)
				uncover(v->col);
			if (!succ) answer.pop_back();
		}
		uncover(r);
		return succ;
	}
}

bool entry[CR][CC];
Node *who[CR][CC];
int cr, cc;

void construct() {
	root = new Node();
	Node *last = root;
	for (int i = 0; i < cc; ++ i) {
		Node *u = new Node();
		last->r = u; u->l = last;
		Node *v = u; u->line_no = i;
		last = u;
		for (int j = 0; j < cr; ++ j)
			if (entry[j][i]) {
				++ u->size;
				Node *cur = new Node();
				who[j][i] = cur;
				cur->line_no = j;
				cur->col = u;
				cur->u = v; v->d = cur;
				v = cur;
			}
		v->d = u; u->u = v;
	}
	last->r = root; root->l = last;
	for (int j = 0; j < cr; ++ j) {
		Node *last = NULL;
		for (int i = cc - 1; i >= 0; -- i)
			if (entry[j][i]) {
				last = who[j][i];
				break;
			}
		for (int i = 0; i < cc; ++ i)
			if (entry[j][i]) {
				last->r = who[j][i];
				who[j][i]->l = last;
				last = who[j][i];
			}
	}
}

void destruct() {
	for (Node *u = root->r; u != root; ) {
		for (Node *v = u->d; v != u; ) {
			Node *nxt = v->d;
			delete(v);
			v = nxt;
		}
		Node *nxt = u->r;
		delete(u); u = nxt;
	}
	delete root;
}
