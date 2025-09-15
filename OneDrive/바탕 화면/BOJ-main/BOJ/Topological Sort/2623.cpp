#include <bits/stdc++.h>
using namespace std;
const int MAX = 1001;
int par[MAX];
vector<int> child[MAX];
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n, m; cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		int s; cin >> s;
		int prev = 0;
		for (int i = 0; i < s; i++)
		{
			int curr; cin >> curr;
			if (prev)
			{
				if (find(child[prev].begin(), child[prev].end(), curr) == child[prev].end())
				{
					par[curr]++;
					child[prev].push_back(curr);
				}
			}
			prev = curr;
		}
	}
	queue<int> q;
	vector<int> ans;
	for (int i = 1; i <= n; i++) if (!par[i]) q.push(i);
	while (q.size())
	{
		int curr = q.front(); q.pop();
		ans.push_back(curr);
		for (int next : child[curr]) if (!--par[next]) q.push(next);
	}
	if (ans.size() == n) for (int a : ans) cout << a << '\n';
	else cout << 0;
	return 0;
}