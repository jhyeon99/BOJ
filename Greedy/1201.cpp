#include <bits/stdc++.h>
using namespace std;

// n개의 수를 m개의 구간으로 나누고 각 구간 최대 길이 k로 반전
vector<int> NMK(int n, int m, int k)
{
    vector<int> ret;

    // 조건 검사: n이 가능한 범위에 있어야 함
    if (m + k - 1 <= n && n <= m * k)
    {
        // 1~n까지 초기 배열 생성
        for (int i = 1; i <= n; i++) ret.push_back(i);

        int section = m;  // 남은 구간 수
        int curr = 0;     // 현재 구간 시작 인덱스
        int next = k;     // 다음 구간 끝 인덱스

        // 각 구간 반전
        while (section--)
        {
            reverse(ret.begin() + curr, ret.begin() + next);
            curr = next;
            next += min(k, n - curr - (section - 1)); // 남은 길이에 맞춰 구간 조정
        }
    }
    else ret.push_back(-1); // 조건 불만족 시 -1 반환

    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m, k; 
    cin >> n >> m >> k;

    // 결과 출력
    for (int arr : NMK(n, m, k))
        cout << arr << ' ';

    return 0;
}
