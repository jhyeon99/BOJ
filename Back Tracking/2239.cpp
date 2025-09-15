#include <bits/stdc++.h>
using namespace std;

const int MAX = 9;

// 좌표를 나타내는 구조체
struct Point
{
	int x, y;
	Point(int x, int y) : x(x), y(y) {};
};

// 스도쿠 판
int n[MAX][MAX];

// 각 열, 행, 3x3 영역에서 이미 사용된 숫자 관리
set<int> vertical[MAX], horizontal[MAX], area[MAX];

// 빈 칸 좌표 저장
vector<Point> blank;

// 해답을 찾았는지 여부
bool ans;

// (x, y) 좌표가 속한 3x3 영역 번호 계산
inline int Area(Point p)
{
	return (p.y / 3) * 3 + (p.x / 3);
}

// DFS 백트래킹으로 스도쿠 채우기
void DFS(int idx)
{
	// 모든 빈 칸을 채웠으면 출력하고 종료
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
	// 1~9 숫자 시도
	for (int i = 1; i <= 9; i++)
	{
		// 현재 행, 열, 영역에 i가 없으면 배치 가능
		if (vertical[p.x].find(i) == vertical[p.x].end() &&
			horizontal[p.y].find(i) == horizontal[p.y].end() &&
			area[Area(p)].find(i) == area[Area(p)].end())
		{
			// 숫자 배치
			vertical[p.x].insert(i);
			horizontal[p.y].insert(i);
			area[Area(p)].insert(i);
			n[p.y][p.x] = i;

			// 다음 빈 칸으로 이동
			DFS(idx + 1);

			// 이미 해답을 찾았으면 되돌아가지 않음
			if (ans) return;

			// 백트래킹: 원상복구
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

	// 스도쿠 입력 받기
	for (int y = 0; y < MAX; y++)
	{
		for (int x = 0; x < MAX; x++)
		{
			n[y][x] = cin.get() - '0'; // 한 문자씩 읽기
		}
		cin.get(); // 줄바꿈 제거
	}

	// 초기 상태 세팅: 빈 칸과 사용된 숫자 기록
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

	// DFS 시작
	DFS(0);
	return 0;
}
