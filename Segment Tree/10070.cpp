#include <bits/stdc++.h>
using namespace std;

// 노드 정보를 담는 구조체: 구간 최대/최소값 관리
struct Lazy
{
    int max;  // 해당 구간에서 최대 높이
    int min;  // 해당 구간에서 최소 높이
    Lazy() : max(0), min(1e9) {}                 // 초기값 설정
    Lazy(int max, int min) : max(max), min(min) {}
};

int n, k;                   // n: 전체 길이, k: 명령 개수
int num[2000001];           // 최종 각 위치의 값 저장
Lazy lazy[8000004];         // 세그먼트 트리 (4배 크기)


// 노드 단일 업데이트
void update(int node, int op, int height)
{
    if (op == 1)  // 최대값 갱신
    {
        lazy[node].max = max(lazy[node].max, height);
        lazy[node].min = max(lazy[node].min, height);
    }
    else          // 최소값 갱신
    {
        lazy[node].max = min(lazy[node].max, height);
        lazy[node].min = min(lazy[node].min, height);
    }
}

// 범위 업데이트 함수 (세그먼트 트리 + 레이지 전파)
void update_range(int node, int start, int end, int left, int right, int op, int height)
{
    if (left > end || right < start) return;  // 구간 겹치지 않음

    if (left <= start && end <= right)        // 완전히 포함될 때
    {
        update(node, op, height);            // 노드 값 갱신
        if (left == right)                    // 리프 노드이면 최종 값 저장
        {
            num[left] = lazy[node].max;
        }
        return;
    }

    // 자식 노드에 현재 노드의 레이지 값 전달
    for (int n = node * 2; n <= node * 2 + 1; n++)
    {
        update(n, 1, lazy[node].max);
        update(n, 2, lazy[node].min);
    }
    lazy[node] = Lazy();  // 현재 노드 초기화

    // 자식 노드 재귀 호출
    update_range(node * 2, start, (start + end) / 2, left, right, op, height);
    update_range(node * 2 + 1, (start + end) / 2 + 1, end, left, right, op, height);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n >> k;
    for (int i = 0; i < k; i++)
    {
        int op, left, right, height;
        cin >> op >> left >> right >> height;
        update_range(1, 0, n - 1, left, right, op, height);  // 명령 수행
    }

    // 최종 값 계산 및 출력
    for (int i = 0; i < n; i++)
    {
        update_range(1, 0, n - 1, i, i, 1, 0);  // 각 위치 값 보정
        cout << num[i] << '\n';
    }
    return 0;
}
