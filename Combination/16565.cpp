#include <bits/stdc++.h>
using namespace std;

const int MOD = 10007; // 결과를 나눌 모듈러 값

int comb[53][53]; // 이항계수 (조합) 저장 배열

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    // 1. 조합 계산 (파스칼의 삼각형 이용)
    for (int i = 0; i <= 52; i++)
    {
        comb[i][0] = comb[i][i] = 1; // nC0 = 1, nCn = 1
        for (int j = 1; j < i; j++)
            comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % MOD; // 점화식
    }

    int n; 
    cin >> n; // 카드 수 입력

    int ans = 0;

    // 2. 4의 배수만큼 뽑는 경우 계산
    for (int i = 4; i <= n; i += 4)
    {
        // i >> 2 는 i/4 를 의미 (4장씩 묶는 것)
        // i >> 2 & 1 은 i/4 가 홀수인지 짝수인지 확인
        if (i >> 2 & 1)
            ans += comb[13][i >> 2] * comb[52 - i][n - i]; // 홀수면 더함
        else
            ans -= comb[13][i >> 2] * comb[52 - i][n - i]; // 짝수면 뺌
    }

    // 3. 음수 처리 및 모듈러 연산
    ans = (ans % MOD + MOD) % MOD;

    cout << ans; // 결과 출력
    return 0;
}
