/**
 * Author: shjohw12
 * Date: 2022-07-22
 * Description: Dinic algorithm
 */
#pragma once

struct Dinic {
	struct Edge {
		ll par, nxt, cap, flow;
		Edge(ll par, ll nxt, ll cap) :par(par), nxt(nxt), cap(cap), flow(0) {}
	};
	ll n, src, sink;
	vector<ll> st, cur, lv;
	vector<Edge> edge;
	Dinic(ll n) :n(n), src(n + 1), sink(n + 2), st(n + 5, -1) {}
	void addEdge(ll a, ll b, ll cap) {
		edge.emplace_back(st[a], b, cap);
		st[a] = edge.size() - 1;
		edge.emplace_back(st[b], a, 0);
		st[b] = edge.size() - 1;
	}
	bool bfs() {
		lv = vector<ll>(n + 5);
		lv[src] = 1;
		queue<ll> q;
		q.push(src);
		while(!q.empty()) {
			ll idx = q.front();
			q.pop();
			for(ll i = st[idx]; i != -1; i = edge[i].par) {
				Edge& e = edge[i];
				if(!lv[e.nxt] && e.flow < e.cap) {
					lv[e.nxt] = lv[idx] + 1;
					q.push(e.nxt);
				}
			}
		}
		return lv[sink];
	}
	ll dfs(ll idx, ll flow) {
		if(idx == sink) return flow;
		for(ll& i = cur[idx]; i != -1; i = edge[i].par) {
			Edge& e = edge[i];
			if(e.flow < e.cap && lv[e.nxt] == lv[idx] + 1) {
				ll tmp = dfs(e.nxt, min(flow, e.cap - e.flow));
				if(tmp) {
					e.flow += tmp;
					edge[i ^ 1].flow -= tmp;
					return tmp;
				}
			}
		}
		return 0;
	}
	ll solve() {
		ll ret = 0;
		while(bfs()) {
			cur = st;
			ll tmp;
			while(tmp = dfs(src, INF)) ret += tmp;
		}
		return ret;
	}
};
