#include <bits/stdc++.h>
using namespace std;
const int MAXW = 800000;
const int MAXN = 5000;
int arr[MAXN];
bool dp[MAXW];
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int w, n; cin >> w >> n;
    for (int i = 0; i < n; i++) cin >> arr[i];
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (arr[i] + arr[j] > w) continue;
            if (dp[w - arr[i] - arr[j]])
            {
                cout << "YES";
                return 0;
            }
        }
        for (int j = 0; j < i; j++) if (arr[i] + arr[j] < w) dp[arr[i] + arr[j]] = 1;
    }
    cout << "NO";
    return 0;
}
