#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1234567890123456789;

ll n, b, c, a[3][1000000], ret; // n: 도시 수, b: 기본 가격, c: 할인 가격, a: 도시별 박스 배열, ret: 총 비용

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> b >> c; // 도시 수, 기본 가격, 할인 가격 입력
    
    for (int i = 0; i < n; i++)
    {
        cin >> a[0][i];       // 각 도시의 박스 수 입력
        ret += a[0][i] * b;  // 초기 비용 계산 (모든 박스를 기본 가격으로 계산)
    }

    // b > c인 경우에만 할인 적용
    for (int i = 0; i < n; i++)
    {
        if (b <= c) break; // 할인 효과가 없는 경우 반복 종료

        for (int k = 1; k < 3; k++) // 직전 1~2개 도시에서 배송할 수 있는 박스 확인
        {
            if (i - k < 0) break; // 범위를 벗어나면 종료

            ll x = min(a[k - 1][i - 1], a[0][i]); // 이전 도시에서 배송 가능한 박스 수와 현재 도시 박스 수 중 최소
            a[k - 1][i - 1] -= x; // 이전 도시에서 박스 수 감소
            a[0][i] -= x;         // 현재 도시에서 박스 수 감소
            a[k][i] += x;         // 할인 적용 박스 수 누적
            ret -= x * (b - c);   // 총 비용에서 할인만큼 차감
        }
    }

    cout << ret; // 최종 총 비용 출력
    return 0;
}
