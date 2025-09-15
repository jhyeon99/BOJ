#include <bits/stdc++.h>
using namespace std;

const int MAX = 501;       // 최대 정점 수
const int INF = 1e9;       // 무한대 값
int capacity[MAX][MAX], flow[MAX][MAX]; // capacity: 용량, flow: 현재 흐름
vector<int> adj[MAX];      // 인접 리스트

// 최대 유량 계산 (Edmonds-Karp 알고리즘, BFS 기반)
int MaximumFlow(int source, int sink)
{
	int total_flow = 0; // 총 유량 초기화
	while (true)
	{
		vector<int> parent(MAX, -1); // 경로 추적용 부모 배열
		queue<int> q;
		parent[source] = source; // 시작점 표시
		q.push(source);

		// BFS로 증대 경로 찾기
		while (!q.empty() && parent[sink] == -1)
		{
			int here = q.front(); q.pop();
			for (int there = 0; there < MAX; there++)
			{
				// 남은 용량이 있고 방문하지 않았다면
				if (capacity[here][there] - flow[here][there] > 0 && parent[there] == -1)
				{
					q.push(there);
					parent[there] = here; // 경로 기록
				}
			}
		}

		if (parent[sink] == -1) // 증대 경로가 없으면 종료
			break;

		// 최소 용량 찾기
		int amount = INF;
		for (int p = sink; p != source; p = parent[p])
			amount = min(capacity[parent[p]][p] - flow[parent[p]][p], amount);

		// 유량 갱신
		for (int p = sink; p != source; p = parent[p])
		{
			flow[parent[p]][p] += amount;
			flow[p][parent[p]] -= amount; // 역방향 유량 처리
		}

		total_flow += amount; // 총 유량 증가
	}
	return total_flow;
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n, m; cin >> n >> m; // 정점 수, 간선 수 입력

	for (int i = 0; i < m; i++)
	{
		int u, v, w; cin >> u >> v >> w; // 간선 정보: u->v, 용량 w
		capacity[u][v] = capacity[v][u] += w; // 용량 저장 (양방향)
		adj[u].push_back(v);
		adj[v].push_back(u); // 인접 리스트 업데이트
	}

	int source, sink; cin >> source >> sink; // 시작점과 종료점
	cout << MaximumFlow(source, sink);       // 최대 유량 출력
	return 0;
}
