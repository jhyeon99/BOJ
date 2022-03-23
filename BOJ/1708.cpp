#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct Point
{
	int x, y;
	bool operator<(const Point& a)
	{
		return y != a.y ? y < a.y : x < a.x;
	}
};
ll CCW(const Point& a, const Point& b, const Point& c)
{
	return (ll)a.x * (ll)b.y + (ll)b.x * (ll)c.y + (ll)c.x * (ll)a.y - (ll)b.x * (ll)a.y - (ll)c.x * (ll)b.y - (ll)a.x * (ll)c.y;
}
ll Distance(Point a, Point b)
{
	return ll(a.x - b.x) * ll(a.x - b.x) + ll(a.y - b.y) * ll(a.y - b.y);
}
Point p[100000];
stack<int> ch;
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n; cin >> n;
	for (int i = 0; i < n; i++) cin >> p[i].x >> p[i].y;
	sort(p, p + n);
	sort(p + 1, p + n, [&](const Point& a, const Point& b)
		{
			ll ccw = CCW(p[0], a, b);
			if (ccw == 0)
			{
				return Distance(p[0], a) < Distance(p[0], b);
			}
			return ccw > 0;
		});
	ch.push(0);
	ch.push(1);
	for (int next = 2; next < n; next++)
	{
		while (ch.size() >= 2)
		{
			int first, second;
			second = ch.top();
			ch.pop();
			first = ch.top();
			if (CCW(p[first], p[second], p[next]) > 0)
			{
				ch.push(second);
				break;
			}
		}
		ch.push(next);
	}
	cout << ch.size();
	return 0;
}