/**
 * Author: Cube219
 * Date: 2021-10-07
 * License: CC0
 * Description: Finds binomial coefficient. MOD must be prime.
 */
#pragma once

template <int mod>
struct BiCoeff
{
	vector<ll> fact, invfact;

	BiCoeff(int n) : fact(n + 1), invfact(n + 1) {
		fact[0] = 1;
		for(int i = 1; i <= n; ++i) fact[i] = fact[i - 1] * i % mod;
		invfact[n] = pw(fact[n], mod - 2);
		for(int i = n - 1; i >= 0; --i) invfact[i] = invfact[i + 1] * (i + 1) % mod;
	}

	ll pw(ll a, ll b) {
		ll res = 1;
		while(b > 0) {
			if(b & 1) res = res * a % mod;
			a = a * a % mod;
			b >>= 1;
		}
		return res;
	}

	ll get(int n, int r) {
		return fact[n] * (invfact[r] * invfact[n - r] % mod) % mod;
	}

	ll get_lucas(ll n, ll r) {
		ll res = 1;
		while(n > 0 || r > 0) {
			ll a = n % mod;
			ll b = r % mod;
			res *= ncr(a, b);
			res %= mod;

			n /= mod;
			r /= mod;
		}
		return res;
	}
};
