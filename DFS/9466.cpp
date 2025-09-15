#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int MAX = 100001;

int s[MAX];      // 각 노드가 가리키는 노드 (1-indexed)
int dep[MAX];    // DFS에서 현재 노드까지의 깊이
bool vst[MAX];   // 방문 여부
int ans;         // 최종 결과: 사이클 제외 후 남은 노드 수

// DFS로 사이클 탐색 및 제외할 노드 계산
void DFS(int curr, int depth)
{
    dep[curr] = depth;       // 현재 깊이 저장
    int next = s[curr];      // 다음 노드
    
    if (!vst[next])          // 방문하지 않은 경우
    {
        vst[next] = true;
        DFS(next, depth + 1);
    }
    else if (dep[next] != INF)  // 사이클 발견
    {
        // 사이클에 포함된 노드 수만큼 ans에서 제외
        ans -= depth + 1 - dep[next];
    }
    
    dep[curr] = INF;  // DFS 종료 후 깊이 초기화
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int t; cin >> t;  // 테스트 케이스 수
    while (t--)
    {
        int n; cin >> n;
        for (int i = 1; i <= n; i++) cin >> s[i];  // 각 노드가 가리키는 노드 입력

        // 초기화
        for (int i = 1; i <= n; i++)
        {
            dep[i] = 0;
            vst[i] = false;
        }
        
        ans = n;  // 초기값: 모든 노드 포함
        
        // DFS 수행
        for (int i = 1; i <= n; i++)
            if (!vst[i])
            {
                vst[i] = true;
                DFS(i, 0);
            }

        cout << ans << '\n';
    }
    return 0;
}
