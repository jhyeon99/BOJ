#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
vector<pii> v;
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n, m; cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		int from, to; cin >> from >> to;
		if (from > to) v.push_back(pii(to, from));
	}
	sort(v.begin(), v.end());
	ll ans = m;
	int left = -1, right = -1;
	for (pii p : v)
	{
		if (p.first > right)
		{
			ans += 2 * (right - left);
			left = p.first;
			right = p.second;
		}
		else right = max(right, p.second);
	}
	ans += 2 * (right - left);
	cout << ans;
	return 0;
}