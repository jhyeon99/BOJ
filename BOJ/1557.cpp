#include <stdio.h>
typedef long long ll;
ll k;
ll mobius[100001];
void BuildMobius()
{
	mobius[1] = 1;
	for (ll i = 1; i <= 100000; i++)
	{
		if (mobius[i] != 0)
		{
			for (ll j = 2 * i; j <= 100000; j += i)
			{
				mobius[j] -= mobius[i];
			}
		}
	}
}
ll SquareFree(ll n)
{
	ll ret = 0;
	for (ll i = 1; i * i <= n; i++)
	{
		ret += (mobius[i] * (n / (i * i)));
	}
	return ret;
}
int main()
{
	ll left = 0, right = 2e9;
	scanf("%lld", &k);
	BuildMobius();
	while (left + 1 < right)
	{
		ll mid = (left + right) / 2;
		if (SquareFree(mid) < k) left = mid;
		else right = mid;
	}
	printf("%lld", right);
	return 0;
}