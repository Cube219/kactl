/**
 * Author: max804
 * Date: 2022-11-18
 * Description: Computes partial sums a[0] + a[1] + ... + a[pos], and updates an elements.
 * Time: $O(\log N)$.
 * Usage:
 *  Fenwick fw(n);
 *  fw.update(a, 10);
 *  fw.query(5);
 */
#pragma once

struct Fenwick {
	int n;
	vector<ll> t;
	Fenwick(int _n) : n(_n + 1), t(_n + 1, 0) {}

	void update(int pos, ll dv) {
		for(pos++; pos < n; pos += (pos & -pos)) t[pos] += dv;
	}

	ll query(int pos) {
		ll res = 0;
		for(pos++; pos > 0; pos -= (pos & -pos)) res += t[pos];
		return res;
	}
};
