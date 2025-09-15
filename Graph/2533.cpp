#include <bits/stdc++.h>
using namespace std;

const int MAX = 1000001;
vector<int> adj[MAX];  // 트리 인접리스트
bool vst[MAX];         // 방문 체크
int dp[MAX][2];        // dp[node][0] = node를 선택하지 않았을 때, dp[node][1] = node를 선택했을 때

// DFS 기반 트리 DP
void DFS(int curr)
{
	vst[curr] = true;
	dp[curr][0] = 0; // 현재 노드를 선택하지 않은 경우
	dp[curr][1] = 1; // 현재 노드를 선택한 경우 (자기 자신 포함)

	for (int next : adj[curr])
	{
		if (vst[next]) continue;
		DFS(next);

		// 현재 노드를 선택하지 않았다면, 자식 노드는 반드시 선택되어야 함
		dp[curr][0] += dp[next][1];

		// 현재 노드를 선택했다면, 자식 노드는 선택 여부 자유 (최소값 선택)
		dp[curr][1] += min(dp[next][0], dp[next][1]);
	}
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n; cin >> n;

	// 트리 간선 입력
	for (int i = 0; i < n - 1; i++)
	{
		int u, v; cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	DFS(1); // 루트 노드 1부터 DFS 수행

	// 루트 노드 선택 여부 중 최소값 출력
	cout << min(dp[1][0], dp[1][1]);
	return 0;
}
