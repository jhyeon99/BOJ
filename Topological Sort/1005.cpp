#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int t; cin >> t; // 테스트 케이스 수
    while (t--)
    {
        int n, k; cin >> n >> k; // n: 건물 수, k: 건물 간 규칙 수
        vector<int> d(n), par(n); // d[i]: 건물 i 건설 시간, par[i]: 진입차수
        vector<vector<int>> adj(n); // 건물 간 연결 정보 (그래프)

        for (int i = 0; i < n; i++) cin >> d[i];
        for (int i = 0; i < k; i++)
        {
            int x, y; cin >> x >> y;
            x--, y--; 
            adj[x].push_back(y); // x -> y
            par[y]++;           // y 진입차수 증가
        }

        int w; cin >> w; w--; // 목표 건물
        queue<int> q;
        vector<int> dp(n, 0); // dp[i]: i 건물까지 걸리는 최대 시간

        // 진입차수 0인 건물부터 큐에 삽입
        for (int i = 0; i < n; i++)
            if (!par[i]) q.push(i);

        // 위상정렬 + DP 진행
        while (par[w]) // 목표 건물의 진입차수가 0이 될 때까지
        {
            int curr = q.front(); q.pop();
            for (int next : adj[curr])
            {
                dp[next] = max(dp[next], dp[curr] + d[curr]); // 누적 최대 시간
                if (--par[next] == 0) q.push(next);
            }
        }

        cout << dp[w] + d[w] << '\n'; // 목표 건물 건설 완료 시간
    }

    return 0;
}