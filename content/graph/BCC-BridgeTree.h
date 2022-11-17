/**
 * Author: Cube219
 * Date: 2022-07-22
 * Description: Create a tree that combine vertexs with same bcc
 * based on bridges.
 */
#pragma once

vector<int> par(n);
iota(par.begin(), par.end(), 0);
auto find = [&](int x) {
	while(x != par[x]) x = par[x] = par[par[x]];
	return x;
};
auto uni = [&](int a, int b) {
	a = find(a); b = find(b);
	if(a == b) return;
	par[b] = a;
};
for(auto& bcc : bccs) {
	if(bcc.size() == 1) continue;
	for(auto [u, v] : bcc) uni(u, v);
}
vector<vector<int>> g2(n);
for(auto& bcc : bccs) {
	if(bcc.size() != 1) continue;
	auto [u, v] = bcc[0];
	u = find(u); v = find(v);

	g[u].push_back(v);
	g[v].push_back(u);
}
