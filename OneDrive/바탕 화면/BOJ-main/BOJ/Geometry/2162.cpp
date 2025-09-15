#include <bits/stdc++.h>
using namespace std;
const int MAX = 3000;
struct Point
{
	int x, y;
	Point(int x, int y) : x(x), y(y) {}
	bool operator>(Point p)
	{
		if (x == p.x) return y > p.y;
		return x > p.x;
	}
	bool operator<=(Point p)
	{
		if (x == p.x) return y <= p.y;
		return x <= p.x;
	}
};
struct Line
{
	Point a, b;
	Line(Point a, Point b) : a(a), b(b) {}
};
vector<Line> line;
vector<int> adj[MAX];
int group[MAX], groupNum, groupCnt;
int CCW(Point a, Point b, Point c)
{
	int res = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
	if (res > 0) return 1;
	else if (res == 0) return 0;
	else return -1;
}
bool IsCross(Line A, Line B)
{
	int AB = CCW(A.a, A.b, B.a) * CCW(A.a, A.b, B.b);
	int BA = CCW(B.a, B.b, A.a) * CCW(B.a, B.b, A.b);
	if (AB == 0 && BA == 0)
	{
		if (A.a > A.b) swap(A.a, A.b);
		if (B.a > B.b) swap(B.a, B.b);
		return B.a <= A.b && A.a <= B.b;
	}
	return AB <= 0 && BA <= 0;
}
void DFS(int curr)
{
	group[curr] = groupNum;
	groupCnt++;
	for (int next : adj[curr]) if (!group[next]) DFS(next);
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n; cin >> n;
	for (int i = 0; i < n; i++)
	{
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		line.push_back(Line(Point(x1, y1), Point(x2, y2)));
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (IsCross(line[i], line[j]))
			{
				adj[i].push_back(j);
				adj[j].push_back(i);
			}
		}
	}
	int maxGroupCnt = 0;
	for (int i = 0; i < n; i++)
	{
		if (!group[i])
		{
			groupNum++;
			groupCnt = 0;
			DFS(i);
			maxGroupCnt = max(maxGroupCnt, groupCnt);
		}
	}
	cout << groupNum << ' ' << maxGroupCnt;
	return 0;
}