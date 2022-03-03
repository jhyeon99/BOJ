#include <bits/stdc++.h>
using namespace std;
int a[2047];
int DivideAndConquer(int l, int r)
{
    int n = (r - l + 2) / 2, hn = n / 2;
    if (n <= 1) return a[l];
    int s[3] = {};
    for (int i = 0; i < 3; i++)
    {
        s[i] = DivideAndConquer(l + i * hn, l + i * hn + (2 * hn - 2));
    }
    if (s[0] % 2 == s[1] % 2)
    {
        return (s[0] + s[1]) / 2;
    }
    else if (s[0] % 2 == s[2] % 2)
    {
        for (int i = 0; i < hn; i++)
        {
            swap(a[l + hn + i], a[l + n + i]);
        }
        return (s[0] + s[2]) / 2;
    }
    else
    {
        for (int i = 0; i < hn; i++)
        {
            swap(a[l + i], a[l + n + i]);
        }
        return (s[1] + s[2]) / 2;
    }
}
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    for (int i = 0; i < 2 * n - 1; i++)
    {
        cin >> a[i];
    }
    DivideAndConquer(0, 2 * n - 2);
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << ' ';
    }
    return 0;
}