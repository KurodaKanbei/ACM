// spoj 1811
#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

const int oo = 1 << 25;
const int ALPHABET_SIZE = 26;
const int N = 250000 + 7;
const int DEBUG = 0;

using namespace std;

// 末尾需要一个特别字符

class SuffixTree {
public:
	struct Node {
		int start, end, length;
		Node *slink, *father;
		Node* next[ALPHABET_SIZE];
		Node(int start = -1, int end = oo) : start(start), end(end) {
			slink = father = NULL;
			length = 0;
			for (int i = 0; i < ALPHABET_SIZE; i++) {
				next[i] = NULL;
			}
		}
		int len2(int pos) {
			return min(end, pos) - start;
		}
		__inline int len() {
			return end - start;
		}
	};

	Node *cur;
	int cur_len, cur_p;
	Node pool[N << 1];
	Node *root, *needSL;
	int total, pos, remaind;
	int text[N];
	vector<Node* > leaves;

	bool walk_down(Node *x) {
		if (cur_len >= x->len()) {
			cur_p += x->len();
			cur_len -= x->len();
			cur = x;
			return true;
		}
		return false;
	}
	Node* new_node(int start, int end = oo) {
		return new(pool + total++) Node(start, end);
	}
	void add_SL(Node* x) {
		if (needSL != NULL) needSL->slink = x;
		needSL = x;
	}
	void init() {
		needSL = NULL, total = 0, pos = 0,
		remaind = 0;
		root = cur = new_node(-1, -1);
		root->slink = root;
		cur_p = cur_len = 0;
		leaves.clear();
	}
	Node* set_next(Node* a, Node* b) {
		a->next[text[b->start]] = b;
		b->father = a;
		b->length = a->length + a->len();
		return b;
	}
	Node* split(Node *nxt, int len) {
		if (nxt->len2(pos) == len) return nxt;
		if (len == 0) return nxt->father;
		Node* branch = new_node(nxt->start, nxt->start + len);
		set_next(nxt->father, branch);
		nxt->start += len;
		set_next(branch, nxt);
		return branch;
	}
	void extend(int c) {
		text[pos++] = c;
		needSL = NULL;
		remaind++;
		while (remaind > 0) {
			int cur_e = text[cur_p = cur_len ? cur_p : pos - 1];
			Node* nxt = cur->next[cur_e];
			if (nxt == NULL) {
				Node* leaf = new_node(pos - 1);
				leaves.push_back(set_next(cur, leaf));
				add_SL(cur); //rule 2
			} else {
				if (walk_down(nxt)) continue; //observation 2
				if (text[nxt->start + cur_len] == c) { //observation 1
					cur_len++;
					add_SL(cur); //observation 3
					break;
				}
				Node* branch = split(nxt, cur_len); //new_node(nxt->start, nxt->start + cur_len);
				Node* leaf = new_node(pos - 1);
				leaves.push_back(set_next(branch, leaf));
				add_SL(branch); //rule 2
			}
			remaind--;
			if (cur == root && cur_len > 0) { //rule 1
				cur_len--;
				cur_p = pos - remaind;
			} else {
				cur = cur->slink ? cur->slink : root; //rule 3
			}
		}
	}
};

SuffixTree st;
char text[N];

int main() {
	st.init();
	scanf("%s", text);
	for (int i = 0; text[i]; i++) st.extend(text[i] - 'a');
	scanf("%s", text);
	SuffixTree::Node *cur = st.root;
	int answer = 0;
	for (int i = 0, cur_e = 0, cur_len = 0, cnt = 0; text[i]; i++) {
		int idx = text[i] - 'a';
		while (cnt) {
			if (cur_len > 0) {
				int e_id = text[cur_e] - 'a';
				SuffixTree::Node *x = cur->next[e_id];
				if (cur_len >= x->len()) {
					cur_e += x->len();
					cur_len -= x->len();
					cur = x;
					continue;
				}
				if (x->start + cur_len < st.pos && st.text[x->start + cur_len] == idx) break;
			} else {
				if (cur->next[idx] != NULL) break;
			}
			cnt--;
			if (cur == st.root && cur_len > 0) {
				cur_len--;
				cur_e = i - 1 - cnt + 1;
			} else {
				cur = cur->slink != NULL ? cur->slink : st.root;
			}
		}
		if (cnt == 0 && cur->next[idx] == NULL) continue;
		cnt++;
		if (cur_len == 0) cur_e = i;
		cur_len++;
		answer = max(answer, cnt);
	}
	printf("%d\n", answer);
	return 0;
}
