#include <bits/stdc++.h>
using namespace std;

const int INF = 2e9;
const int MAX = 1000000;

int arr[MAX]; // 입력 수열
int dp[MAX];  // dp[i]: 길이가 i+1인 증가하는 부분 수열의 마지막 값 최솟값

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; 
    cin >> n; // 수열 길이

    for (int i = 0; i < n; i++) cin >> arr[i]; // 수열 입력

    // dp 초기화: INF로 채움
    for (int i = 0; i < n; i++) dp[i] = INF;

    // 각 원소를 적절한 위치에 삽입하여 LIS 길이 갱신
    for (int i = 0; i < n; i++)
    {
        // arr[i]가 들어갈 위치 찾기 (lower_bound)
        int idx = lower_bound(dp, dp + n, arr[i]) - dp;
        dp[idx] = arr[i];
    }

    // INF보다 작은 dp의 개수가 LIS 길이
    cout << lower_bound(dp, dp + n, INF) - dp;
    return 0;
}
