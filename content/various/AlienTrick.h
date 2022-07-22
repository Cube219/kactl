/**
 * Author: shjohw12
 * Date: 2022-07-22
 * Description: Alien Trick
 */
#pragma once

// 즉 이분탐색을 돌렸을 때 최종적으로 기울기 a를 얻지 못 할 수 있지만, 기울기 a를 반드시 한 번
거치게 된다. 그 때의 접선 mid*x + mx에 대하여 x=K 일 때의 값 mid*K + mx가 답이 되고, 이것은
다른 어떤 접선에서의 x=K 일 때의 값보다 작거나 같으므로 answer = inf 로 놓고 answer =
min(answer, mid*K + mx) 를 반복하면 결국 답을 구할 수 있게 되는 것이다.
// 반대로 볼록함수 + 최솟값 구하기이면 연산할 때마다 mid를 더한다고 생각하고 x=K 일 때 접선의
값이 항상 크거나 같으므로 answer = -inf로 놓고 answer = max(answer, -mid*K + mn) 를 반복하면
된다.
signed main()
{
	int N; int K; cin >> N >> K;
	vector<int> A(N);
	for(auto& it : A) cin >> it;
	vector<int> suf(N + 1);
	for(int i = N - 1; i >= 0; --i)
		suf[i] = suf[i + 1] + A[i];
	int lf = 0, rg = 1e16;
	int ans = inf;
	while(lf <= rg)
	{
		int mid = (lf + rg) / 2;
		vector<int> dp(N + 1);
		vector<int> cnt(N + 1);
		vector<pair<int, int>> memo(N + 1);
		pair<int, int> mx = make_pair(-mid, 0);
		for(int i = N - 1; i >= 0; --i)
		{
			dp[i] = suf[i] + mx.first;
			cnt[i] = mx.second + 1;
			memo[i] = max(memo[i + 1], make_pair(dp[i], cnt[i]));
			mx = max(mx, make_pair(memo[i].first - mid - suf[i], memo[i].second));
		}
		ans = min(ans, memo[0].first + mid * K);
		if(cnt[0] <= K) rg = mid - 1;
		else lf = mid + 1;
	}
	cout << ans << '\n';
	return 0;
}
