#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int d, p, q;
    cin >> d >> p >> q;

    // 항상 p >= q로 설정
    if (p < q) swap(p, q);

    int n = ceil((double)d / p); // 큰 단위(p) 개수 초기 추정
    int m = 0;                   // 작은 단위(q) 개수
    int ans = p * n;             // 초기 최소 합

    while (n) {
        n--; // 큰 단위 하나 줄임
        // 남은 거리를 작은 단위(q)로 채움
        m += ceil((double)(d - (p * n + q * m)) / q);

        if (ans == p * n + q * m) break; // 더 이상 줄일 수 없으면 종료
        ans = min(ans, p * n + q * m);   // 최소 합 갱신
        if (ans == d) break;             // 정확히 d면 종료
    }

    cout << ans; // 최소 합 출력
    return 0;
}
