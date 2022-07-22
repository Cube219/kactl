/**
 * Author: Cube219
 * Date: 2022-07-22
 * Description: Calculates shortest paths from $st$ in a graph that might have negative edge weights.
 *  Return empty vector if the graph has a negative cycle.
 */
#pragma once

auto spfa = [&](int st) -> vector<ll> {
	vector<ll> dst(n, LNF), cycle(n, 0);
	vector<char> inq(n, false);

	queue<int> q;
	q.push(st);
	dst[st] = 0;
	while(!q.empty()) {
		int cur = q.front(); q.pop(); inq[cur] = false;

		for(auto [nxt, cost] : g[cur]) {
			if(dst[nxt] > dst[cur] + cost) {
				dst[nxt] = dst[cur] + cost;
				if(!inq[nxt]) {
					q.push(nxt);
					inq[nxt] = true;
				}
				cycle[nxt]++;
				if(cycle[nxt] > n) return {};
			}
		}
	}
	return dst;
};
