#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 2D 좌표를 나타내는 구조체
struct Point
{
	int x, y;
	Point() {}
	Point(int x, int y) : x(x), y(y) {}

	// 좌표 비교 (x 우선, x 같으면 y 비교)
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

// 선분을 나타내는 구조체
struct Line
{
	Point a, b;
	Line() {}
	Line(Point a, Point b) : a(a), b(b) {}
};

// CCW (Counter ClockWise) : 세 점 a, b, c가 시계방향/반시계방향/일직선인지 판단
int CCW(Point a, Point b, Point c)
{
	ll res = ((ll)b.x - (ll)a.x) * ((ll)c.y - (ll)a.y) - ((ll)b.y - (ll)a.y) * ((ll)c.x - (ll)a.x);
	if (res > 0) return 1;    // 반시계 방향
	else if (res == 0) return 0; // 일직선
	else return -1;            // 시계 방향
}

// 두 선분이 교차하는지 판정
bool IsCross(Line A, Line B)
{
	int AB = CCW(A.a, A.b, B.a) * CCW(A.a, A.b, B.b);
	int BA = CCW(B.a, B.b, A.a) * CCW(B.a, B.b, A.b);

	if (AB == 0 && BA == 0) // 두 선분이 한 직선상에 있는 경우
	{
		// 좌표 정렬
		if (A.a > A.b) swap(A.a, A.b);
		if (B.a > B.b) swap(B.a, B.b);
		// 선분 겹침 여부 판정
		return B.a <= A.b && A.a <= B.b;
	}

	// 일반적인 교차 판정
	return AB <= 0 && BA <= 0;
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	Line l1, l2;
	// 첫 번째 선분 입력
	cin >> l1.a.x >> l1.a.y >> l1.b.x >> l1.b.y;
	// 두 번째 선분 입력
	cin >> l2.a.x >> l2.a.y >> l2.b.x >> l2.b.y;

	// 두 선분이 교차하면 1, 아니면 0 출력
	cout << IsCross(l1, l2);

	return 0;
}
