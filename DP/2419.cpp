#include <bits/stdc++.h>
using namespace std;

const int MAX = 301;
const int INF = 1e9;

int n, m;                    // n: 점 개수, m: 반복 횟수
int pos[MAX];                // 점의 위치 배열
int zero;                     // 위치 0이 들어있는 인덱스
int dp[MAX][MAX][2];          // DP 배열: dp[l][r][state] = 왼쪽 l, 오른쪽 r, 현재 위치 상태
int ans;                      // 최종 답

// l: 왼쪽 인덱스, r: 오른쪽 인덱스, state: 현재 위치(0=왼쪽, 1=오른쪽), rpt: 남은 이동 횟수
int Rec(int l, int r, int state, int rpt)
{
	if (!rpt) return 0; // 더 이상 이동할 횟수가 없으면 0

	int& ret = dp[l][r][state];
	if (ret != -1) return ret; // 이미 계산한 값이 있으면 반환

	ret = INF;
	int prev = !state ? pos[l] : pos[r]; // 현재 위치

	// 왼쪽으로 이동 가능하면 계산
	if (l - 1 >= 0)
		ret = min(ret, rpt * (prev - pos[l - 1]) + Rec(l - 1, r, 0, rpt - 1));

	// 오른쪽으로 이동 가능하면 계산
	if (r + 1 < n)
		ret = min(ret, rpt * (pos[r + 1] - prev) + Rec(l, r + 1, 1, rpt - 1));

	return ret;
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	cin >> n >> m;
	bool isZero = false;

	// 점 위치 입력
	for (int i = 0; i < n; i++) cin >> pos[i];

	// 0 위치 추가
	pos[n++] = 0;

	// 점들을 오름차순으로 정렬
	sort(pos, pos + n);

	// 0이 있는 인덱스 찾기
	zero = lower_bound(pos, pos + n, 0) - pos;

	// 이동 횟수 i에 대한 최대 값 계산
	for (int i = 0; i < n; i++)
	{
		memset(dp, -1, sizeof dp); // DP 초기화
		ans = max(ans, m * i - Rec(zero, zero, 0, i)); // 최대값 갱신
	}

	cout << ans;
	return 0;
}
