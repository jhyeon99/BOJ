#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int MAX = 16;

int n;                 // 도시 수
int w[MAX][MAX];       // w[i][j] = i에서 j로 이동하는 비용
int dp[MAX][1 << MAX]; // dp[curr][vst] = 현재 도시 curr, 방문한 도시 집합 vst일 때 최소 비용

// -------------------------- DFS + 비트마스크 DP --------------------------
int DFS(int curr, int vst)
{
    // 모든 도시를 방문했을 경우, 시작점으로 돌아가는 비용 반환
    if (vst == (1 << n) - 1) {
        if (!w[curr][0]) return INF; // 시작점으로 가는 경로가 없으면 INF
        return w[curr][0];
    }

    int& ret = dp[curr][vst];
    if (ret != -1) return ret; // 이미 계산한 상태면 바로 반환

    ret = INF;
    for (int next = 0; next < n; next++) {
        // 갈 수 없는 경로나 이미 방문한 도시는 건너뜀
        if (!w[curr][next] || (vst & (1 << next))) continue;

        // 다음 도시 방문 후 비용 갱신
        ret = min(ret, DFS(next, vst | (1 << next)) + w[curr][next]);
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> w[i][j];

    memset(dp, -1, sizeof(dp));

    // 0번 도시에서 시작, 0번 도시 방문 처리
    cout << DFS(0, 1);
