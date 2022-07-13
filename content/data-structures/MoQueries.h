/**
 * Author: max804
 * Date: 2022-07-13
 * Description: Mo's query
 * Usage:
 * Time: O(N \sqrt Q)
 */
#pragma once

//convert (x,y) to d
ll hilbertCurve(int x, int y, ll n) {
	ll rx, ry, s = 1, d = 0;
	while(s < n) s *= 2;
	n = s;
	for(s = n / 2; s > 0; s /= 2) {
		rx = (x & s) > 0;
		ry = (y & s) > 0;
		d += s * s * ((3 * rx) ^ ry);
		// rotate
		if(ry == 0) {
			if(rx == 1) {
				x = n - 1 - x;
				y = n - 1 - y;
			}
			swap(x, y);
		}
	}
	return d;
}

struct Query {
	int l, r, idx, h;
};

int main() {
	vector<Query> ql(m);
	for(auto& q : ql) q.h = hilbertCurve(q.l, q.r, n);
	sort(ql.begin(), ql.end(), [](const auto& l, const auto& r) {
		return l.h < r.h;
	});

	auto add = [&](int idx) {};
	auto del = [&](int idx) {};
	auto calc = [&]() -> int {};

	vector<int> res(m);
	int cl = ql[0].l, cr = ql[0].l - 1;
	for(auto [l, r, idx, _] : ql) {
		while(l < cl) add(--cl);
		while(cr < r) add(++cr);
		while(cl < l) del(cl++);
		while(r < cr) del(cr--);
		res[idx] = calc();
	}
}
