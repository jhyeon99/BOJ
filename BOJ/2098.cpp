#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;
const int MAX = 16;

int n;
int w[MAX][MAX];
int dp[MAX][1 << MAX];

int DFS(int curr, int vst)
{
	if (vst == (1 << n) - 1) {
		if (!w[curr][0]) {
			return INF;
		}
		return w[curr][0];
	}

	int& ret = dp[curr][vst];
	if (ret != -1) {
		return ret;
	}
	ret = INF;
	for (int next = 0; next < n; next++) {
		if (!w[curr][next] || vst & 1 << next) {
			continue;
		}
		ret = min(ret, DFS(next, vst | 1 << next) + w[curr][next]);
	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> w[i][j];
		}
	}

	memset(dp, -1, sizeof(dp));
	cout << DFS(0, 1);

	return 0;
}