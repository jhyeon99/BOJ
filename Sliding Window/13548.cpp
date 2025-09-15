#include <bits/stdc++.h>
using namespace std;

const int INF = 1234567890;

// 쿼리 구조체: 구간 [i, j], 입력 순서 저장
struct Query
{
    int i, j, order;
    Query() {}
    Query(int i, int j, int order) : i(i), j(j), order(order) {}
};

int a[100000];       // 입력 배열
int ans[100000];     // 쿼리별 정답 저장
Query q[100000];

int cnt1[100001];    // 값별 등장 횟수
int cnt2[100001];    // 등장 횟수별 값 개수 (빈도 빈도)
int maxOfCnt;        // 현재 구간 최빈값 빈도

// 값 n을 구간에 추가
void Push(int n)
{
    cnt2[cnt1[n]++]--;      // 기존 빈도 감소
    maxOfCnt = max(maxOfCnt, cnt1[n]); // 최빈값 갱신
    cnt2[cnt1[n]]++;        // 새로운 빈도 증가
}

// 값 n을 구간에서 제거
void Pop(int n)
{
    cnt2[cnt1[n]--]--;      // 기존 빈도 감소
    if (!cnt2[maxOfCnt])    // 최빈값 갱신
        maxOfCnt--;
    cnt2[cnt1[n]]++;        // 새로운 빈도 증가
}

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
        int aIdx = a.j / sqrt(n), bIdx = b.j / sqrt(n);
        return aIdx == bIdx ? a.i < b.i : aIdx < bIdx;
    });

    int ci = 0, cj = 0; // 현재 처리 구간 [ci, cj]
    cnt2[0] = INF;      // 초기 빈도값 세팅
    Push(a[0]);          // 첫 원소 추가

    for (int i = 0; i < m; i++)
    {
        // 구간 시작 위치 조정
        while (ci < q[i].i) Pop(a[ci++]);
        while (ci > q[i].i) Push(a[--ci]);

        // 구간 끝 위치 조정
        while (cj < q[i].j) Push(a[++cj]);
        while (cj > q[i].j) Pop(a[cj--]);

        ans[q[i].order] = maxOfCnt; // 정답 저장
    }

    for (int i = 0; i < m; i++) cout << ans[i] << '\n';
    return 0;
}
