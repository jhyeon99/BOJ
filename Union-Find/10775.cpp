#include <bits/stdc++.h>
using namespace std;

const int MAX = 100001;
int adj[MAX]; // 유니온-파인드 배열: 부모 노드 저장

// 경로 압축을 이용한 유니온-파인드
int UF(int idx)
{
    if (adj[idx] == idx) return idx;      // 루트 노드이면 반환
    return adj[idx] = UF(adj[idx]);       // 경로 압축
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int g, p; cin >> g >> p;             // g: 게이트 수, p: 비행기 수

    // 초기화: 각 게이트는 자기 자신을 루트로
    for (int i = 1; i <= g; i++) adj[i] = i;

    int ans = 0; // 도킹 가능한 비행기 수

    for (int i = 0; i < p; i++)
    {
        int gi; cin >> gi;               // i번째 비행기가 도킹 가능한 최대 게이트
        int dock = adj[gi] = UF(gi);    // 유니온-파인드를 통해 도킹 가능한 게이트 찾기
        if (!dock) break;               // 도킹할 수 있는 게이트 없으면 종료
        ans++;                          // 도킹 성공
        adj[dock] = UF(adj[dock - 1]);  // 사용한 게이트를 이전 게이트와 연결
    }

    cout << ans;                        // 도킹 가능한 총 비행기 수 출력
    return 0;
}
