#include <bits/stdc++.h>
using namespace std;

const int MAX = 10001;

vector<int> adj[MAX];    // 원래 그래프
vector<int> rev[MAX];    // 역방향 그래프
vector<int> scc[MAX];    // SCC 결과 저장
vector<int> dfn;         // DFS 완료 순서 저장
bool vst[MAX];           // 방문 여부
int num[MAX];            // SCC 번호

// 일반 DFS: 각 정점을 끝까지 탐색하고 종료 시 순서를 dfn에 저장
void DFS(int v) {
    vst[v] = true;
    for (int u : adj[v]) {
        if (!vst[u]) DFS(u);
    }
    dfn.push_back(v);
}

// 역방향 DFS: 현재 정점과 연결된 정점을 모두 탐색하여 같은 SCC 번호를 부여
void RevDFS(int v, int number) {
    vst[v] = true;
    num[v] = number;
    for (int u : rev[v]) {
        if (!vst[u]) RevDFS(u, number);
    }
}

// Kosaraju 알고리즘으로 SCC 찾기
int GetSCC(int v) {
    memset(vst, 0, sizeof vst);

    // 1. 일반 DFS로 종료 순서 기록
    for (int i = 1; i <= v; i++) {
        if (!vst[i]) DFS(i);
    }

    // 2. 방문 초기화 및 종료 순서 역순으로 DFS
    memset(vst, 0, sizeof vst);
    reverse(dfn.begin(), dfn.end());
    int ret = 0;

    for (int i : dfn) {
        if (!vst[i]) RevDFS(i, ret++);
    }

    // 3. SCC 번호 정리 및 각 SCC에 속한 정점 저장
    int cnv[MAX], cnt = 0;
    for (int i = 0; i < ret; i++) cnv[i] = -1;

    for (int i = 1; i <= v; i++) {
        if (cnv[num[i]] == -1) cnv[num[i]] = cnt++;
        scc[cnv[num[i]]].push_back(i);
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int v, e;
    cin >> v >> e;

    // 그래프 입력
    for (int i = 0; i < e; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        rev[b].push_back(a);
    }

    int ret = GetSCC(v);

    cout << ret << '\n';

    // 각 SCC 출력 (-1로 종료)
    for (int i = 0; i < ret; i++) {
        sort(scc[i].begin(), scc[i].end());
        for (int j : scc[i]) cout << j << ' ';
        cout << -1 << '\n';
    }

    return 0;
}
