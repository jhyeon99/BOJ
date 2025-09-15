#include <bits/stdc++.h>
using namespace std;

// 쿼리 구조체: 구간 [i, j], 입력 순서 저장
struct Query
{
    int i, j, order;
    Query() {}
    Query(int i, int j, int order) : i(i), j(j), order(order) {}
};

int a[100000];       // 입력 배열
int ans[100000];     // 쿼리별 정답 저장
int cnt[1000001];    // 값별 등장 횟수
int uniqueCnt;       // 현재 구간의 유니크 값 개수
Query q[100000];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];

    int m; cin >> m;
    for (int k = 0; k < m; k++)
    {
        int i, j; cin >> i >> j;
        q[k] = Query(i - 1, j - 1, k); // 0-indexed로 변환
    }

    // Mo's 알고리즘: sqrt(n) 블록 단위 정렬
    sort(q, q + m, [&](const Query& a, const Query& b)
    {
        int aIdx = a.j / sqrt(n);
        int bIdx = b.j / sqrt(n);
        return aIdx == bIdx ? a.i < b.i : aIdx < bIdx;
    });

    int ci = 0, cj = 0; // 현재 처리 구간 [ci, cj]
    if (!cnt[a[0]]++) { uniqueCnt++; } // 첫 원소 추가

    for (int i = 0; i < m; i++)
    {
        int ni = q[i].i, nj = q[i].j;

        // 현재 구간의 시작 위치 조정
        for (int i = ci; i < ni; i++) if (!--cnt[a[i]]) { uniqueCnt--; }
        for (int i = ci - 1; i >= ni; i--) if (!cnt[a[i]]++) { uniqueCnt++; }

        // 현재 구간의 끝 위치 조정
        for (int i = cj + 1; i <= nj; i++) if (!cnt[a[i]]++) { uniqueCnt++; }
        for (int i = cj; i > nj; i--) if (!--cnt[a[i]]) { uniqueCnt--; }

        ci = ni, cj = nj;
        ans[q[i].order] = uniqueCnt; // 정답 저장
    }

    for (int i = 0; i < m; i++) cout << ans[i] << '\n';
    return 0;
}
