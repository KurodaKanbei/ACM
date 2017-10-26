namespace splay {
struct Node {
	Node *child[2], *father; int val, sum, size;
	inline Node() { val = sum = size = 0; }
	inline int which() { return father->child[1] == this; }
	inline void set(Node *temp, int dir) {
		child[dir] = temp; temp->father = this;
	}
	inline void update() {
		size = 1 + child[0]->size + child[1]->size;
		sum = val + child[0]->sum + child[1]->sum;
	}
	inline void release() {}
};
Node *null, *head;
inline void print(Node *root) {
	if (root == null) return; print(root->child[0]); printf("%d ", root->val);
	print(root->child[1]);
}
inline Node* create(int val = 0) {
	Node *temp = new Node(); temp->val = val;
	temp->child[0] = temp->child[1] = temp->father = null; return temp;
}
inline void rotate(Node *root) {
	Node *father = root->father; int dir = root->which(); father->release();
	root->release; father->set(root->child[!dir], dir);
	father->father->set(root, father->which()); root->set(father, !dir);
	if (father == head) head = root;
	father->update();
}
inline void splay(Node *root, Node *target) {
	for (root->release(); root->father != target; )
		if (root->father->father == target) rotate(root);
		else root->which() == root->father->which() ? (rotate(root->father), rotate(root)) : (rotate(root), rotate(root));
	root->update();
}
inline int rank(Node *root) {
	splay(root, null); return root->child[0]->size + 1;
}
inline Node* find(int rank) {
	Node *now = head;
	for (; now->child[0]->size + 1 != rank; ) {
		now->release();
		if (now->child[0]->size + 1 > rank) now = now->child[0];
		else { rank -= now->child[0]->size + 1; now = now->child[1]; }
	} return now;
}
inline void splay(int left, int right) {
	splay(find(right), null); splay(find(left), head);
}
inline Node* insert(int pos, int val) {
	splay(pos, pos + 1); Node *now = head->child[0]; Node *cur = create(val);
	now->set(cur, 1); splay(cur, null); return head;
}
inline void insert(int pos, int n, int val[]) {
	splay(pos, pos + 1); Node *now = head->child[0];
	for (int i = 1; i <= n; ++i) {
		Node *cur = create(val[i]); now->set(cur, 1); now = cur;
	} splay(now, null);
}
inline void erase(Node *root) {
	int pos = rank(root); splay(pos - 1, pos + 1);
	head->child[0]->child[1] = null; head->child[0]->update(); head->update();
}
inline int query(int left, int right) {
	splay(left - 1, right + 1); return head->child[0]->child[1]->sum;
}
inline void prepare() {
	null = new Node(); head = create(); Node *tail = create();
	head->set(tail, 1); splay(tail, null);
}