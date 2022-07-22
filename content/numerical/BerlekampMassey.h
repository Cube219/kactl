/**
 * Author: Lucian Bicsi
 * Date: 2017-10-31
 * License: CC0
 * Source: Wikipedia
 * Description: Recovers any $n$-order linear recurrence relation from the first
 * $2n$ terms of the recurrence.
 * Useful for guessing linear recurrences after brute-forcing the first terms.
 * Should work on any field, but numerical stability for floats is not guaranteed.
 * Output will have size $\le n$.
 * Usage:
 *   berlekampMassey({0, 1, 1, 3, 5, 11}) // {1, 2}
 *   get_nth({ 1, 2 }, { 0, 1 }, n)
 * Time: O(N^2)
 * Status: bruteforce-tested mod 5 for n <= 5 and all s
 */
#pragma once

constexpr ll mod = 1000000007;

ll modpow(ll b, ll e) {
	ll ans = 1;
	for(; e; b = b * b % mod, e /= 2) if(e & 1) ans = ans * b % mod;
	return ans;
}

vector<ll> berlekampMassey(vector<ll> s) {
	int n = sz(s), L = 0, m = 0;
	vector<ll> C(n), B(n), T;
	C[0] = B[0] = 1;

	ll b = 1;
	rep(i,0,n) { ++m;
		ll d = s[i] % mod;
		rep(j,1,L+1) d = (d + C[j] * s[i - j]) % mod;
		if (!d) continue;
		T = C; ll coef = d * modpow(b, mod-2) % mod;
		rep(j,m,n) C[j] = (C[j] - coef * B[j - m]) % mod;
		if (2 * L > i) continue;
		L = i + 1 - L; B = T; b = d; m = 0;
	}

	C.resize(L + 1); C.erase(C.begin());
	for (ll& x : C) x = (mod - x) % mod;
	return C;
}

int get_nth(const vector<ll>& rec, const vector<ll>& dp, ll n) {
	int m = rec.size();
	vector<ll> s(m), t(m);
	s[0] = 1;
	if(m != 1) t[1] = 1;
	else t[0] = rec[0];
	auto mul = [&rec](const vector<ll>& v, const vector<ll>& w) {
		int m = v.size();
		vector<ll> t(2 * m);
		for(int j = 0; j < m; j++) {
			for(int k = 0; k < m; k++) {
				t[j + k] += 1ll * v[j] * w[k] % mod;
				if(t[j + k] >= mod) t[j + k] -= mod;
			}
		}
		for(int j = 2 * m - 1; j >= m; j--) {
			for(int k = 1; k <= m; k++) {
				t[j - k] += 1ll * t[j] * rec[k - 1] % mod;
				if(t[j - k] >= mod) t[j - k] -= mod;
			}
		}
		t.resize(m);
		return t;
	};
	while(n) {
		if(n & 1) s = mul(s, t);
		t = mul(t, t);
		n >>= 1;
	}
	ll ret = 0;
	for(int i = 0; i < m; i++) ret += 1ll * s[i] * dp[i] % mod;
	return ret % mod;
}
