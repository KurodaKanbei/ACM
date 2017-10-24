/* 
 * Suffix Automaton - array version
 * SAMSAMSAM? SAMSAMSAM!
 */

namespace SAM {
	int to[100005 << 1][26], parent[100005 << 1], step[100005 << 1], tot;
	int root, np;
	int sam_len;
	
	int newnode(int STEP = 0) {
		++tot;
		memset(to[tot], 0, sizeof to[tot]);
		parent[tot] = 0;
		step[tot] = STEP;
		return tot;
	}
	
	void init() {
		tot = 0;
		root = np = newnode(sam_len = 0);
	}
	
	void extend(char ch) {
		int x = ch - 'a';
		int last = np; np = newnode(++sam_len);
		for (; last && !to[last][x]; last = parent[last])
			to[last][x] = np;
		if (!last) parent[np] = root;
		else {
			int q = to[last][x];
			if (step[q] == step[last] + 1) parent[np] = q;
			else {
				nq = newnode(step[last] + 1);
				memcpy(to[nq], to[q], sizeof to[q]);
				parent[nq] = parent[q];
				parent[q] = parent[np] = nq;
				for (; last && to[last][x] == q; last = parent[last])
					to[last][x] = nq;
			}
		}
	}
}
