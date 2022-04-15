#include <bits/stdc++.h>
using namespace std;
const int MAX = 32001;
int parCnt[MAX];
vector<int> child[MAX];
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n, m; cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		int a, b; cin >> a >> b;
		parCnt[b]++;
		child[a].push_back(b);
	}
	queue<int> q;
	for (int i = 1; i <= n; i++) if (!parCnt[i]) q.push(i);
	while (q.size())
	{
		int curr = q.front(); q.pop();
		cout << curr << ' ';
		for (int next : child[curr])
		{
			if (!--parCnt[next])
			{
				q.push(next);
			}
		}
	}
	return 0;
}