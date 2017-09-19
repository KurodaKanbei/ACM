const bool BCC_VERTEX = 0, BCC_EDGE = 1;
struct BCC {  // N = N0 + M0. Remember to call init(&raw_graph).
	Graph *g, forest; // g is raw graph ptr.
	int dfn[N], DFN, low[N];
	int stack[N], top;
	int expand_to[N];  	// Where edge i is expanded to in expaned graph.
	// Vertex i expaned to i.
	int compress_to[N];  // Where vertex i is compressed to.
	bool vertex_type[N], cut[N], compress_cut[N], branch[M];
	//std::vector<int> BCC_component[N];  // Cut vertex belongs to none.
	__inline void init(Graph *raw_graph) {
		g = raw_graph;
	}
	void DFS(int u, int pe) {
		dfn[u] = low[u] = ++DFN; cut[u] = false;
		if (!~g->adj[u]) {
			cut[u] = 1; 
			compress_to[u] = forest.new_node();
			compress_cut[compress_to[u]] = 1;
		}
		for (int e = g->adj[u]; ~e; e = g->nxt[e]) {
			int v = g->v[e]; 
			if ((e ^ pe) > 1 && dfn[v] > 0 && dfn[v] < dfn[u]) {
				stack[top++] = e;
				low[u] = std::min(low[u], dfn[v]);
			}
			else if (!dfn[v]) {
				stack[top++] = e; branch[e] = 1;
				DFS(v, e);
				low[u] = std::min(low[v], low[u]);
				if (low[v] >= dfn[u]) {
					if (!cut[u]) {
						cut[u] = 1;
						compress_to[u] = forest.new_node();
						compress_cut[compress_to[u]] = 1;
					}
					int cc = forest.new_node();
					forest.bi_ins(compress_to[u], cc);
					compress_cut[cc] = 0;
					//BCC_component[cc].clear();
					do {
						int cur_e = stack[--top];
						compress_to[expand_to[cur_e]] = cc;
						compress_to[expand_to[cur_e^1]] = cc;
						if (branch[cur_e]) {
							int v = g->v[cur_e];
							if (cut[v]) 
								forest.bi_ins(cc, compress_to[v]);
							else {
								//BCC_component[cc].push_back(v);
								compress_to[v] = cc;
							}
						}
					} while (stack[top] != e);
				}
			}
		}
	}
	void solve() {
		forest.init(g->base);
		int n = g->n;
		for (int i = 0; i < g->e; i++) {
			expand_to[i] = g->new_node();
		}
		memset(branch, 0, sizeof(*branch) * g->e);
		memset(dfn + g->base, 0, sizeof(*dfn) * n); DFN = 0;
		for (int i = 0; i < n; i++)
			if (!dfn[i + g->base]) {
				top = 0;
				DFS(i + g->base, -1);
			}
	}
} bcc;

bcc.init(&raw_graph);
bcc.solve();
// Do something with bcc.forest ...
