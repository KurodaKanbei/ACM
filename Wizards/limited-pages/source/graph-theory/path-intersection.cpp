bool cmp(int x,int y) {
	return dep[x] > dep[y];
}
std::pair<int,int> path_intersection(int a,int b,int c,int d) {
	std::vector<int> poi;
	poi.push_back(getlca(a, c));
	poi.push_back(getlca(a, d));
	poi.push_back(getlca(b, c));
	poi.push_back(getlca(b, d));
	std::sort(poi.begin(), poi.end(), cmp);
	return std::make_pair(poi[0], poi[1]);
}
