#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
const int MAX = 10;
int diag1[2 * MAX - 1], diag2[2 * MAX - 1];
vector<pii> pos[2];
int cnt[2], ans[2];
void DFS(int prev, bool color)
{
	for (int i = prev + 1; i < pos[color].size(); i++)
	{
		pii p = pos[color][i];
		int p1 = p.first + p.second, p2 = MAX - p.first - 1 + p.second;
		if (diag1[p1] || diag2[p2]) continue;
		diag1[p1]++, diag2[p2]++;
		ans[color] = max(ans[color], ++cnt[color]);
		DFS(i, color);
		diag1[p1]--, diag2[p2]--;
		cnt[color]--;
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n; cin >> n;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			bool b; cin >> b;
			if (b)
			{
				pos[(i + j) % 2].push_back(pii(j, i));
			}
		}
	}
	DFS(-1, 0);
	DFS(-1, 1);
	cout << ans[0] + ans[1];
	return 0;
}