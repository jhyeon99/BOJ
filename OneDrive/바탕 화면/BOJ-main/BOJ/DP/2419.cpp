#include <bits/stdc++.h>
using namespace std;
const int MAX = 301;
const int INF = 1e9;
int n, m;
int pos[MAX];
int zero, dp[MAX][MAX][2], ans;
int Rec(int l, int r, int state, int rpt)
{
	if (!rpt) return 0;
	int& ret = dp[l][r][state];
	if (ret != -1) return ret;
	ret = INF;
	int prev = !state ? pos[l] : pos[r];
	if (l - 1 >= 0) ret = min(ret, rpt * (prev - pos[l - 1]) + Rec(l - 1, r, 0, rpt - 1));
	if (r + 1 < n) ret = min(ret, rpt * (pos[r + 1] - prev) + Rec(l, r + 1, 1, rpt - 1));
	return ret;
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n >> m;
	bool isZero = false;
	for (int i = 0; i < n; i++) cin >> pos[i];
	pos[n++] = 0;
	sort(pos, pos + n);
	zero = lower_bound(pos, pos + n, 0) - pos;
	for (int i = 0; i < n; i++)
	{
		memset(dp, -1, sizeof dp);
		ans = max(ans, m * i - Rec(zero, zero, 0, i));
	}
	cout << ans;
	return 0;
}