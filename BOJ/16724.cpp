#include <bits/stdc++.h>
using namespace std;
const int MAX = 1000;
const int WAY = 4;
int n, m;
char dir[MAX][MAX];
int num[MAX][MAX], cnt, ans;
int dy[WAY] = { -1, 1, 0, 0 }, dx[WAY] = { 0, 0, -1, 1 };
int Direction(char c)
{
	switch (c)
	{
	case 'U':
		return 0;
	case 'D':
		return 1;
	case 'L':
		return 2;
	case 'R':
		return 3;
	default:
		return -1;
	}
}
void DFS(int y, int x)
{
	num[y][x] = cnt;
	int d = Direction(dir[y][x]);
	int ny = y + dy[d], nx = x + dx[d];
	if (!num[ny][nx]) DFS(ny, nx);
	else if (num[ny][nx] == cnt) ans++;
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		cin.get();
		for (int j = 0; j < m; j++)
		{
			dir[i][j] = cin.get();
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (!num[i][j])
			{
				cnt++;
				DFS(i, j);
			}
		}
	}
	cout << ans;
	return 0;
}