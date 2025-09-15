#include <bits/stdc++.h>
using namespace std;
const int INF = 1234567890;
int n, a[3][10000], ret;
int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> a[0][i];
		ret += a[0][i] * 3;
	}
	for (int i = 0; i < n; i++)
	{
		for (int k = 1; k < 3; k++)
		{
			if (i - k < 0) break;
			int x = min(a[k - 1][i - 1], a[0][i]);
			a[k - 1][i - 1] -= x;
			a[0][i] -= x;
			a[k][i] += x;
			ret -= x;
		}
	}
	cout << ret;
	return 0;
}