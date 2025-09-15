#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 2차원 점 구조체
struct Point
{
    int x, y;
    bool operator<(const Point& a) // y좌표 기준 정렬, 같으면 x좌표 기준
    {
        return y != a.y ? y < a.y : x < a.x;
    }
};

// CCW 함수: 세 점이 만드는 벡터의 방향 판단
ll CCW(const Point& a, const Point& b, const Point& c)
{
    // (b - a) x (c - a) = 0이면 일직선, >0이면 반시계, <0이면 시계
    return (ll)a.x * (ll)b.y + (ll)b.x * (ll)c.y + (ll)c.x * (ll)a.y
         - (ll)b.x * (ll)a.y - (ll)c.x * (ll)b.y - (ll)a.x * (ll)c.y;
}

// 두 점 사이 거리 제곱
ll Distance(Point a, Point b)
{
    return ll(a.x - b.x) * ll(a.x - b.x) + ll(a.y - b.y) * ll(a.y - b.y);
}

Point p[100000]; // 점 배열
stack<int> ch;   // 볼록 껍질 스택

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;

    // 점 입력
    for (int i = 0; i < n; i++) cin >> p[i].x >> p[i].y;

    // 1. 기준점 선택: y좌표 가장 작은 점(p[0])
    sort(p, p + n);

    // 2. 기준점 기준 각도 순 정렬
    sort(p + 1, p + n, [&](const Point& a, const Point& b)
    {
        ll ccw = CCW(p[0], a, b);
        if (ccw == 0) // 일직선이면 기준점과 거리 짧은 순
            return Distance(p[0], a) < Distance(p[0], b);
        return ccw > 0; // 반시계 방향이 먼저
    });

    // 3. 볼록 껍질 스택 초기화
    ch.push(0);
    ch.push(1);

    // 4. 나머지 점들 처리
    for (int next = 2; next < n; next++)
    {
        while (ch.size() >= 2)
        {
            int first, second;
            second = ch.top(); ch.pop();
            first = ch.top();

            if (CCW(p[first], p[second], p[next]) > 0)
            {
                ch.push(second); // 반시계이면 유지
                break;
            }
            // 시계 방향이면 second 제거
        }
        ch.push(next);
    }

    // 5. 결과: 볼록 껍질 점 개수
    cout << ch.size();
    return 0;
}
