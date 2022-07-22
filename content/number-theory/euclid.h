/**
 * Author: Cube219
 * Date: 2022-07-22
 * Description: Finds two integers $x$ and $y$, such that $ax+by=\gcd(a,b)$. If
 * you just need gcd, use the built in \texttt{\_\_gcd} instead.
 * If $a$ and $b$ are coprime, then $x$ is the inverse of $a \pmod{b}$.
 */
#pragma once

struct ENode {
	ll s, t, g;
};

ENode eeuc(ll a, ll b) {
	if(b == 0) return { 1, 0, a };

	ll r = a % b;
	auto res = eeuc(b, r);
	ll x = res.t;
	ll y = res.s - a / b * res.t;
	return { x, y, res.g };
}

// Ax+By=C, D=gcd(A, B)=g
// x0 = s * C/D       y0 = t * C/D
// s = x0 + k * B/D   t = y0 - k * A/D
