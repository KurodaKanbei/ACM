struct Node{
	int mn, key, size, tag;
	bool rev;
	Node* ch[2];
	Node(int mn, int key, int size): mn(mn), key(key), size(size), rev(0), tag(0){}
	void downtag();
	Node* update(){
		mn = min(ch[0] -> mn, min(key, ch[1] -> mn));
		size = ch[0] -> size + 1 + ch[1] -> size;
		return this;
	}
};
typedef pair<Node*, Node*> Pair;
Node *null, *root;
void Node::downtag(){
	if(rev){
		for(int i = 0; i < 2; i++)
			if(ch[i] != null){
				ch[i] -> rev ^= 1;
				swap(ch[i] -> ch[0], ch[i] -> ch[1]);
			}
		rev = 0;
	}
	if(tag){
		for(int i = 0; i < 2; i++)
			if(ch[i] != null){
				ch[i] -> key += tag;
				ch[i] -> mn += tag;
				ch[i] -> tag += tag;
			}
		tag = 0;
	}
}
int r(){
	static int s = 3023192386;
	return (s += (s << 3) + 1) & (~0u >> 1);
}
bool random(int x, int y){
	return r() % (x + y) < x;
}
Node* merge(Node *p, Node *q){
	if(p == null) return q;
	if(q == null) return p;
	p -> downtag();
	q -> downtag();
	if(random(p -> size, q -> size)){
		p -> ch[1] = merge(p -> ch[1], q);
		return p -> update();
	}else{
		q -> ch[0] = merge(p, q -> ch[0]);
		return q -> update();
	}
}
Pair split(Node *x, int n){
	if(x == null) return make_pair(null, null);
	x -> downtag();
	if(n <= x -> ch[0] -> size){
		Pair ret = split(x -> ch[0], n);
		x -> ch[0] = ret.second;
		return make_pair(ret.first, x -> update());
	}
	Pair ret = split(x -> ch[1], n - x -> ch[0] -> size - 1);
	x -> ch[1] = ret.first;
	return make_pair(x -> update(), ret.second);
}
pair<Node*, Pair> get_segment(int l, int r){
	Pair ret = split(root, l - 1);
	return make_pair(ret.first, split(ret.second, r - l + 1));
}
int main(){
	null = new Node(INF, INF, 0);
	null -> ch[0] = null -> ch[1] = null;
	root = null;
}
