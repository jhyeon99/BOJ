#include <bits/stdc++.h>
using namespace std;
const int INF = 2e9;
const int MAX = 1000;
const int COLOR = 3; // 색상 개수 (빨강, 초록, 파랑)

int cost[MAX][COLOR];           // 각 집을 색칠하는 비용
int dp[MAX][COLOR][COLOR];      // dp[i][first][last] : 0~i번째 집까지, 첫 번째 집이 first, i번째 집이 last 색일 때 최소 비용

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n; 
    cin >> n; // 집의 수

    // 각 집의 색칠 비용 입력
    for (int i = 0; i < n; i++) 
        cin >> cost[i][0] >> cost[i][1] >> cost[i][2];

    // dp 배열 초기화
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < COLOR; j++) 
            for (int k = 0; k < COLOR; k++) 
                dp[i][j][k] = INF;

    // 첫 번째 집 색 지정
    for (int k = 0; k < COLOR; k++) 
        dp[0][k][k] = cost[0][k];

    // DP 진행
    for (int i = 1; i < n; i++)
        for (int j = 0; j < COLOR; j++)         // 첫 번째 집 색
            for (int k = 0; k < COLOR; k++)     // 이전 집 색
                for (int l = 0; l < COLOR; l++) // 현재 집 색
                    if (k != l)                // 인접 집 색이 다르면
                        dp[i][j][l] = min(dp[i][j][l], dp[i - 1][j][k] + cost[i][l]);

    // 마지막 집까지 색칠 후, 첫 번째와 마지막 집 색이 다른 최소값 찾기
    int ans = INF;
    for (int j = 0; j < COLOR; j++)
        for (int k = 0; k < COLOR; k++)
            if (j != k)
                ans = min(ans, dp[n - 1][j][k]);

    cout << ans;
    return 0;
}
