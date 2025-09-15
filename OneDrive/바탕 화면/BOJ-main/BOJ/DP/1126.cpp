#include <bits/stdc++.h>

using namespace std;

const int MAXN = 51;
const int MAXH = 500001;

int val[MAXN];
int dp[MAXN][MAXH];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		cin >> val[i];
	}

	int ans = -1;
	memset(dp, -1, sizeof dp);
	dp[0][0] = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < MAXH; j++) {
			if (dp[i - 1][j] != -1) {
				dp[i][j] = max(dp[i][j], dp[i - 1][j]);
			}
			if (j + val[i] < MAXH && dp[i - 1][j + val[i]] != -1) {
				dp[i][j] = max(dp[i][j], dp[i - 1][j + val[i]] + val[i]);
			}
			if (dp[i - 1][abs(j - val[i])] != -1) {
				dp[i][j] = max(dp[i][j], dp[i - 1][abs(j - val[i])] + max(0, val[i] - j));
			}
			if (j == 0 && dp[i][j] > 0) {
				ans = max(ans, dp[i][j]);
			}
		}
	}
	cout << ans;
	return 0;
}