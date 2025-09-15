#include <bits/stdc++.h>
using namespace std;
const int MOD = 10007;
int comb[53][53];
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	for (int i = 0; i <= 52; i++)
	{
		comb[i][0] = comb[i][i] = 1;
		for (int j = 1; j < i; j++)
			comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % MOD;
	}
	int n; cin >> n;
	int ans = 0;
	for (int i = 4; i <= n; i += 4)
	{
		if (i >> 2 & 1)
			ans += comb[13][i >> 2] * comb[52 - i][n - i];
		else
			ans -= comb[13][i >> 2] * comb[52 - i][n - i];
	}
	ans = (ans % MOD + MOD) % MOD;
	cout << ans;
	return 0;
}