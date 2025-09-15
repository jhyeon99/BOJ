#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int MAX = 100000;
using pii = pair<int, int>;

pii e[MAX];   // 전깃줄의 좌우 위치 (A, B)
int dp[MAX];  // LIS(최장 증가 부분 수열) 저장용
int idx[MAX]; // 각 전깃줄이 LIS에서 몇 번째 위치에 있는지 저장

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n; cin >> n;

	// 전깃줄 입력
	for (int i = 0; i < n; i++)
	{
		cin >> e[i].first >> e[i].second;
	}

	// A 좌표 기준으로 정렬
	sort(e, e + n);

	// LIS 초기화
	for (int i = 0; i < n; i++) dp[i] = INF;

	// LIS 계산 (B 좌표 기준)
	for (int i = 0; i < n; i++)
	{
		int x = lower_bound(dp, dp + n, e[i].second) - dp;
		dp[x] = e[i].second; // B 좌표를 넣어 증가 부분 수열 갱신
		idx[i] = x;          // 현재 전깃줄이 LIS에서 몇 번째인지 저장
	}

	// LIS 길이 계산
	int m = lower_bound(dp, dp + n, INF) - dp - 1;
	int ans1 = n - (m + 1); // 제거해야 하는 전깃줄 개수
	cout << ans1 << '\n';

	// LIS에 포함된 전깃줄 표시
	bool ans2[MAX] = {};
	for (int i = n - 1, j = m; i >= 0; i--)
	{
		if (idx[i] == j)
		{
			ans2[i] = true; // LIS에 포함
			j--;
		}
	}

	// 제거해야 하는 전깃줄 출력
	for (int i = 0; i < n; i++)
		if (!ans2[i])
			cout << e[i].first << '\n';

	return 0;
}
