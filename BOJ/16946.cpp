#include <bits/stdc++.h>
using namespace std;
const int MAX = 1000;
const int WAY = 4;
int n, m;
bool wall[MAX][MAX];
int groupNum[MAX][MAX], groupSize[MAX * MAX], groupCnt;
int dy[WAY] = { -1, 1, 0, 0 }, dx[WAY] = { 0, 0, -1, 1 };
void DFS(int y, int x)
{
	groupNum[y][x] = groupCnt;
	groupSize[groupCnt]++;
	for (int i = 0; i < WAY; i++)
	{
		int ny = y + dy[i], nx = x + dx[i];
		if (0 > ny || ny >= n || 0 > nx || nx >= m) continue;
		if (groupNum[ny][nx] || wall[ny][nx]) continue;
		DFS(ny, nx);
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		cin.ignore();
		for (int j = 0; j < m; j++)
		{
			wall[i][j] = cin.get() - '0';
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (!groupNum[i][j] && !wall[i][j])
			{
				groupCnt++;
				DFS(i, j);
			}
		}
	}
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < m; x++)
		{
			int ans = wall[y][x];
			if (!wall[y][x]) cout << ans;
			else
			{
				set<int> st;
				for (int i = 0; i < WAY; i++)
				{
					int ny = y + dy[i], nx = x + dx[i];
					if (0 > ny || ny >= n || 0 > nx || nx >= m) continue;
					st.insert(groupNum[ny][nx]);
				}
				for (int g : st) ans += groupSize[g];
				cout << ans % 10;
			}
		}
		cout << '\n';
	}
	return 0;
}