/* 
 * Palindrome Automaton - pointer version
 * PAMPAMPAM? PAMPAMPAM!
 */

namespace PAM {
	struct Node *pool_pointer;
	struct Node {
		Node *fail, *to[26];
		int cnt, len;
		
		Node() {}
		Node(int len): len(len) {
			memset(to, 0, sizeof(to));
			fail = 0;
			cnt = 0;
		}
		
		void *operator new (size_t) {
			return pool_pointer++;
		}
	} pool[100005], *root[2], *last;
	int pam_len, str[100005];
	
	void init() {
		pool_pointer = pool;
		root[0] = new Node(0);
		root[1] = new Node(-1);
		root[0]->fail = root[1]->fail = root[1];
		str[pam_len = 0] = -1; // different from all characters 
		last = root[0];
	}
	
	void extend(char ch) {
		static Node *p, *np, *q;
		
		int x = str[++pam_len] = ch - 'a';
		
		p = last;
		while (str[pam_len - p->len - 1] != x)
			p = p->fail;
		if (!p->to[x]) {
			np = new Node(p->len + 2), q = p->fail;
			while (str[pam_len - q->len - 1] != x) q = q->fail;
			np->fail = q->to[x] ? q->to[x] : root[0];
			p->to[x] = np;
		}
		last = p->to[x];
		++last->cnt;
	}
}
