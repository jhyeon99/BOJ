#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;
int n, a[200000], b[200000];
ll Solve()
{
	vector<pii> v;
	for (int i = 0; i < n; i++)
	{
		v.push_back(pii(b[i], a[i]));
	}
	sort(v.begin(), v.end());
	ll ret = v[0].second;
	priority_queue<int> pq;
	for (int i = 1; i + 1 < n; i += 2)
	{
		pq.push(v[i].second);
		pq.push(v[i + 1].second);
		ret += pq.top();
		pq.pop();
	}
	return ret;
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	for (int i = 0; i < n; i++)
	{
		cin >> b[i];
	}
	cout << Solve();
	return 0;
}