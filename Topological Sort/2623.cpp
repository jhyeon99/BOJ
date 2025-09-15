#include <bits/stdc++.h>
using namespace std;

const int MAX = 1001;
int par[MAX];                // 각 노드의 진입 차수 (부모 개수)
vector<int> child[MAX];      // 각 노드의 자식 리스트

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n, m; 
	cin >> n >> m;            // 노드 수, 순서 정보 수

	for (int i = 0; i < m; i++)
	{
		int s; cin >> s;      // 한 줄의 수열 길이
		int prev = 0;
		for (int i = 0; i < s; i++)
		{
			int curr; cin >> curr;  // 순서 정보
			if (prev)
			{
				// prev → curr 에 대한 간선이 존재하지 않으면 추가
				if (find(child[prev].begin(), child[prev].end(), curr) == child[prev].end())
				{
					par[curr]++;          // curr의 진입 차수 증가
					child[prev].push_back(curr);
				}
			}
			prev = curr;  // 이전 노드 갱신
		}
	}

	queue<int> q;
	vector<int> ans;

	// 진입 차수가 0인 노드를 큐에 넣기
	for (int i = 1; i <= n; i++) if (!par[i]) q.push(i);

	// 위상 정렬 수행
	while (q.size())
	{
		int curr = q.front(); q.pop();
		ans.push_back(curr);       // 순서에 추가
		for (int next : child[curr])
			if (!--par[next]) q.push(next);  // 진입 차수 감소 후 0이면 큐에 삽입
	}

	// 모든 노드가 포함되었는지 확인
	if (ans.size() == n) 
		for (int a : ans) cout << a << '\n';
	else 
		cout << 0;  // 순서를 정할 수 없는 경우
	return 0;
}
