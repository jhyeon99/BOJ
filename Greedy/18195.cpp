#include <bits/stdc++.h>
using namespace std;
const int INF = 1234567890;

int n;                  // 도시 수
int a[3][10000];        // a[0][i]: i번째 도시 배송할 박스 수
                        // a[1][i], a[2][i]: i번째 도시에서 1, 2일 뒤 배송 예정 박스 수
int ret;                // 총 비용

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[0][i];         // 각 도시의 박스 수 입력
        ret += a[0][i] * 3;     // 기본 배송 비용: 각 박스 3원
    }

    for (int i = 0; i < n; i++)
    {
        // 현재 도시와 직전 1~2개 도시를 묶어 배송할 수 있는 박스 수 계산
        for (int k = 1; k < 3; k++)
        {
            if (i - k < 0) break;        // 배열 범위 체크
            int x = min(a[k - 1][i - 1], a[0][i]);  // 직전 도시 박스와 현재 도시 박스 중 최소값
            a[k - 1][i - 1] -= x;       // 이전 도시 박스 감소
            a[0][i] -= x;               // 현재 도시 박스 감소
            a[k][i] += x;               // 현재 도시에서 k일 뒤 배송될 박스 증가
            ret -= x;                    // 묶음 배송 할인: 박스 1원 절약
        }
    }

    cout << ret;   // 최소 비용 출력
    return 0;
}
