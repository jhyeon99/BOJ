#include <bits/stdc++.h>
using namespace std;

// 2D 좌표를 나타내는 구조체
struct Point
{
    int x, y;
    Point() {}
    Point(int x, int y) : x(x), y(y) {}

    // 좌표가 범위 안에 있는지 확인
    bool InRange(int s, int e)
    {
        return s <= x && x <= e && s <= y && y <= e;
    }

    // 연산자 오버로딩: 벡터 덧셈
    Point operator+(const Point& p) const
    {
        return Point(x + p.x, y + p.y);
    }

    // 연산자 오버로딩: 벡터 뺄셈
    Point operator-(const Point& p) const
    {
        return Point(x - p.x, y - p.y);
    }

    // 좌표 비교 (정렬용)
    bool operator<(const Point& p) const
    {
        return (x != p.x) ? x < p.x : y < p.y;
    }

    // 좌표 동일 여부
    bool operator==(const Point& p) const
    {
        return x == p.x && y == p.y;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n; cin >> n;  // 체스판 크기 n x n

    Point a; cin >> a.x >> a.y;  // Alice 초기 위치
    Point b; cin >> b.x >> b.y;  // Bob 초기 위치

    set<Point> moves;  // Alice가 이동 가능한 좌표 벡터
    for (int i = 0; i < n; i++)
    {
        int x, y; cin >> x >> y;
        moves.insert(Point(x, y));
    }

    // Alice와 Bob이 같은 위치면 Alice 승
    if (a == b)
    {
        cout << "Alice wins";
        return 0;
    }

    // Alice가 바로 Bob을 잡을 수 있는지 확인
    for (Point move : moves)
    {
        Point a1 = a + move; // 이동 후 좌표
        if (a1.InRange(1, n))
        {
            // Bob이 현재 위치이거나 다음 이동으로 잡을 수 있으면 Alice 승
            if (a1 == b || moves.find(b - a1) != moves.end())
            {
                cout << "Alice wins";
                return 0;
            }
        }
    }

    // 임의 좌표에서 Bob이 안전한지 확인
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
                    // Alice 이동으로 잡을 수 있는지 체크
                    if (b1 == ran || moves.find(ran - b1) != moves.end())
                    {
                        flag = true;
                    }
                }
            }
            // 안전한 좌표 발견 -> 무승부와 좌표 출력
            if (!flag)
            {
                cout << "tie " << ran.x << ' ' << ran.y;
                return 0;
            }
        }
    }

    // 그 외의 경우 Bob 승
    cout << "Bob wins";
    return 0;
}
