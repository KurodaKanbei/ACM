// 点集并的直径端点 $\subset$ 每个点集直径端点的并
// 可以用 dfs 序的 ST 表维护子树直径，建议使用 RMQLCA
void make(vi &poi) {
    //poi 要按 dfn 排序 需要清空边表 E 注意 V 无序
    //0 号点相当于一个虚拟的根，需要 lca(u,0)==0,h[0]=0
    V = {0}; vi st = {0};
    for (int v : poi) {
        V.pb(v);int w=lca(st.back(),v), sz=st.size();
        while (sz > 1 && h[st[sz - 2]] >= h[w])
            E[st[sz - 2]].pb(st[sz - 1]), sz --;
        st.resize(sz);
        if (st[sz - 1] != w)
            E[w].pb(st.back()), st.back() = w, V.pb(w);
        st.pb(v);
    }
    for (int i=1; i<st.size(); ++i) E[st[i-1]].pb(st[i]);
}
