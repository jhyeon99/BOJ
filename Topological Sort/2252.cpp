#include <bits/stdc++.h>
using namespace std;

const int MAX = 32001;

// 각 노드의 부모 개수
int parCnt[MAX];

// 각 노드의 자식 노드 목록
vector<int> child[MAX];

int main()
{
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL);

	int n, m;
	cin >> n >> m; // 노드 개수와 간선 개수 입력

	// 그래프 입력
	for (int i = 0; i < m; i++)
	{
		int a, b; 
		cin >> a >> b; // a -> b
		parCnt[b]++;    // b의 부모 개수 증가
		child[a].push_back(b); // a의 자식 목록에 b 추가
	}

	queue<int> q;

	// 부모가 없는 노드를 큐에 삽입 (진입차수 0)
	for (int i = 1; i <= n; i++) 
		if (!parCnt[i]) q.push(i);

	// 위상 정렬 시작
	while (q.size())
	{
		int curr = q.front(); 
		q.pop();
		cout << curr << ' '; // 현재 노드 출력

		// 현재 노드의 자식 노드 처리
		for (int next : child[curr])
		{
			parCnt[next]--; // 부모 개수 감소
			if (!parCnt[next]) // 부모가 모두 처리되었으면 큐에 삽입
			{
				q.push(next);
			}
		}
	}

	return 0;
}
