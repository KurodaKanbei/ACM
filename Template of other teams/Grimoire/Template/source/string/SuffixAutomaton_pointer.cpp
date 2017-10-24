/* 
 * Suffix Automaton - pointer version
 * SAMSAMSAM? SAMSAMSAM!
 */

namespace SAM {
	struct Node *pool_pointer;
	struct Node {
		Node *to[26], *parent;
		int step;
		
		Node(int STEP = 0): step(STEP) {
			memset(to, 0, sizeof to);
			parent = 0;
			step = 0;
		}
		
		void *operator new (size_t) {
			return pool_pointer++;
		}
	} pool[100005 << 1], *root, *np;
	int sam_len;
	
	void init() {
		pool_pointer = pool;
		root = np = new Node(sam_len = 0);
	}
	
	void extend(char ch) {
		static Node *last, *q, *nq;
		
		int x = ch - 'a';
		last = np; np = new Node(++sam_len);
		for (; last && !last->to[x]; last = last->parent)
			last->to[x] = np;
		if (!last) np->parent = root;
		else {
			q = last->to[x];
			if (q->step == last->step + 1) np->parent = q;
			else {
				nq = new Node(*q);
				nq->step = last->step + 1;
				q->parent = np->parent = nq;
				for (; last && last->to[x] == q; last = last->parent)
					last->to[x] = nq;
			}
		}
	}
}
