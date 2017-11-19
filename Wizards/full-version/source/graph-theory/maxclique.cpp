const int N = 1000 + 7;
vector<vector<bool> > adj;
class MaxClique {
    const vector<vector<bool> > adj;
    const int n;
    vector<int> result, cur_res;
    vector<vector<int> > color_set;
    const double t_limit; // MAGIC
	int para, level;
	vector<pair<int, int> > steps;
public:
    class Vertex {
    public:
        int i, d;
        Vertex(int i, int d = 0) : i(i), d(d) {}
    };
    void reorder(vector<Vertex> &p) {
        for (auto &u : p) {
            u.d = 0;
            for (auto v : p) u.d += adj[v.i][u.i];
        }
        sort(p.begin(), p.end(), [&](const Vertex &a, const Vertex &b) { return a.d > b.d; } );
    }
	// reuse p[i].d to denote the maximum possible clique for first i vertices.
    void init_color(vector<Vertex> &p) {
        int maxd = p[0].d;
        for (int i = 0; i < p.size(); i++) p[i].d = min(i, maxd) + 1;
    }
    bool bridge(const vector<int> &s, int x) {
        for (auto v : s) if (adj[v][x]) return true;
        return false;
    }
	// approximate estimate the p[i].d
	// Do not care about first mink color class (For better result, we must get some vertex in some color class larger than mink )
    void color_sort(vector<Vertex> &cur) {
        int totc = 0, ptr = 0, mink = max((int)result.size() - (int)cur_res.size(), 0);
        for (int i = 0; i < cur.size(); i++) {
            int x = cur[i].i, k = 0;
            while (k < totc && bridge(color_set[k], x)) k++;
            if (k == totc) color_set[totc++].clear();
            color_set[k].push_back(x);
            if (k < mink) cur[ptr++].i = x;
        }
        if (ptr) cur[ptr - 1].d = 0;
        for (int i = mink; i < totc; i ++) {
            for (auto v : color_set[i]) {
                cur[ptr++] = Vertex(v, i + 1);
            }
        }
    }
    void expand(vector<Vertex> &cur) {
		steps[level].second = steps[level].second - steps[level].first + steps[level - 1].first;
		steps[level].first = steps[level - 1].second;
        while (cur.size()) {
            if (cur_res.size() + cur.back().d <= result.size()) return ;
            int x = cur.back().i;
            cur_res.push_back(x); cur.pop_back();
            vector<Vertex> remain;
            for (auto v : cur) {
                if (adj[v.i][x]) remain.push_back(v.i);
            }
            if (remain.size() == 0) {
                if (cur_res.size() > result.size()) result = cur_res;
            } else {
				// Magic ballance.
				if (1. * steps[level].second / ++para < t_limit) reorder(remain);
                color_sort(remain);
				steps[level++].second++;
                expand(remain);
				level--;
            }
            cur_res.pop_back();
        }
    }
public:
    MaxClique(const vector<vector<bool> > &_adj, int n, double tt = 0.025) : adj(_adj), n(n), t_limit(tt) {
        result.clear();
        cur_res.clear();
        color_set.resize(n);
		steps.resize(n + 1);
		fill(steps.begin(), steps.end(), make_pair(0, 0));
		level = 1;
		para = 0;
    }
    vector<int> solve() {
        vector<Vertex> p;
        for (int i = 0; i < n; i++) p.push_back(Vertex(i));
        reorder(p);
        init_color(p);
        expand(p);
        return result;
    }
};
