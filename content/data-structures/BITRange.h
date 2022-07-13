/**
 * Author: max804
 * Date: 2022-07-13
 * License: CC0
 * Description: Computes partial sums a[0] + a[1] + ... + a[pos], and updates elements in [l, r].
 * Time: $O(\log N)$.
 * Usage:
 *  FenwickRange fw(n);
 *  fw.update(l, r, 10);
 *  fw.query(5);
 */
#pragma once

struct FenwickRange
{
	int n;
	vector<ll> tmul, tadd;
	FenwickRange(int _n) : n(_n + 1), tmul(_n + 1, 0), tadd(_n + 1, 0) {}

	void udtImpl(int pos, ll mul, ll add)
	{
		for(; pos < n; pos += (pos & -pos)) {
			tmul[pos] += mul;
			tadd[pos] += add;
		}
	}

	void update(int l, int r, ll v)
	{
		l++;
		r++;
		udtImpl(l, v, -v * (l - 1));
		udtImpl(r, -v, v * r);
	}

	ll query(int pos)
	{
		pos++;
		ll mul = 0, add = 0;
		int st = pos;
		for(; pos > 0; pos -= (pos & -pos)) {
			mul += tmul[pos];
			add += tadd[pos];
		}
		return mul * st + add;
	}
};
