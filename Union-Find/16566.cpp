#include <bits/stdc++.h>
using namespace std;

const int MAX = 4000000;
int val[MAX], par[MAX];

// 경로 압축을 적용한 Union-Find의 Find 함수
int Find(int x)
{
    if (par[x] == x) return x;        // 루트이면 자기 자신 반환
    return par[x] = Find(par[x]);     // 경로 압축 후 반환
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, m, k; 
    cin >> n >> m >> k;               // n: 최대값?, m: 값 개수, k: 쿼리 개수

    for (int i = 0; i < m; i++)
    {
        cin >> val[i];                 // 값 입력
        par[i] = i;                    // 각 값 초기 부모는 자기 자신
    }

    sort(val, val + m);                // 값 오름차순 정렬

    for (int i = 0; i < k; i++)
    {
        int t; cin >> t;               // 쿼리 입력
        int x = upper_bound(val, val + m, t) - val;  // t보다 큰 첫 위치 찾기
        cout << val[Find(x)] << '\n';                // 그 위치의 값 출력
        par[x] = Find(x) + 1;                        // Union 처리 (다음 사용될 위치 연결)
    }

    return 0;
}
