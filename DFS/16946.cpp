#include <bits/stdc++.h>
using namespace std;

const int MAX = 1000;
const int WAY = 4;

int n, m;                          // 격자 크기
bool wall[MAX][MAX];               // 벽 여부
int groupNum[MAX][MAX];            // 각 칸이 속한 그룹 번호
int groupSize[MAX * MAX];          // 그룹별 빈 공간 크기
int groupCnt;                      // 그룹 개수
int dy[WAY] = { -1, 1, 0, 0 }, dx[WAY] = { 0, 0, -1, 1 }; // 상하좌우 이동

// DFS로 빈 공간 그룹화
void DFS(int y, int x)
{
	groupNum[y][x] = groupCnt;      // 현재 칸 그룹 번호 설정
	groupSize[groupCnt]++;          // 그룹 크기 증가

	for (int i = 0; i < WAY; i++)
	{
		int ny = y + dy[i], nx = x + dx[i];

		// 범위 벗어나면 패스
		if (0 > ny || ny >= n || 0 > nx || nx >= m) continue;

		// 이미 그룹에 속했거나 벽이면 패스
		if (groupNum[ny][nx] || wall[ny][nx]) continue;

		DFS(ny, nx); // 재귀 DFS
	}
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	cin >> n >> m;

	// 벽 정보 입력
	for (int i = 0; i < n; i++)
	{
		cin.ignore(); // 개행 제거
		for (int j = 0; j < m; j++)
		{
			wall[i][j] = cin.get() - '0';
		}
	}

	// 모든 빈 칸을 DFS로 그룹화
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (!groupNum[i][j] && !wall[i][j])
			{
				groupCnt++;
				DFS(i, j);
			}
		}
	}

	// 결과 출력
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < m; x++)
		{
			int ans = wall[y][x]; // 벽이면 1, 빈 칸이면 0

			if (!wall[y][x]) cout << ans; // 빈 칸이면 그대로 출력
			else
			{
				set<int> st;
				for (int i = 0; i < WAY; i++)
				{
					int ny = y + dy[i], nx = x + dx[i];
					if (0 > ny || ny >= n || 0 > nx || nx >= m) continue;
					st.insert(groupNum[ny][nx]); // 인접 그룹 번호 저장
				}

				for (int g : st) ans += groupSize[g]; // 인접 그룹 크기 합산
				cout << ans % 10;                     // 10으로 나눈 나머지 출력
			}
		}
		cout << '\n';
	}

	return 0;
}
