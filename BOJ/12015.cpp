#include <bits/stdc++.h>
using namespace std;
const int INF = 2e9;
const int MAX = 1000000;
int arr[MAX], dp[MAX];
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n; cin >> n;
	for (int i = 0; i < n; i++) cin >> arr[i];
	for (int i = 0; i < n; i++) dp[i] = INF;
	for (int i = 0; i < n; i++) dp[lower_bound(dp, dp + n, arr[i]) - dp] = arr[i];
	cout << lower_bound(dp, dp + n, INF) - dp;
	return 0;
}