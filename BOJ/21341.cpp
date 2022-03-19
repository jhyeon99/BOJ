#include <bits/stdc++.h>
using namespace std;
struct Point
{
	int x, y;
	Point() {}
	Point(int x, int y) : x(x), y(y) {}
	bool InRange(int s, int e)
	{
		return s <= x && x <= e && s <= y && y <= e;
	}
	Point operator+(const Point& p) const
	{
		return Point(x + p.x, y + p.y);
	}
	Point operator-(const Point& p) const
	{
		return Point(x - p.x, y - p.y);
	}
	bool operator<(const Point& p) const
	{
		return (x != p.x) ? x < p.x : y < p.y;
	}
	bool operator==(const Point& p) const
	{
		return x == p.x && y == p.y;
	}
};
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n; cin >> n;
	Point a; cin >> a.x >> a.y;
	Point b; cin >> b.x >> b.y;
	set<Point> moves;
	for (int i = 0; i < n; i++)
	{
		int x, y; cin >> x >> y;
		moves.insert(Point(x, y));
	}
	if (a == b)
	{
		cout << "Alice wins";
		return 0;
	}
	for (Point move : moves)
	{
		Point a1 = a + move;
		if (a1.InRange(1, n))
		{
			if (a1 == b || moves.find(b - a1) != moves.end())
			{
				cout << "Alice wins";
				return 0;
			}
		}
	}
	set<Point> vst;
	vst.insert(b);
	while (vst.size() < n * n)
	{
		Point ran = Point(rand() % n + 1, rand() % n + 1);
		if (vst.find(ran) == vst.end())
		{
			vst.insert(ran);
			bool flag = false;
			for (Point move : moves)
			{
				Point b1 = b + move;
				if (b1.InRange(1, n))
				{
					if (b1 == ran || moves.find(ran - b1) != moves.end())
					{
						flag = true;
					}
				}
			}
			if (!flag)
			{
				cout << "tie " << ran.x << ' ' << ran.y;
				return 0;
			}
		}
	}
	cout << "Bob wins";
	return 0;
}