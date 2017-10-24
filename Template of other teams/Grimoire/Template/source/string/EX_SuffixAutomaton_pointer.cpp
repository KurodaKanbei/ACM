/* 
 * EX Suffix Automaton - pointer version
 * SAMSAMSAM? SAMSAMSAM!
 */

namespace SAM {
	struct Node *pool_pointer;
	struct Node {
		Node *parent, *to[26];
		int step;
		
		Node(int step = 0): step(step) {
			memset(to, 0, sizeof to);
			parent = 0;
		}
		
		void *operator new (size_t) {
			return pool_pointer++;
		}
	} pool[100005 * 10 << 1], *root, *np;
	int sam_len, now_len;
	
	void init() {
		sam_len = now_len = 0;
		pool_pointer = pool;
		root = new Node();
	}
	
	void new_str() { // a new string start
		now_len = 0;
		np = root;
	}
	
	void extend(char ch) {
		static Node *last, *q, *nq;
		
		int x = ch - 'a';
		if (np->to[x]) {
			np = np->to[x];
			++now_len;
		}
		else {
			last = np; np = new Node(++now_len);
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
		
		sam_len = std::max(sam_len, now_len);
	}
}
