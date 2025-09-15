#include <bits/stdc++.h>
using namespace std;
const int MAX = 32001;
int parent[MAX];
vector<int> child[MAX];
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n, m; cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		int a, b; cin >> a >> b;
		child[a].push_back(b);
		parent[b]++;
	}
	priority_queue<int, vector<int>, greater<int>> pq;
	for (int i = 1; i <= n; i++)
	{
		if (!parent[i]) pq.push(i);
	}
	while (pq.size())
	{
		int curr = pq.top(); pq.pop();
		cout << curr << ' ';
		for (int next : child[curr])
		{
			if (!--parent[next])
			{
				pq.push(next);
			}
		}
	}
	return 0;
}