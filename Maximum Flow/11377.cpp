#include <bits/stdc++.h>
using namespace std;

const int MAX = 2003;
const int INF = 1e9;

vector<int> adj[MAX];      // 인접 리스트
int capacity[MAX][MAX];    // 각 간선 용량
int flow[MAX][MAX];        // 현재 유량

// BFS 기반 최대 유량 계산 (Edmonds-Karp)
int MaximumFlow(int source, int sink)
{
    int total_flow = 0;
    while (true)
    {
        vector<int> parent(MAX, -1); // 경로 추적용 부모 배열
        queue<int> q;
        parent[source] = source;
        q.push(source);

        // 증강 경로 탐색
        while (!q.empty() && parent[sink] == -1)
        {
            int here = q.front(); q.pop();
            for (int there : adj[here])
            {
                // 남은 용량이 존재하고 아직 방문하지 않았다면
                if (capacity[here][there] - flow[here][there] > 0 && parent[there] == -1)
                {
                    q.push(there);
                    parent[there] = here;
                }
            }
        }

        if (parent[sink] == -1) // 더 이상 증강 경로 없음
            break;

        // 경로 상 최소 용량 찾기
        int amount = INF;
        for (int p = sink; p != source; p = parent[p])
            amount = min(capacity[parent[p]][p] - flow[parent[p]][p], amount);

        // 유량 갱신
        for (int p = sink; p != source; p = parent[p])
        {
            flow[parent[p]][p] += amount;
            flow[p][parent[p]] -= amount;
        }

        total_flow += amount; // 전체 유량 증가
    }
    return total_flow;
}

// 간선 추가
void AddEdge(int u, int v, int w)
{
    adj[u].push_back(v);
    adj[v].push_back(u); // 역방향 간선도 추가 (잔여 그래프)
    capacity[u][v] = w;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m, k; 
    cin >> n >> m >> k; // n: 왼쪽 노드 수, m: 오른쪽 노드 수, k: 특별 용량

    int source = 0, bridge = 1, sink = n + m + 2;
    AddEdge(source, bridge, k); // source -> bridge (특수 용량)

    // 왼쪽 노드와 bridge 연결
    for (int i = 2; i < n + 2; i++)
    {
        AddEdge(source, i, 1);
        AddEdge(bridge, i, 1);
        int t; cin >> t; // i번째 노드가 연결할 오른쪽 노드 수
        while (t--)
        {
            int j; cin >> j;
            j += n + 1; // 오른쪽 노드 인덱스 조정
            AddEdge(i, j, 1); // 왼쪽 노드 -> 오른쪽 노드
        }
    }

    // 오른쪽 노드 -> sink 연결
    for (int i = n + 2; i < n + m + 2; i++)
    {
        AddEdge(i, sink, 1);
    }

    cout << MaximumFlow(source, sink); // 최대 유량 출력
    return 0;
}
