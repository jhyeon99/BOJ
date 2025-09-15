#include <bits/stdc++.h>
using namespace std;

const int MAX = 100000;
const int INF = 1e9;
int a[MAX];

int main()
{
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);

    int n, s; 
    cin >> n >> s;  // 배열 길이 n과 목표 합 s
    for (int i = 0; i < n; i++) cin >> a[i];

    int l = 0, r = 0;        // 투 포인터 좌, 우
    int sum = a[0];          // 현재 구간 합
    int ans = INF;           // 최소 길이

    while (r < n)
    {
        if (sum >= s) 
        {
            // 현재 구간 길이 갱신
            ans = min(ans, r - l + 1);
        }

        if (sum - a[l] >= s)
        {
            // 왼쪽 요소 제거 가능하면 제거
            sum -= a[l++];
        }
        else
        {
            // 아니면 오른쪽 포인터 증가
            r++;
            if (r < n) sum += a[r];
        }
    }

    if (ans == INF) ans = 0; // 합 ≥ s 구간이 없으면 0
    cout << ans;
    return 0;
}
