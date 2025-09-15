#include <bits/stdc++.h>
using namespace std;

const int MAX = 10000;

// 2D 좌표를 나타내는 구조체
struct Point
{
	double x, y;
	Point() {};
	Point(double x, double y) : x(x), y(y) {}
};

// CCW 함수를 이용한 삼각형 면적 계산
// a, b, c 세 점이 이루는 삼각형의 signed area 계산
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
	int n; cin >> n; // 다각형 꼭짓점의 개수
	for (int i = 0; i < n; i++)
	{
		cin >> p[i].x >> p[i].y; // 각 꼭짓점 좌표 입력
	}

	double res = 0;
	// 다각형 면적 계산
	// 삼각형 면적을 p[0] 기준으로 나머지 점과 연결하여 합산
	for (int i = 1; i < n; i++)
	{
		res += CCW(p[0], p[i - 1], p[i]);
	}

	cout << fixed;
	cout.precision(1); // 소수점 첫째 자리까지 출력
	cout << abs(res / 2); // 면적은 항상 양수이므로 절댓값 사용
	return 0;
}
