bool dfs(int i) {
    path[len++] = i;
    if (v[i]) return true;
    v[i] = true;
    for (int j = 0; j < k; ++j) {
        if (i != j && match[i] != j && !v[j]) {
            int kok = match[j];
            if (d[kok] < d[i] + w[i][j] - w[j][kok]) {
                d[kok] = d[i] + w[i][j] - w[j][kok];
                if (dfs(kok)) return true;
            }
        }
    }
    --len; v[i] = false;
    return false;
}
void solve() {
    for (int i = 0; i < k; ++i) p[i] = i, match[i] = i ^ 1;
    int cnt = 0;
    for (;;) {
        len = 0;
        bool flag = false;
        memset(d, 0, sizeof(d));
        memset(v, 0, sizeof(v));
        for (int i = 0; i < k; ++i) {
            if (dfs(p[i])) {
                flag = true;
                int t = match[path[len - 1]], j = len - 2;
                while (path[j] != path[len - 1]) {
                    match[t] = path[j];
                    swap(t, match[path[j]]);
                    --j;
                }
                match[t] = path[j];
                match[path[j]] = t;
                break;
            }
        }
        if (!flag) {
            if (++cnt >= 3) break;
            random_shuffle(p, p+k);
        }
    }
}
