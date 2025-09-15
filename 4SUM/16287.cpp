#include <bits/stdc++.h>
using namespace std;

const int MAXW = 800000; // 최대 합
const int MAXN = 5000;   // 최대 원소 개수
int arr[MAXN];            // 입력 배열
bool dp[MAXW];            // 가능한 두 수 합 체크

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int w, n; 
    cin >> w >> n;         // 목표 합 w, 배열 크기 n
    for (int i = 0; i < n; i++) cin >> arr[i]; // 배열 입력

    for (int i = 0; i < n; i++)
    {
        // i번째 이후 원소와 합이 목표보다 작을 경우 체크
        for (int j = i + 1; j < n; j++)
        {
            if (arr[i] + arr[j] > w) continue; // 합이 w보다 크면 무시
            if (dp[w - arr[i] - arr[j]])       // 이전 합으로 w를 만들 수 있는 경우
            {
                cout << "YES";                 // 4개 수로 w 만들 수 있음
                return 0;
            }
        }
        // 현재 원소와 이전 원소 합을 dp에 기록
        for (int j = 0; j < i; j++)
            if (arr[i] + arr[j] < w) dp[arr[i] + arr[j]] = 1;
    }
    cout << "NO"; // 만들 수 없는 경우
    return 0;
}
