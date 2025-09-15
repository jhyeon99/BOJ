#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;

const int INF = 1e9;

int n, k, a;
int s[100001], d[100001], l[100001], r[100001]; // s: 값, d: 차이, l/r: 왼쪽/오른쪽 인덱스
bool v[100001]; // 이미 병합된 위치 체크
priority_queue<pii, vector<pii>, greater<pii>> pq; // 최소 힙 (차이, 인덱스)

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n >> k;
    d[0] = d[n] = INF;

    // 초기값 입력 및 차이 계산
    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
        l[i + 1] = i; // 왼쪽 연결
        if (i > 0)
        {
            r[i - 1] = i;       // 오른쪽 연결
            d[i] = s[i] - s[i - 1]; // 인접 차이
        }
        pq.push(pii(d[i], i)); // 힙에 차이 삽입
    }

    // k번 병합
    while (k--)
    {
        while (v[pq.top().second]) pq.pop(); // 이미 처리된 차이는 패스
        int dist = pq.top().first;
        int idx = pq.top().second;
        pq.pop();

        v[l[idx]] = v[r[idx]] = true; // 병합 표시
        d[idx] = d[l[idx]] + d[r[idx]] - d[idx]; // 새로운 차이 계산

        // 연결 업데이트
        l[idx] = l[l[idx]];
        r[idx] = r[r[idx]];
        l[r[idx]] = idx;
        r[l[idx]] = idx;

        pq.push(pii(d[idx], idx)); // 힙에 새 차이 삽입
        a += dist; // 결과 누적
    }

    cout << a; // 최종 최소 합
    return 0;
}
