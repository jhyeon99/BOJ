#include <stdio.h>
typedef long long ll;

ll k;
ll mobius[100001];

// 뮤비우스 함수 계산
void BuildMobius()
{
    mobius[1] = 1;
    for (ll i = 1; i <= 100000; i++)
    {
        if (mobius[i] != 0)
        {
            for (ll j = 2 * i; j <= 100000; j += i)
            {
                mobius[j] -= mobius[i];
            }
        }
    }
}

// n 이하의 제곱수가 아닌 수(Square-free number) 개수 계산
ll SquareFree(ll n)
{
    ll ret = 0;
    for (ll i = 1; i * i <= n; i++)
    {
        ret += (mobius[i] * (n / (i * i))); // 뮤비우스 함수 활용
    }
    return ret;
}

int main()
{
    ll left = 0, right = 2e9;
    scanf("%lld", &k);

    BuildMobius(); // 뮤비우스 함수 초기화

    // 이분 탐색으로 k번째 제곱수가 없는 수 찾기
    while (left + 1 < right)
    {
        ll mid = (left + right) / 2;
        if (SquareFree(mid) < k) left = mid;
        else right = mid;
    }

    printf("%lld", right); // 결과 출력
    return 0;
}
