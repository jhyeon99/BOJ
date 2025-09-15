#include <bits/stdc++.h>
using namespace std;

const int MAX = 4000001;
bool isPrime[MAX];       // 소수 판별 배열
vector<int> prime;       // 소수 저장

// 에라토스테네스의 체로 소수 미리 계산
void Seive()
{
    for (int i = 2; i < MAX; i++) isPrime[i] = true;
    for (int i = 2; i * 2 < MAX; i++) {
        if (!isPrime[i]) continue;
        for (int j = 2; i * j < MAX; j++) {
            isPrime[i * j] = false; // 배수는 소수 아님
        }
    }
    for (int i = 2; i < MAX; i++) 
        if (isPrime[i]) prime.push_back(i); // 소수 저장
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;

    Seive(); // 소수 계산

    int l = 0, r = 0, s = prime[0], a = 0; // 슬라이딩 윈도우 변수: l,r=인덱스, s=합, a=경우의 수

    while (true)
    {
        if (s <= n)
        {
            if (s == n) a++; // 합이 n이면 경우의 수 증가
            if (++r == prime.size()) break; // 끝까지 탐색
            s += prime[r]; // 오른쪽으로 확장
        }
        else
        {
            s -= prime[l++]; // 합이 크면 왼쪽 제거
        }
    }

    cout << a; // 결과 출력
    return 0;
}
