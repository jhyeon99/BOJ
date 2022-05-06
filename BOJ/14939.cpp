#include <bits/stdc++.h>
using namespace std;
const int INF = 2e9;
const int MAX = 10;
const int WAY = 4;
bool arr[MAX][MAX], tmp[MAX][MAX];
int dx[WAY] = { -1, 1, 0, 0 }, dy[WAY] = { 0,0,-1,1 };
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	for (int i = 0; i < MAX; i++)
	{
		for (int j = 0; j < MAX; j++)
		{
			char c; cin >> c;
			if (c == 'O') arr[i][j] = true;
		}
	}
	int ans = INF;
	for (int bit = 0; bit < 1 << MAX; bit++)
	{
		int cnt = 0;
		for (int i = 0; i < MAX; i++)
		{
			for (int j = 0; j < MAX; j++)
			{
				tmp[i][j] = arr[i][j];
			}
		}
		for (int x = 0; x < MAX; x++)
		{
			if (bit & (1 << x))
			{
				tmp[0][x] ^= 1;
				for (int i = 0; i < WAY; i++)
				{
					int nx = x + dx[i];
					int ny = dy[i];
					if (nx < 0 || nx >= MAX || ny < 0 || ny >= MAX) continue;
					tmp[ny][nx] ^= 1;
				}
				cnt++;
			}
		}
		for (int y = 1; y < MAX; y++)
		{
			for (int x = 0; x < MAX; x++)
			{
				if (tmp[y - 1][x])
				{
					tmp[y][x] ^= 1;
					for (int i = 0; i < WAY; i++)
					{
						int nx = x + dx[i];
						int ny = y + dy[i];
						if (nx < 0 || nx >= MAX || ny < 0 || ny >= MAX) continue;
						tmp[ny][nx] ^= 1;
					}
					cnt++;
				}
			}
		}
		bool dark = true;
		for (int y = 0; y < MAX; y++)
		{
			for (int x = 0; x < MAX; x++)
			{
				if (tmp[y][x])
				{
					dark = false;
				}
			}
		}
		if (dark) ans = min(ans, cnt);
	}
	if (ans == INF) ans = -1;
	cout << ans;
	return 0;
}