#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll basis[60];
int main()
{
	int n; cin >> n;
	for (int i = 0; i < n; i++)
	{
		ll a; cin >> a;
		for (int j = 59; j >= 0; j--)
		{
			if (a & (1LL << j))
			{
				if (!basis[j])
				{
					basis[j] = a;
					break;
				}
				else
				{
					a ^= basis[j];
				}
			}
		}
	}
	ll ans = 0;
	for (int i = 59; i >= 0; i--)
	{
		ans = max(ans, ans ^ basis[i]);
	}
	cout << ans;
	return 0;
}