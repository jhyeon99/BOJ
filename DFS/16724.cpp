#include <bits/stdc++.h>
using namespace std;

const int MAX = 1000;
const int WAY = 4;

int n, m;                   // 격자 크기
char dir[MAX][MAX];          // 각 칸의 방향 정보
int num[MAX][MAX], cnt, ans; // num: 방문 그룹 번호, cnt: 현재 그룹 번호, ans: 사이클 개수
int dy[WAY] = { -1, 1, 0, 0 }, dx[WAY] = { 0, 0, -1, 1 };

// 문자 방향을 배열 인덱스로 변환
int Direction(char c)
{
	switch (c)
	{
	case 'U': return 0;
	case 'D': return 1;
	case 'L': return 2;
	case 'R': return 3;
	default: return -1;
	}
}

// DFS로 사이클 및 방문 처리
void DFS(int y, int x)
{
	num[y][x] = cnt;                  // 현재 칸을 현재 그룹으로 표시
	int d = Direction(dir[y][x]);      // 이동 방향 확인
	int ny = y + dy[d], nx = x + dx[d]; // 다음 칸 좌표 계산

	if (!num[ny][nx]) DFS(ny, nx);    // 방문하지 않은 칸이면 DFS 재귀
	else if (num[ny][nx] == cnt) ans++; // 같은 그룹에 이미 방문한 칸이면 사이클 발생
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		cin.get(); // 개행 제거
		for (int j = 0; j < m; j++)
		{
			dir[i][j] = cin.get(); // 방향 입력
		}
	}

	// 모든 칸을 탐색하며 DFS 실행
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (!num[i][j])
			{
				cnt++;     // 새로운 그룹 시작
				DFS(i, j);
			}
		}
	}

	cout << ans; // 사이클 개수 출력
	return 0;
}
