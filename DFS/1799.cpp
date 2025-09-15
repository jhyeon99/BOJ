#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

const int MAX = 10;                // 최대 체스판 크기
int diag1[2 * MAX - 1], diag2[2 * MAX - 1]; // 좌상-우하, 우상-좌하 대각선 체크
vector<pii> pos[2];                // 색깔별 가능한 위치 저장 (0: 검은색, 1: 흰색)
int cnt[2], ans[2];                // 현재 비숍 수, 최대 비숍 수

// DFS로 비숍 배치
void DFS(int prev, bool color)
{
    for (int i = prev + 1; i < pos[color].size(); i++)
    {
        pii p = pos[color][i];
        int p1 = p.first + p.second;          // 좌상-우하 대각선 번호
        int p2 = MAX - p.first - 1 + p.second; // 우상-좌하 대각선 번호

        if (diag1[p1] || diag2[p2]) continue; // 대각선 충돌 체크

        // 배치
        diag1[p1]++; diag2[p2]++;
        ans[color] = max(ans[color], ++cnt[color]);

        DFS(i, color); // 다음 위치 탐색

        // 백트래킹
        diag1[p1]--; diag2[p2]--;
        cnt[color]--;
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n; 
    cin >> n; // 체스판 크기 n x n

    // 입력받아 색깔별 가능한 위치 저장
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            bool b; cin >> b;
            if (b)
            {
                pos[(i + j) % 2].push_back({j, i}); // (i+j)%2로 체스판 색깔 구분
            }
        }
    }

    DFS(-1, 0); // 검은색 칸 DFS
    DFS(-1, 1); // 흰색 칸 DFS

    cout << ans[0] + ans[1]; // 최대 비숍 배치 수
    return 0;
}
