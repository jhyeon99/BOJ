#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
const int MAX = 100001;
vector<pii> adj[MAX];
bool vst[MAX];
int MST2()
{
	int ret = 0;
	priority_queue<pii, vector<pii>, greater<pii>> pq;
	pq.push(pii(0, 1));
	int cut = 0;
	while (!pq.empty())
	{
		int cWeight = pq.top().first;
		int curr = pq.top().second;
		pq.pop();
		if (vst[curr]) continue;
		vst[curr] = true;
		ret += cWeight;
		cut = max(cut, cWeight);
		for (auto nextPair : adj[curr])
		{
			int nWeight = nextPair.first, next = nextPair.second;
			if (!vst[next])
			{
				pq.push({ nWeight, next });
			}
		}
	}
	ret -= cut;
	return ret;
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n, m; cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		int a, b, c; cin >> a >> b >> c;
		adj[a].push_back(pii(c, b));
		adj[b].push_back(pii(c, a));
	}
	cout << MST2();
	return 0;
}