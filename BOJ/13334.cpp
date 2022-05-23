#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
priority_queue<pii, vector<pii>, greater<pii>> pq1;
priority_queue<int, vector<int>, greater<int>> pq2;
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n; cin >> n;
	for (int i = 0; i < n; i++)
	{
		int h, o; cin >> h >> o;
		if (h > o) swap(h, o);
		pq1.push(pii(o, h));
	}
	int d; cin >> d;
	int ans = 0, cnt = 0;
	while (pq1.size())
	{
		int e = pq1.top().first;
		int s = pq1.top().second;
		pq1.pop();
		cnt++;
		pq2.push(s);
		int x = e - d;
		while (pq2.size())
		{
			if (pq2.top() >= x) break;
			pq2.pop();
			cnt--;
		}
		ans = max(ans, cnt);
	}
	cout << ans;
	return 0;
}