#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAX = 1001;
int a[MAX], b[MAX], aSum[MAX], bSum[MAX];
vector<int> aSubarr, bSubarr;
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int t, n; cin >> t >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
		aSum[i] = aSum[i - 1] + a[i];
	}
	int m; cin >> m;
	for (int i = 1; i <= m; i++)
	{
		cin >> b[i];
		bSum[i] = bSum[i - 1] + b[i];
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j <= n; j++)
		{
			aSubarr.push_back(aSum[j] - aSum[i]);
		}
	}
	for (int i = 0; i < m; i++)
	{
		for (int j = i + 1; j <= m; j++)
		{
			bSubarr.push_back(bSum[j] - bSum[i]);
		}
	}
	sort(bSubarr.begin(), bSubarr.end());
	ll ans = 0;
	for (int sum : aSubarr)
	{
		ans += upper_bound(bSubarr.begin(), bSubarr.end(), t - sum) - lower_bound(bSubarr.begin(), bSubarr.end(), t - sum);
	}
	cout << ans;
	return 0;
}