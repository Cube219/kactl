/**
 * Author: Cube219
 * Date: 2022-07-22
 * Description: Finds two integers $x$ and $y$, such that $ax+by=\gcd(a,b)$. If
 * you just need gcd, use the built in \texttt{\_\_gcd} instead.
 * If $a$ and $b$ are coprime, then $x$ is the inverse of $a \pmod{b}$.
 */
#pragma once

struct ERes { ll x, y, g; };
ERes eeuc(ll a, ll b)
{
	if(b == 0) return { 1, 0, a };

	ERes res = eeuc(b, a % b);
	ll x = res.y;
	ll y = res.x - a / b * res.y;
	return { x, y, res.g };
}
// Ax+By=C, D=gcd(A,B)=g
// x0 = x * C/D       y0 = y * C/D
// s = x0 + t*B/D   t = y0 - t*A/D
