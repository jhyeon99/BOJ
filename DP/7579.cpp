#include <bits/stdc++.h>
using namespace std;

const int INF = 2e9;
const int MAX = 101;

int mem[MAX], cost[MAX];      // 각 앱의 메모리 사용량과 비용
int dp[MAX][MAX * MAX];       // dp[i][j] = i번째 앱까지 고려했을 때 비용 j로 얻는 최대 메모리

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, m; 
    cin >> n >> m;              // 앱 개수, 목표 메모리
    for (int i = 1; i <= n; i++) cin >> mem[i];    // 메모리
    for (int i = 1; i <= n; i++) cin >> cost[i];   // 비용

    // DP 채우기
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= 100 * n; j++)  // 최대 비용 범위
        {
            dp[i][j] = dp[i - 1][j];       // i번째 앱 사용하지 않는 경우
            if (i > 0 && j >= cost[i])     // i번째 앱을 사용할 수 있는 경우
            {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - cost[i]] + mem[i]);
            }
        }
    }

    // 최소 비용 탐색
    for (int i = 0; i <= 100 * n; i++)
    {
        if (dp[n][i] >= m)   // 목표 메모리 m 이상 달성 가능하면
        {
            cout << i;       // 최소 비용 출력
            break;
        }
    }

    return 0;
}
