bool ena[mxn]; int s[mxn]; // s[x] 是子树 x 的大小
#define fore(i) for (auto i : G[x]) if (!ena[i])
#define fors(i) fore(i) if (i != p)
int size(int x, int p)
{ s[x] = 1; fors(i) s[x] += size(i, x); return s[x]; }
pii core(int x, int p, int sx, vi &st) {
    st.push_back(x); fors(i) if (sx - s[i] < s[i])
        return core(i, x, sx, st); return {x, p}; }
void divide(int y) {
    vi path; int x, yi; tie(x,yi)=core(y,0,s[y],path);
    path.pop_back(); for (int i : path) s[i] -= s[x];
    ena[x] = true; if (x != y) divide(y); // work(yi)
    for (int j : path); // ... // 从 y 到 x 收集 dp 值
    ... // 更新 x 的 dp 值并收集 更新注意复杂度 
    fore(i) if (i != yi) work(i); // 更新 i 子树 ( 二分 )
    fore(i) if (i != yi) divide(i); ena[x] = false;
}
