#include <bits/stdc++.h>
using namespace std;

const int INF = 2e9;       // 충분히 큰 값
const int MAX = 1000000;   // 최대 배열 크기
int arr[MAX], dp[MAX], idx[MAX]; // arr: 입력 배열, dp: LIS 끝값 저장, idx: 각 원소의 dp 인덱스 저장

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n; 
	cin >> n; // 배열 길이 입력
	for (int i = 0; i < n; i++) cin >> arr[i]; // 배열 값 입력

	for (int i = 0; i < n; i++) dp[i] = INF; // dp 배열 초기화

	for (int i = 0; i < n; i++)
	{
		int x = lower_bound(dp, dp + n, arr[i]) - dp; // arr[i]가 들어갈 dp 위치 탐색
		dp[x] = arr[i];   // dp 갱신
		idx[i] = x;       // 원소 i가 dp에서 몇 번째 위치인지 저장
	}

	int a1 = lower_bound(dp, dp + n, INF) - dp; // LIS 길이 계산
	cout << a1 << '\n';

	vector<int> a2;
	for (int i = n - 1, j = a1 - 1; i >= 0; i--) // LIS 구성 원소 추적
	{
		if (idx[i] == j)
		{
			a2.push_back(i); // 해당 인덱스 저장
			j--;             // 다음 위치 탐색
		}
	}

	reverse(a2.begin(), a2.end()); // 원래 순서로 복원
	for (int a : a2) cout << arr[a] << ' '; // LIS 출력
	return 0;
}
