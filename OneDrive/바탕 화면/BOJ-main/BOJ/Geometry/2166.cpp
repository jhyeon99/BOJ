#include <bits/stdc++.h>
using namespace std;
const int MAX = 10000;
struct Point
{
	double x, y;
	Point() {};
	Point(double x, double y) : x(x), y(y) {}
};
double CCW(Point a, Point b, Point c)
{
	double ret = a.x * b.y + b.x * c.y + c.x * a.y;
	ret += (-a.y * b.x - b.y * c.x - c.y * a.x);
	return ret;
}
Point p[MAX];
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n; cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> p[i].x >> p[i].y;
	}
	double res = 0;
	for (int i = 1; i < n; i++)
	{
		res += CCW(p[0], p[i - 1], p[i]);
	}
	cout << fixed;
	cout.precision(1);
	cout << abs(res / 2);
	return 0;
}