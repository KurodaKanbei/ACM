void build(int *l, int *r) { // 左闭右开
	auto t = r - 1; if (l >= t) return;
	random_shuffle(l, r);
	G.reset(); // 重置流量
	add2(*l, *t, G.dinic(*l, *t)); // 添加树边
	fill(G.v, G.v + G.n + 1, false); G.dfscut(*l); // 求割集
	auto m = partition(l, r, [](int x){return G.v[x];});
	build(l, m); build(m, r);
}
