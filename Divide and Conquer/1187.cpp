#include <bits/stdc++.h>
using namespace std;

int a[2047];

// 분할 정복을 통해 배열 재배치
int DivideAndConquer(int l, int r)
{
    int n = (r - l + 2) / 2;   // 현재 구간 크기
    int hn = n / 2;            // 절반 크기

    if (n <= 1) return a[l];   // 구간 크기가 1이면 반환

    int s[3] = {};
    // 3등분 후 재귀 호출
    for (int i = 0; i < 3; i++)
    {
        s[i] = DivideAndConquer(l + i * hn, l + i * hn + (2 * hn - 2));
    }

    // 나머지 기준으로 swap 및 병합 결정
    if (s[0] % 2 == s[1] % 2)
    {
        return (s[0] + s[1]) / 2;
    }
    else if (s[0] % 2 == s[2] % 2)
    {
        for (int i = 0; i < hn; i++)
            swap(a[l + hn + i], a[l + n + i]);
        return (s[0] + s[2]) / 2;
    }
    else
    {
        for (int i = 0; i < hn; i++)
            swap(a[l + i], a[l + n + i]);
        return (s[1] + s[2]) / 2;
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;

    for (int i = 0; i < 2 * n - 1; i++)
        cin >> a[i]; // 배열 입력

    DivideAndConquer(0, 2 * n - 2); // 재배치 수행

    for (int i = 0; i < n; i++)
        cout << a[i] << ' '; // 결과 출력

    return 0;
}
