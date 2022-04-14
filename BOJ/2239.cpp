#include <bits/stdc++.h>
using namespace std;
const int MAX = 9;
struct Point
{
	int x, y;
	Point(int x, int y) : x(x), y(y) {};
};
int n[MAX][MAX];
set<int>  vertical[MAX], horizontal[MAX], area[MAX];
vector<Point> blank;
bool ans;
inline int Area(Point p)
{
	return (p.y / 3) * 3 + (p.x / 3);
}
void DFS(int idx)
{
	if (idx == blank.size())
	{
		ans = true;
		for (int y = 0; y < MAX; y++)
		{
			for (int x = 0; x < MAX; x++)
			{
				cout << n[y][x];
			}
			cout << '\n';
		}
		return;
	}
	Point p = blank[idx];
	for (int i = 1; i <= 9; i++)
	{
		if (vertical[p.x].find(i) == vertical[p.x].end() && horizontal[p.y].find(i) == horizontal[p.y].end() && area[Area(p)].find(i) == area[Area(p)].end())
		{
			vertical[p.x].insert(i);
			horizontal[p.y].insert(i);
			area[Area(p)].insert(i);
			n[p.y][p.x] = i;
			DFS(idx + 1);
			if (ans) return;
			vertical[p.x].erase(i);
			horizontal[p.y].erase(i);
			area[Area(p)].erase(i);
			n[p.y][p.x] = 0;
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	for (int y = 0; y < MAX; y++)
	{
		for (int x = 0; x < MAX; x++)
		{
			n[y][x] = cin.get() - '0';
		}
		cin.get();
	}
	for (int y = 0; y < MAX; y++)
	{
		for (int x = 0; x < MAX; x++)
		{
			if (n[y][x])
			{
				vertical[x].insert(n[y][x]);
				horizontal[y].insert(n[y][x]);
				area[Area(Point(x, y))].insert(n[y][x]);
			}
			else
			{
				blank.push_back(Point(x, y));
			}
		}
	}
	DFS(0);
	return 0;
}