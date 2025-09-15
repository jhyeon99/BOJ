#include <bits/stdc++.h>
using namespace std;
const int MAX = 500000;

int parent[MAX];  // 각 노드의 부모 노드

// Find 연산: 루트 노드를 찾고 경로 압축
int GetParent(int idx)
{
    if (parent[idx] == idx) return idx;
    return parent[idx] = GetParent(parent[idx]);
}

// Union 연산: 두 집합 합치기
void UnionParent(int a, int b)
{
    int pa = GetParent(a);
    int pb = GetParent(b);
    if (pa > pb) swap(pa, pb);  // 작은 번호를 부모로
    parent[pb] = pa;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;   // 노드 수, 간선 수
    for (int i = 0; i < n; i++) parent[i] = i;  // 초기화

    int ans = 0;  // 사이클 발생 시 간선 번호
    for (int i = 0; i < m; i++)
    {
        int u, v; cin >> u >> v;
        if (GetParent(u) == GetParent(v))  // 이미 같은 집합이면 사이클 발생
        {
            ans = i + 1;  // 현재 간선 번호 (1-based)
            break;
        }
        UnionParent(u, v);  // 집합 합치기
    }

    cout << ans;  // 사이클이 발생한 간선 번호 출력 (없으면 0)
    return 0;
}
