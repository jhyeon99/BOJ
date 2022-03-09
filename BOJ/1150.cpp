#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
const int INF = 1e9;
int n, k, a;
int s[100001], d[100001], l[100001], r[100001];
bool v[100001];
priority_queue<pii, vector<pii>, greater<pii>> pq;
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n >> k;
	d[0] = d[n] = INF;
	for (int i = 0; i < n; i++)
	{
		cin >> s[i];
		l[i + 1] = i;
		if (i > 0)
		{
			r[i - 1] = i;
			d[i] = s[i] - s[i - 1];
		}
		pq.push(pii(d[i], i));
	}
	while (k--)
	{
		while (v[pq.top().second]) pq.pop();
		int dist = pq.top().first;
		int idx = pq.top().second;
		pq.pop();
		v[l[idx]] = v[r[idx]] = true;
		d[idx] = d[l[idx]] + d[r[idx]] - d[idx];
		l[idx] = l[l[idx]];
		r[idx] = r[r[idx]];
		l[r[idx]] = idx;
		r[l[idx]] = idx;
		pq.push(pii(d[idx], idx));
		a += dist;
	}
	cout << a;
	return 0;
}