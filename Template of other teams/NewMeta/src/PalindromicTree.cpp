struct node {
	node *child[26], *fail;
	int length; //cnt
	node(int length) : fail(NULL), length(length) {memset(child, NULL, sizeof(child));}
};
int size, text[N];
node *odd, *even;
node *match(node *now) {
	for (; text[size - now->length - 1] != text[size]; now = now->fail);
	return now;
}
bool extend(node *&last, int token) {
	text[++ size] = token;
	node *now = last;
	now = match(now);
	if (now->child[token]) {
		last = now->child[token];
		return false;
	}
	last = now->child[token] = new node(now->length + 2);
	if (now == odd) last->fail = even;
	else {
		now = match(now->fail);
		last->fail = now->child[token];
	}
	//last -> cnt ++;
	return true;
}
void build() {
	text[size = 0] = -1;
	even = new node(0), odd = new node(-1);
	even->fail = odd;
}
// for in reversed ordered : x -> fail -> cnt += x -> cnt
