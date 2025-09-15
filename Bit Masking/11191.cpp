#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll basis[60]; // XOR 선형 기저: 각 비트 위치별로 대표 값 저장

int main()
{
    int n; 
    cin >> n; // 입력 원소 개수
    
    for (int i = 0; i < n; i++)
    {
        ll a; 
        cin >> a;
        // 선형 기저에 a 추가
        for (int j = 59; j >= 0; j--)
        {
            if (a & (1LL << j)) // j번째 비트가 1이면
            {
                if (!basis[j]) // 해당 비트에 기저가 없으면 새로운 기저로 추가
                {
                    basis[j] = a;
                    break;
                }
                else
                {
                    a ^= basis[j]; // 이미 기저가 있으면 XOR하여 줄이기
                }
            }
        }
    }

    ll ans = 0;
    // 최대 XOR값 구하기: 큰 비트부터 적용
    for (int i = 59; i >= 0; i--)
    {
        ans = max(ans, ans ^ basis[i]);
    }

    cout << ans; // 최종 XOR 최대값 출력
    return 0;
}
