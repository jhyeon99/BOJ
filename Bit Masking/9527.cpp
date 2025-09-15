#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 0부터 x까지 각 수의 이진 표현에서 1의 개수를 합산
ll F(ll x)
{
    x++;               // 0부터 x까지 포함하기 위해 1 증가
    ll ret = 0;
    // 각 비트 위치별로 1의 개수 계산
    for (ll i = 54; i >= 0; i--)  // 최대 2^54 범위까지 고려
    {
        if (x & (1LL << i))       // i번째 비트가 1이면
        {
            x -= (1LL << i);      // 해당 비트 값을 제거하고
            // i번째 비트가 1인 모든 수의 개수 + 남은 x 범위에 대한 1의 개수 추가
            ret += i * (1LL << (i - 1)) + x;
        }
    }
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll a, b; cin >> a >> b;
    // [a, b] 구간 내 모든 수의 1의 개수 합 = F(b) - F(a-1)
    cout << F(b) - F(a - 1);
    return 0;
}
