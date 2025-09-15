#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX = 17;
int n, h;                    // n: 노드 개수, h: 루트 노드
vector<int> adj[100000];      // 인접 리스트
bool vst[100000];             // 방문 체크
vector<int> leaf;             // 리프 노드 저장

// DFS 탐색 함수
void DFS(int curr)
{
    for (int next : adj[curr])
    {
        if (!vst[next])
        {
            vst[next] = true; // 방문 처리
            DFS(next);        // 재귀 호출
        }
    }
    // 현재 노드가 리프 노드인 경우
    if (adj[curr].size() == 1)
    {
        leaf.push_back(curr);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> h;           // 노드 수와 루트 입력
    for (int i = 0; i < n - 1; i++)
    {
        int u, v; cin >> u >> v;
        adj[u].push_back(v); // 양방향 연결
        adj[v].push_back(u);
    }

    vst[h] = true;           // 루트 방문 처리
    DFS(h);                  // DFS 시작

    int s = (leaf.size() + 1) / 2; // 리프 노드 쌍 개수
    cout << s << '\n';
    for (int i = 0; i < s; i++)
    {
        // 앞쪽 절반과 뒤쪽 절반 리프를 쌍으로 출력
        cout << leaf[i] << ' ' << leaf[leaf.size() / 2 + i] << '\n';
    }
    return 0;
}
