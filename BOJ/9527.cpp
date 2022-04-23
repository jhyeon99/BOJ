#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll F(ll x)
{
	x++;
	ll ret = 0;
	for (ll i = 54; i >= 0; i--)
	{
		if (x & (1LL << i))
		{
			x -= (1LL << i);
			ret += i * (1LL << i - 1) + x;
		}
	}
	return ret;
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	ll a, b; cin >> a >> b;
	cout << F(b) - F(a - 1);
	return 0;
}