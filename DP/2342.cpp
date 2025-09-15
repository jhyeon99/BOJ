#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;       // 충분히 큰 값
const int MAX = 100000;    // 입력 수열 최대 길이
const int STATE = 5;       // 상태 수 (0~4, 문제에 따른 상태)

int s[MAX];                // 입력 수열
int dp[MAX][STATE];        // dp[i][j] : i번째까지 연주 후 상태 j로 끝나는 최소 비용

// 상태 전환 비용 계산 함수
int W(int f, int t)
{
	if (f == t) return 1;             // 같은 손가락이면 비용 1
	else if (f == 0) return 2;        // 시작 상태(손가락 없음) -> 비용 2
	else if ((f & 1) ^ (t & 1)) return 3; // 손가락 홀짝 바뀌면 비용 3
	else return 4;                     // 그 외의 경우 비용 4
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	int n = 0;
	// 입력 받기 (0이 나오면 종료)
	while (true)
	{
		cin >> s[n];
		if (!s[n]) break;
		n++;
	}

	// dp 초기화: INF로 초기화
	for (int i = 0; i < n; i++) fill_n(dp[i], STATE, INF);

	dp[0][0] = 2; // 첫 번째 상태 초기값

	// dp 수행
	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < STATE; j++)
		{
			// 이전 상태 j에서 현재 s[i]로 올 때 최소값 갱신
			dp[i][j] = min(dp[i][j], dp[i - 1][j] + W(s[i - 1], s[i]));

			// 이전 상태가 현재 손가락이 아니면, 이전 상태를 s[i-1]로 바꾸고 최소값 갱신
			if (s[i - 1] != j)
				dp[i][s[i - 1]] = min(dp[i][s[i - 1]], dp[i - 1][j] + W(j, s[i]));
		}
	}

	// 마지막 위치에서 최소값 계산
	int ans = INF;
	for (int i = 0; i < STATE; i++) ans = min(ans, dp[n - 1][i]);

	cout << ans;

	return 0;
}
