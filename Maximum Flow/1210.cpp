#include <bits/stdc++.h>
using namespace std;

const int MAX = 400;
const int INF = 1e9;

int capacity[MAX][MAX]; // 정점/간선 용량
int flow[MAX][MAX];     // 현재 유량

// 정점 분할: in/out 노드로 변환
inline int In(int i) { return i << 1; }      // i번째 정점의 in 노드
inline int Out(int i) { return i << 1 | 1; } // i번째 정점의 out 노드

// 최대 유량 계산 (Edmonds-Karp)
int MaximumFlow(int source, int sink)
{
    int total_flow = 0;
    while (true)
    {
        vector<int> parent(MAX, -1);
        queue<int> q;
        parent[source] = source;
        q.push(source);

        // BFS로 증강 경로 탐색
        while (!q.empty() && parent[sink] == -1)
        {
            int here = q.front(); q.pop();
            for (int there = 0; there < MAX; there++)
            {
                if (capacity[here][there] - flow[here][there] > 0 && parent[there] == -1)
                {
                    q.push(there);
                    parent[there] = here;
                }
            }
        }

        if (parent[sink] == -1) break; // 증강 경로 없음

        // 경로 상 최소 용량 계산
        int amount = INF;
        for (int p = sink; p != source; p = parent[p])
            amount = min(capacity[parent[p]][p] - flow[parent[p]][p], amount);

        // 경로 상 유량 갱신
        for (int p = sink; p != source; p = parent[p])
        {
            flow[parent[p]][p] += amount;
            flow[p][parent[p]] -= amount;
        }

        total_flow += amount;
    }
    return total_flow;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    int source, sink; cin >> source >> sink;
    source--, sink--;

    // 정점 용량 입력
    for (int i = 0; i < n; i++)
    {
        int w; cin >> w;
        capacity[In(i)][Out(i)] = w; // in->out으로 정점 용량 설정
    }

    // 간선 연결 (무한 용량)
    for (int i = 0; i < m; i++)
    {
        int u, v; cin >> u >> v;
        u--; v--;
        capacity[Out(u)][In(v)] = capacity[Out(v)][In(u)] = INF;
    }

    MaximumFlow(In(source), Out(sink));

    // 최소 컷 정점 찾기
    vector<int> parent(MAX, -1);
    queue<int> q;
    parent[In(source)] = In(source);
    q.push(In(source));
    while (!q.empty())
    {
        int here = q.front(); q.pop();
        for (int there = 0; there < MAX; there++)
        {
            if (capacity[here][there] - flow[here][there] > 0 && parent[there] == -1)
            {
                q.push(there);
                parent[there] = here;
            }
        }
    }

    // 최소 컷에 속한 정점 출력
    for (int i = 0; i < 2 * n; i += 2)
    {
        if (parent[i] != -1 && parent[i + 1] == -1)
            cout << (i >> 1) + 1 << ' ';
    }

    return 0;
}
