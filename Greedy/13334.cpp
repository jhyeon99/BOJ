#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

// 끝나는 시간을 기준으로 최소 힙, 시작 시간을 저장하는 최소 힙
priority_queue<pii, vector<pii>, greater<pii>> pq1;
priority_queue<int, vector<int>, greater<int>> pq2;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; 
    cin >> n; // 구간의 개수

    // 구간 입력
    for (int i = 0; i < n; i++)
    {
        int h, o; 
        cin >> h >> o;
        if (h > o) swap(h, o); // 작은 값이 시작, 큰 값이 끝
        pq1.push(pii(o, h));   // (끝나는 시간, 시작 시간)
    }

    int d; 
    cin >> d; // 구간 길이 제한
    int ans = 0, cnt = 0;

    // 끝나는 시간을 기준으로 구간 탐색
    while (!pq1.empty())
    {
        int e = pq1.top().first;  // 현재 구간 끝
        int s = pq1.top().second; // 현재 구간 시작
        pq1.pop();

        cnt++;
        pq2.push(s); // 시작 시간을 힙에 추가

        int x = e - d; // 구간 길이 제한
        // 시작 시간이 제한보다 작은 구간 제거
        while (!pq2.empty() && pq2.top() < x)
        {
            pq2.pop();
            cnt--;
        }

        ans = max(ans, cnt); // 최대 구간 수 갱신
    }

    cout << ans;
    return 0;
}
