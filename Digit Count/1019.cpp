#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n; cin >> n;        // 1~n까지 숫자 입력
    int arr[10] = {};       // 0~9 각 숫자 등장 횟수

    for (int curr = n, e = 1; curr; e *= 10) // 각 자릿수별 계산
    {
        int t = curr % 10, next = curr / 10;
        for (int i = 0; i < 10; i++)
            arr[i] += (next + (1 <= i && i <= t)) * e; // 자리수 누적
        arr[t] -= e - (n % e) - 1; // 현재 자리수 조정
        curr = next;
    }

    for (int i = 0; i < 10; i++)
        cout << arr[i] << ' '; // 결과 출력

    return 0;
}