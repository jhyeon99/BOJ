#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX = 1001;

int a[MAX], b[MAX];      // 원본 배열
int aSum[MAX], bSum[MAX]; // 누적합 배열
vector<int> aSubarr, bSubarr; // 모든 부분 배열 합 저장

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t, n;
    cin >> t >> n;

    // 배열 A 입력 및 누적합 계산
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        aSum[i] = aSum[i - 1] + a[i];
    }

    int m;
    cin >> m;

    // 배열 B 입력 및 누적합 계산
    for (int i = 1; i <= m; i++) {
        cin >> b[i];
        bSum[i] = bSum[i - 1] + b[i];
    }

    // 배열 A의 모든 부분 배열 합 구하기
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
            aSubarr.push_back(aSum[j] - aSum[i]);
        }
    }

    // 배열 B의 모든 부분 배열 합 구하기
    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j <= m; j++) {
            bSubarr.push_back(bSum[j] - bSum[i]);
        }
    }

    // 배열 B 부분 합 정렬 (이분 탐색 용)
    sort(bSubarr.begin(), bSubarr.end());

    ll ans = 0;
    // 배열 A 부분 합과 B 부분 합의 합이 t가 되는 경우 개수 계산
    for (int sumA : aSubarr) {
        ans += upper_bound(bSubarr.begin(), bSubarr.end(), t - sumA)
             - lower_bound(bSubarr.begin(), bSubarr.end(), t - sumA);
    }

    cout << ans;
    return 0;
}
