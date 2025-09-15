#include <bits/stdc++.h>
using namespace std;

const int MAXN = 51;
const int MAXH = 500001;

int val[MAXN];      // 입력 값 배열
int dp[MAXN][MAXH]; // dp[i][j]: i번째까지 고려했을 때 j 상태의 최대 합

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) cin >> val[i]; // 값 입력

    int ans = -1;
    memset(dp, -1, sizeof dp);
    dp[0][0] = 0; // 초기 상태

    // DP 진행
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < MAXH; j++) {
            if (dp[i - 1][j] != -1) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j]); // 선택 안함
            }
            if (j + val[i] < MAXH && dp[i - 1][j + val[i]] != -1) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j + val[i]] + val[i]); // 한쪽에 추가
            }
            if (dp[i - 1][abs(j - val[i])] != -1) {
                dp[i][j] = max(dp[i][j], dp[i - 1][abs(j - val[i])] + max(0, val[i] - j)); // 차이 계산
            }
            if (j == 0 && dp[i][j] > 0) ans = max(ans, dp[i][j]); // 균형 상태 최대값 갱신
        }
    }

    cout << ans;
    return 0;
}
