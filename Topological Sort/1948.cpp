#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

const int MAX = 10001;
vector<pii> adj[MAX], invadj[MAX]; // adj: 정방향 그래프, invadj: 역방향 그래프
int par[MAX];        // 각 노드의 진입 차수
int dist[MAX];       // 시작점에서 각 노드까지의 최장 거리
bool vst[MAX];       // 역방향 BFS 방문 체크

int main()
{
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);

    int n, m; 
    cin >> n >> m; // 노드, 간선 수

    for (int i = 0; i < m; i++)
    {
        int u, v, w; 
        cin >> u >> v >> w; // u->v 가중치 w
        adj[u].push_back({w, v});
        par[v]++;                  // 진입 차수 증가
        invadj[v].push_back({w, u}); // 역방향 그래프
    }

    int s, e; 
    cin >> s >> e; // 시작점, 종료점

    // ---------- 위상정렬로 최장 경로 계산 ----------
    queue<int> q;
    q.push(s);

    while (!q.empty())
    {
        int curr = q.front(); q.pop();
        for (pii p : adj[curr])
        {
            int next = p.second;
            int w = p.first;
            dist[next] = max(dist[next], dist[curr] + w); // 최장 거리 갱신
            if (--par[next] == 0) q.push(next);
        }
    }

    int maxDist = dist[e]; // 최종 최대 거리

    // ---------- 역방향 BFS로 최장 경로에 속한 간선 수 계산 ----------
    int criticalEdges = 0;
    queue<int> q2;
    q2.push(e);

    while (!q2.empty())
    {
        int curr = q2.front(); q2.pop();
        for (pii p : invadj[curr])
        {
            int w = p.first;
            int prev = p.second;
            // 최장 경로에 포함된 간선 확인
            if (dist[curr] == dist[prev] + w)
            {
                criticalEdges++;
                if (!vst[prev])
                {
                    vst[prev] = true;
                    q2.push(prev);
                }
            }
        }
    }

    cout << maxDist << '\n' << criticalEdges;
    return 0;
}
