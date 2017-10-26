// 如果不是历史版本的合并, 可以每个点一开始取一个随机值, 按照堆的规则合并
struct node {
	int size;
	node *left, *right;
	inline node(node *_left, node *_right) {
		left = _left; right = _right;
		size = 0;
	}
	inline node* update() {
		size = left -> size + 1 + right -> size;
		return this;
	}
	inline pair<node*, node*> split(int);
};
node* null; //use NULL when persistent!
inline bool random(int x, int y) {return rand() % (x + y) < x;}
inline node* mergy(node* x, node* y) {
	if (x == null) return y;
	if (y == null) return x;
	if (random(x -> size, y -> size)) {
		//x push_down
		x -> right = mergy(x -> right, y);
		return x -> update();
		//new node & update when persistent
	}
	//y push_down
	y -> left = mergy(x, y -> left);
	return y -> update();
	//new node & update when persistent
}
inline pair<node*, node*> node::split(int n) {
	if (this == null) return make_pair(null, null);
	//push_down
	//copy myself
	if (n <= left -> size) {
		pair<node*, node*> ret = left -> split(n);
		left = null;
		return make_pair(ret.first, mergy(ret.second, this -> update()));
	}
	pair<node*, node*> ret = right -> split(n -left -> size - 1);
	right = null;
	return make_pair(mergy(this -> update(), ret.first), ret.second);
}
inline void prepare() {
	//don't use null when persistent
	null = new node(null, null);
	null -> left = null -> right = null;
}
