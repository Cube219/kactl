/**
 * Author: Cube219
 * 
 * Description: Divide and Conquar Optimization DP example
 */
#pragma once

auto dnc = [&](auto&& self, int l, int r, int minj, int maxj) {
	if(l > r) return;

	int i = (l + r) / 2;

	int midj = minj;
	ll mn = INF;
	int ed = min(maxj, i);
	for(int j = minj; j <= ed; ++j) {
		ll v = dp[1][j] + (sum[i] - sum[j]) * (i - j);
		if(mn > v) {
			mn = v;
			midj = j;
		}
	}
	dp[0][i] = mn;
	self(self, l, i - 1, minj, midj);
	self(self, i + 1, r, midj, maxj);
};

for(int i = 0; i < g; ++i) {
	dnc(dnc, 1, n, 0, n);
	swap(dp[0], dp[1]);
	fill(dp[0].begin() + 1, dp[0].end(), INF);
}
