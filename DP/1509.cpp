#include <bits/stdc++.h>
using namespace std;

const int MAX = 2501;
const int INF = 1e9;

bool pal[MAX][MAX]; // pal[i][j] = str[i..j]가 팰린드롬이면 true
int dp[MAX];        // dp[i] = str[0..i-1]까지 최소 팰린드롬 분할 수

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string str;
    cin >> str;
    int n = str.size();

    // 모든 부분 문자열 팰린드롬 여부 계산
    for (int j = 0; j < n; j++) {        // 길이 j+1의 문자열
        for (int i = 0; i < n - j; i++) {
            if (str[i] == str[i + j]) {
                // 내부 부분 문자열이 팰린드롬이거나 길이가 1 또는 2이면
                if (pal[i + 1][i + j - 1] || j < 2) {
                    pal[i][i + j] = true;
                }
            }
        }
    }

    dp[0] = 0; // 공백 문자열은 분할 필요 없음
    for (int i = 1; i <= n; i++) {
        dp[i] = INF;
        for (int j = 0; j < i; j++) {
            if (pal[j][i - 1]) {       // str[j..i-1]가 팰린드롬이면
                dp[i] = min(dp[i], dp[j] + 1); // 이전 최소 + 1
            }
        }
    }

    cout << dp[n]; // 최소 팰린드롬 분할 수 출력
    return 0;
}
