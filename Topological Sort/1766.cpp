#include <bits/stdc++.h>
using namespace std;

const int MAX = 32001;
int parent[MAX];          // 각 노드의 진입 차수(in-degree)
vector<int> child[MAX];   // 인접 리스트: 해당 노드에서 나가는 간선

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, m; 
    cin >> n >> m; // n: 노드 개수, m: 간선 개수

    // 그래프 입력
    for (int i = 0; i < m; i++)
    {
        int a, b; 
        cin >> a >> b;   // a -> b
        child[a].push_back(b);
        parent[b]++;     // 진입 차수 증가
    }

    // 최소 힙(priority_queue) 사용: 사전 순 처리
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 1; i <= n; i++)
    {
        if (parent[i] == 0) pq.push(i); // 진입 차수 0인 노드 큐에 삽입
    }

    // 위상 정렬 수행
    while (!pq.empty())
    {
        int curr = pq.top(); 
        pq.pop();
        cout << curr << ' '; // 현재 노드 출력

        for (int next : child[curr])
        {
            parent[next]--;   // 진입 차수 감소
            if (parent[next] == 0) // 더 이상 선행 노드가 없으면
            {
                pq.push(next);
            }
        }
    }

    return 0;
}
