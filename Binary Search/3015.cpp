#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAX = 5e5;

int a[MAX];  // 입력 배열

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int n; 
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];

    deque<int> s;   // 현재까지의 수열 상태를 저장
    s.push_front(a[0]);
    ll ans = 0;     // 조건을 만족하는 쌍의 개수 누적

    for (int i = 1; i < n; i++)
    {
        // 현재 a[i]와 기존 수열 s와 비교하여 최소값 누적
        ans += min((int)s.size(), (int)(upper_bound(s.begin(), s.end(), a[i]) - s.begin()) + 1);

        // 현재 a[i]보다 작은 값들은 제거 (조건 만족을 위해)
        while (s.front() < a[i])
        {
            s.pop_front();
            if (s.empty()) break;
        }

        // 새로운 값을 앞에 추가
        s.push_front(a[i]);
    }

    cout << ans;
    return 0;
}
