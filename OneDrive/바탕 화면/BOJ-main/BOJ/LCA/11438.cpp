#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100001; // 최대 노드 수
const int MAXK = 17;     // 2^17 > 100000, 이진 상승을 위한 최대 깊이
vector<int> adj[MAXN];   // 트리 인접 리스트
int depth[MAXN];          // 각 노드의 깊이
int parent[MAXN][MAXK];   // parent[i][k] : 노드 i의 2^k 번째 조상

// DFS를 통해 깊이와 1단계 부모 설정
void DFS(int curr)
{
	for (int next : adj[curr])
	{
		if (depth[next] == -1) // 방문하지 않은 노드이면
		{
			depth[next] = depth[curr] + 1; // 깊이 설정
			parent[next][0] = curr;        // 1단계 부모 설정
			DFS(next);
		}
	}
}

// 두 노드 u, v의 최소 공통 조상(LCA) 계산
int LCA(int u, int v)
{
	if (depth[u] < depth[v])
		swap(u, v); // 항상 u가 깊이가 더 깊게

	int diff = depth[u] - depth[v]; // 깊이 차이
	for (int k = 0; diff > 0; k++)
	{
		if (diff & 1) u = parent[u][k]; // 2^k 단계씩 올라가기
		diff >>= 1;
	}

	if (u != v)
	{
		// 이진 상승으로 공통 조상 찾기
		for (int k = MAXK - 1; k >= 0; k--)
		{
			if (parent[u][k] != -1 && parent[u][k] != parent[v][k])
			{
				u = parent[u][k];
				v = parent[v][k];
			}
		}
		u = parent[u][0]; // 마지막 부모가 LCA
	}
	return u;
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n; cin >> n; // 노드 수
	for (int i = 0; i < n - 1; i++)
	{
		int u, v; cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	// 초기화
	memset(depth, -1, sizeof depth);
	memset(parent, -1, sizeof parent);

	depth[1] = 0; // 루트 노드 깊이 0
	DFS(1);       // DFS로 깊이와 부모 설정

	// 이진 상승 테이블 구축
	for (int k = 1; k < MAXK; k++)
	{
		for (int curr = 2; curr <= n; curr++)
		{
			if (parent[curr][k - 1] != -1)
				parent[curr][k] = parent[parent[curr][k - 1]][k - 1];
		}
	}

	int m; cin >> m; // 쿼리 수
	for (int i = 0; i < m; i++)
	{
		int u, v; cin >> u >> v;
		cout << LCA(u, v) << '\n'; // LCA 출력
	}

	return 0;
}
