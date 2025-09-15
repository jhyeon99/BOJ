#include <bits/stdc++.h>
using namespace std;
const int MAX = 100000;
const int INF = 1e9;
int a[MAX];
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n, s; cin >> n >> s;
	for (int i = 0; i < n; i++) cin >> a[i];
	int l = 0, r = 0, sum = a[0], ans = INF;
	while (r < n)
	{
		if (sum >= s) ans = min(ans, r - l + 1);
		if (sum - a[l] >= s)
		{
			sum -= a[l++];
		}
		else
		{
			sum += a[++r];
		}
	}
	if (ans == INF) ans = 0;
	cout << ans;
	return 0;
}