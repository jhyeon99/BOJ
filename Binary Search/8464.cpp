#include <stdio.h>
typedef long long ll;

ll k;                       // k번째 제곱수 없는 수
ll mobius[200001];          // Möbius 함수 값 저장

// Möbius 함수 생성 (Sieve 방식)
void BuildMobius()
{
    mobius[1] = 1;
    for (ll i = 1; i <= 200000; i++)
    {
        if (mobius[i] != 0)
        {
            for (ll j = 2 * i; j <= 200000; j += i)
            {
                mobius[j] -= mobius[i];   // Inclusion-Exclusion 적용
            }
        }
    }
}

// 1~n 사이의 제곱인수를 포함하지 않는 수 개수 계산
ll NonSquareFree(ll n)
{
    ll ret = n;  // 초기값: 모든 수
    for (ll i = 1; i * i <= n; i++)
    {
        ret -= (mobius[i] * (n / (i * i)));  // 제곱인수 포함하는 수 제외
    }
    return ret;
}

int main()
{
    ll left = 0, right = 3e10;  // 이분 탐색 범위
    scanf("%lld", &k);

    BuildMobius();  // Möbius 함수 계산

    // 이분 탐색으로 k번째 제곱수 없는 수 찾기
    while (left + 1 < right)
    {
        ll mid = (left + right) / 2;
        if (NonSquareFree(mid) < k) left = mid;
        else right = mid;
    }

    printf("%lld", right);  // k번째 제곱수 없는 수 출력
    return 0;
}
