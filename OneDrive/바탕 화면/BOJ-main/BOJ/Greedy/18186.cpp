#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1234567890123456789;
ll n, b, c, a[3][1000000], ret;
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n >> b >> c;
	for (int i = 0; i < n; i++)
	{
		cin >> a[0][i];
		ret += a[0][i] * b;
	}
	for (int i = 0; i < n; i++)
	{
		if (b <= c) break;
		for (int k = 1; k < 3; k++)
		{
			if (i - k < 0) break;
			ll x = min(a[k - 1][i - 1], a[0][i]);
			a[k - 1][i - 1] -= x;
			a[0][i] -= x;
			a[k][i] += x;
			ret -= x * (b - c);
		}
	}
	cout << ret;
	return 0;
}