#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    ll n; 
    cin >> n;        // 입력 값 N
    ll ans = n;      // 초기값은 N
    ll num = n;      // N을 나누어 소인수 확인용

    // 2부터 sqrt(N)까지 소인수 체크
    for (ll i = 2L; i * i <= n; i++)
    {
        if (num % i == 0)
        {
            // i가 소인수이면 피 함수 갱신
            ans /= i;
            ans *= i - 1;

            // i로 나누어 떨어지는 모든 배수를 제거
            while (num % i == 0)
            {
                num /= i;
            }
        }
    }

    // 남은 수가 1이 아니면 소인수로 처리
    if (num != 1)
    {
        ans /= num;
        ans *= num - 1;
    }

    cout << ans; // 오일러 피 함수 값 출력
    return 0;
}
