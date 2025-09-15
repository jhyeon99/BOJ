#include <stdio.h>
typedef long long ll;
ll k;
ll mobius[200001];
void BuildMobius()
{
	mobius[1] = 1;
	for (ll i = 1; i <= 200000; i++)
	{
		if (mobius[i] != 0)
		{
			for (ll j = 2 * i; j <= 200000; j += i)
			{
				mobius[j] -= mobius[i];
			}
		}
	}
}
ll NonSquareFree(ll n)
{
	ll ret = n;
	for (ll i = 1; i * i <= n; i++)
	{
		ret -= (mobius[i] * (n / (i * i)));
	}
	return ret;
}
int main()
{
	ll left = 0, right = 3e10;
	scanf("%lld", &k);
	BuildMobius();
	while (left + 1 < right)
	{
		ll mid = (left + right) / 2;
		if (NonSquareFree(mid) < k) left = mid;
		else right = mid;
	}
	printf("%lld", right);
	return 0;
}