#include <bits/stdc++.h>
using namespace std;

const int MAXV = 20000;
const int MAXE = 5;   // 최대 인접 간선 수
const int INF = 1e9;

int capacity[MAXV][MAXE]; // 정점/간선 용량
int flow[MAXV][MAXE];     // 현재 유량
vector<int> adj[MAXV];    // 인접 리스트

// 최대 유량 계산 (Edmonds-Karp)
int MaximumFlow(int source, int sink)
{
    int total_flow = 0;
    while (true)
    {
        vector<int> parent(MAXV, -1);
        vector<int> parentI(MAXV, -1); // 부모 노드에서 어떤 간선을 사용했는지
        queue<int> q;
        parent[source] = source;
        q.push(source);

        // BFS로 증강 경로 탐색
        while (!q.empty() && parent[sink] == -1)
        {
            int here = q.front(); q.pop();
            for (int i = 0; i < adj[here].size(); i++)
            {
                int there = adj[here][i];
                if (capacity[here][i] - flow[here][i] > 0 && parent[there] == -1)
                {
                    q.push(there);
                    parent[there] = here;
                    parentI[there] = i;
                }
            }
        }

        if (parent[sink] == -1) break; // 증강 경로 없음

        // 경로 상 최소 용량 계산
        int amount = INF;
        for (int p = sink; p != source; p = parent[p])
            amount = min(capacity[parent[p]][parentI[p]] - flow[parent[p]][parentI[p]], amount);

        // 경로 상 유량 갱신
        for (int p = sink; p != source; p = parent[p])
        {
            flow[parent[p]][parentI[p]] += amount;
            // 역방향 유량 갱신
            int i; 
            for (i = 0; i < adj[p].size(); i++) if (adj[p][i] == parent[p]) break;
            flow[p][i] -= amount;
        }

        total_flow += amount;
    }
    return total_flow;
}

// 격자 맵
char c[MAXV >> 1][MAXV >> 1];
int di[4] = { -1, 1, 0, 0 }, dj[4] = { 0, 0, -1, 1 };

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;

    for (int i = 0; i < n; i++)
    {
        cin.ignore();
        for (int j = 0; j < m; j++)
            cin >> c[i][j]; // 격자 입력 ('#': 벽, 'K': 출발, 'H': 도착)
    }

    int source, sink;

    // 정점 분할 및 간선 설정
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (c[i][j] == '#') continue;
            int currIn = 2 * (i * m + j);
            int currOut = 2 * (i * m + j) + 1;
            if (c[i][j] == 'K') source = currOut;
            if (c[i][j] == 'H') sink = currIn;

            // 정점 용량 설정 (in -> out)
            capacity[currIn][adj[currIn].size()] = 1;
            adj[currIn].push_back(currOut);
            adj[currOut].push_back(currIn);

            // 4방향 이동 간선 (무한 용량)
            for (int k = 0; k < 4; k++)
            {
                int ni = i + di[k], nj = j + dj[k];
                if (ni < 0 || ni >= n || nj < 0 || nj >= m) continue;
                if (c[ni][nj] == '#') continue;

                int nextIn = 2 * (ni * m + nj);
                int nextOut = 2 * (ni * m + nj) + 1;
                capacity[currOut][adj[currOut].size()] = INF;
                adj[currOut].push_back(nextIn);
                adj[nextIn].push_back(currOut);
            }
        }
    }

    // 출발과 도착이 바로 연결되어 있으면 -1
    for (int next : adj[source])
    {
        if (next == sink)
        {
            cout << -1;
            return 0;
        }
    }

    cout << MaximumFlow(source, sink);
    return 0;
}
