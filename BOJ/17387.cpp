#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct Point
{
	int x, y;
	Point() {}
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
	Line() {}
	Line(Point a, Point b) : a(a), b(b) {}
};
int CCW(Point a, Point b, Point c)
{
	ll res = ((ll)b.x - (ll)a.x) * ((ll)c.y - (ll)a.y) - ((ll)b.y - (ll)a.y) * ((ll)c.x - (ll)a.x);
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
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	Line l1, l2;
	cin >> l1.a.x >> l1.a.y >> l1.b.x >> l1.b.y;
	cin >> l2.a.x >> l2.a.y >> l2.b.x >> l2.b.y;
	cout << IsCross(l1, l2);
	return 0;
}