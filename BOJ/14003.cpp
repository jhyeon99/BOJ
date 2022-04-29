#include <bits/stdc++.h>
using namespace std;
const int INF = 2e9;
const int MAX = 1000000;
int arr[MAX], dp[MAX], idx[MAX];
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n; cin >> n;
	for (int i = 0; i < n; i++) cin >> arr[i];
	for (int i = 0; i < n; i++) dp[i] = INF;
	for (int i = 0; i < n; i++)
	{
		int x = lower_bound(dp, dp + n, arr[i]) - dp;
		dp[x] = arr[i];
		idx[i] = x;
	}
	int a1 = lower_bound(dp, dp + n, INF) - dp;
	cout << a1 << '\n';
	vector<int> a2;
	for (int i = n - 1, j = a1 - 1; i >= 0; i--)
	{
		if (idx[i] == j)
		{
			a2.push_back(i);
			j--;
		}
	}
	reverse(a2.begin(), a2.end());
	for (int a : a2) cout << arr[a] << ' ';
	return 0;
}