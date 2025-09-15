#include <bits/stdc++.h>
using namespace std;

const int INF = 2e9;
const int MAX = 500;
int r[MAX], c[MAX];     // 각 행렬의 행(r)과 열(c)
int dp[MAX][MAX];       // dp[i][j] = i번째부터 j번째까지 행렬 곱 최소 비용

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int n; cin >> n;    // 행렬 개수
    for (int i = 0; i < n; i++) cin >> r[i] >> c[i]; // 각 행렬의 행과 열

    // 초기화: 같은 행렬끼리는 곱셈 비용 0, 나머지는 INF
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            dp[i][j] = i == j ? 0 : INF;
        }
    }

    // DP 계산: 구간 길이 k
    for (int k = 1; k < n; k++)
    {
        for (int i = 0; i < n - k; i++)
        {
            for (int j = i; j < i + k; j++)
            {
                // i~j와 j+1~i+k 행렬을 곱하는 비용 계산
                dp[i][i + k] = min(dp[i][i + k], 
                                    dp[i][j] + dp[j + 1][i + k] + r[i] * c[j] * c[i + k]);
            }
        }
    }

    cout << dp[0][n - 1]; // 전체 행렬 곱 최소 비용 출력
    return 0;
}
