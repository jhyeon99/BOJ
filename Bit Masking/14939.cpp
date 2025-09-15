#include <bits/stdc++.h>
using namespace std;

const int INF = 2e9;  // 초기 정답 무한대
const int MAX = 10;   // 그리드 크기 10x10
const int WAY = 4;    // 상하좌우 이동

bool arr[MAX][MAX], tmp[MAX][MAX];  // arr: 초기 상태, tmp: 시뮬레이션용 복사
int dx[WAY] = { -1, 1, 0, 0 }, dy[WAY] = { 0, 0, -1, 1 }; // 상하좌우 좌표 변화

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	// 입력 받기, 'O'면 true(켜짐) 저장
	for (int i = 0; i < MAX; i++)
	{
		for (int j = 0; j < MAX; j++)
		{
			char c; cin >> c;
			if (c == 'O') arr[i][j] = true;
		}
	}

	int ans = INF;  // 최소 클릭 수 초기화

	// 첫 행의 모든 경우의 수(2^10) 시도
	for (int bit = 0; bit < 1 << MAX; bit++)
	{
		int cnt = 0; // 클릭 횟수 카운트

		// tmp에 현재 arr 복사
		for (int i = 0; i < MAX; i++)
		{
			for (int j = 0; j < MAX; j++)
			{
				tmp[i][j] = arr[i][j];
			}
		}

		// 첫 행에서 클릭 결정
		for (int x = 0; x < MAX; x++)
		{
			if (bit & (1 << x)) // x번째 열 클릭 시
			{
				tmp[0][x] ^= 1; // 자기 자신 토글
				// 상하좌우 토글
				for (int i = 0; i < WAY; i++)
				{
					int nx = x + dx[i];
					int ny = dy[i];
					if (nx < 0 || nx >= MAX || ny < 0 || ny >= MAX) continue;
					tmp[ny][nx] ^= 1;
				}
				cnt++; // 클릭 수 증가
			}
		}

		// 두 번째 행부터 아래로 처리
		for (int y = 1; y < MAX; y++)
		{
			for (int x = 0; x < MAX; x++)
			{
				if (tmp[y - 1][x]) // 바로 위가 켜져 있으면 클릭
				{
					tmp[y][x] ^= 1; // 자기 자신 토글
					for (int i = 0; i < WAY; i++)
					{
						int nx = x + dx[i];
						int ny = y + dy[i];
						if (nx < 0 || nx >= MAX || ny < 0 || ny >= MAX) continue;
						tmp[ny][nx] ^= 1; // 상하좌우 토글
					}
					cnt++; // 클릭 수 증가
				}
			}
		}

		// 모든 전구 꺼졌는지 확인
		bool dark = true;
		for (int y = 0; y < MAX; y++)
		{
			for (int x = 0; x < MAX; x++)
			{
				if (tmp[y][x])
				{
					dark = false; // 켜진 전구가 있으면 false
				}
			}
		}

		// 꺼졌으면 최소값 갱신
		if (dark) ans = min(ans, cnt);
	}

	// 불가능하면 -1
	if (ans == INF) ans = -1;
	cout << ans;
	return 0;
}
