#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

const int MAX = 101;
const int WAY = 4;
const int dy[WAY] = { -1, 1, 0, 0 }, dx[WAY] = { 0, 0, 1, -1 }; // 상, 하, 우, 좌

int r, c, m;                     // 격자 크기 (r행 c열), 상어 수 m
int sz[MAX][MAX], idx[MAX][MAX];  // sz: 해당 칸 상어 크기, idx: 상어 인덱스

struct Shark
{
	int y, x, s, d, z;  // 좌표(y,x), 속력 s, 방향 d, 크기 z

	Shark() {}

	// 상어 이동
	void Move()
	{
		if (d <= 2) // 상하 이동
		{
			int w = d == 1 ? 1 : r; // 방향에 따라 끝 칸 결정
			if (s <= abs(y - w)) // 끝까지 못감
			{
				y += dy[d - 1] * s;
			}
			else if (s <= abs(y - w) + (r - 1)) // 반사 후 이동
			{
				d = (d - 1 ^ 1) + 1; // 방향 반전
				y = w + dy[d - 1] * (s - (abs(y - w)));
			}
			else // 여러 번 반사
			{
				y -= dy[d - 1] * (2 * (r - 1) - s);
			}
		}
		else // 좌우 이동
		{
			int w = d == 3 ? c : 1;
			if (s <= abs(x - w))
			{
				x += dx[d - 1] * s;
			}
			else if (s <= abs(x - w) + (c - 1))
			{
				d = (d - 1 ^ 1) + 1;
				x = w + dx[d - 1] * (s - (abs(x - w)));
			}
			else
			{
				x -= dx[d - 1] * (2 * (c - 1) - s);
			}
		}
	}
};

vector<Shark> shark; // 상어 정보 저장

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	cin >> r >> c >> m;

	// 상어 정보 입력
	for (int i = 0; i < m; i++)
	{
		Shark s;
		cin >> s.y >> s.x >> s.s >> s.d >> s.z;

		// 반복 이동 최적화 (속도를 격자 크기 기준으로 나머지 처리)
		s.s %= ((s.d <= 2 ? r : c) - 1) * 2;
		shark.push_back(s);
	}

	int ans = 0;

	// 낚시왕 이동 (1열부터 c열까지)
	for (int k = 1; k <= c; k++)
	{
		memset(sz, 0, sizeof(sz));   // 각 칸 상어 크기 초기화
		memset(idx, 0, sizeof(idx));  // 각 칸 상어 인덱스 초기화
		vector<int> era;              // 제거할 상어 인덱스

		// 상어 격자 배치 및 크기 비교
		for (int i = 0; i < shark.size(); i++)
		{
			if (!sz[shark[i].y][shark[i].x]) // 빈 칸이면
			{
				sz[shark[i].y][shark[i].x] = shark[i].z;
				idx[shark[i].y][shark[i].x] = i;
			}
			else // 이미 상어가 존재하면
			{
				if (sz[shark[i].y][shark[i].x] > shark[i].z) // 기존 상어가 더 크면
					era.push_back(i);
				else // 새 상어가 더 크면
				{
					era.push_back(idx[shark[i].y][shark[i].x]);
					sz[shark[i].y][shark[i].x] = shark[i].z;
					idx[shark[i].y][shark[i].x] = i;
				}
			}
		}

		// 낚시왕이 잡는 상어 처리 (가장 위쪽 상어)
		for (int j = 1; j <= r; j++)
		{
			if (sz[j][k])
			{
				ans += sz[j][k];           // 크기 합산
				era.push_back(idx[j][k]);  // 제거할 상어 목록에 추가
				break;
			}
		}

		// 제거할 상어 삭제 (큰 인덱스부터 삭제해야 안전)
		sort(era.begin(), era.end(), greater<>());
		for (int i = 0; i < era.size(); i++)
			shark.erase(shark.begin() + era[i]);

		// 상어 이동
		for (int i = 0; i < shark.size(); i++)
			shark[i].Move();
	}

	cout << ans;
	return 0;
}
