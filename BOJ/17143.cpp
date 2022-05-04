#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
const int MAX = 101;
const int WAY = 4;
const int dy[WAY] = { -1, 1, 0, 0 }, dx[WAY] = { 0, 0, 1, -1 };
int r, c, m;
int sz[MAX][MAX], idx[MAX][MAX];
struct Shark
{
	int y, x, s, d, z;
	Shark() {}
	void Move()
	{
		if (d <= 2)
		{
			int w = d == 1 ? 1 : r;
			if (s <= abs(y - w))
			{
				y += dy[d - 1] * s;
			}
			else if (s <= abs(y - w) + (r - 1))
			{
				d = (d - 1 ^ 1) + 1;
				y = w + dy[d - 1] * (s - (abs(y - w)));
			}
			else
			{
				y -= dy[d - 1] * (2 * (r - 1) - s);
			}
		}
		else
		{
			int w = d == 3 ? c : 1;
			if (s <= abs(x - w))
			{
				x += dx[d - 1] * s;
			}
			else if (s <= abs(x - w) + (c - 1))
			{
				d = (d - 1 ^ 1) + 1;
				x = w + dx[d - 1] * (s - (abs(x - w)));
			}
			else
			{
				x -= dx[d - 1] * (2 * (c - 1) - s);
			}
		}
	}
};
vector<Shark> shark;
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> r >> c >> m;
	for (int i = 0; i < m; i++)
	{
		Shark s;
		cin >> s.y >> s.x >> s.s >> s.d >> s.z;
		s.s %= ((s.d <= 2 ? r : c) - 1) * 2;
		shark.push_back(s);
	}
	int ans = 0;
	for (int k = 1; k <= c; k++)
	{
		memset(sz, 0, sizeof(sz));
		memset(idx, 0, sizeof(idx));
		vector<int> era;
		for (int i = 0; i < shark.size(); i++)
		{
			if (!sz[shark[i].y][shark[i].x])
			{
				sz[shark[i].y][shark[i].x] = shark[i].z;
				idx[shark[i].y][shark[i].x] = i;
			}
			else
			{
				if (sz[shark[i].y][shark[i].x] > shark[i].z)
				{
					era.push_back(i);
				}
				else
				{
					era.push_back(idx[shark[i].y][shark[i].x]);
					sz[shark[i].y][shark[i].x] = shark[i].z;
					idx[shark[i].y][shark[i].x] = i;
				}
			}
		}
		for (int j = 1; j <= r; j++)
		{
			if (sz[j][k])
			{
				ans += sz[j][k];
				era.push_back(idx[j][k]);
				break;
			}
		}
		sort(era.begin(), era.end(), greater<>());
		for (int i = 0; i < era.size(); i++)
		{
			shark.erase(shark.begin() + era[i]);
		}
		for (int i = 0; i < shark.size(); i++)
		{
			shark[i].Move();
		}
	}
	cout << ans;
	return 0;
}