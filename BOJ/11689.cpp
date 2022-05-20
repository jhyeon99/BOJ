#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	ll n; cin >> n;
	ll ans = n, num = n;
	for (ll i = 2L; i * i <= n; i++)
	{
		if (num % i == 0)
		{
			ans /= i;
			ans *= i - 1;
			while (num % i == 0)
			{
				num /= i;
			}
		}
	}
	if (num != 1)
	{
		ans /= num;
		ans *= num - 1;
	}
	cout << ans;
	return 0;
}