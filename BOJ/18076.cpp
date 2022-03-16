#include <bits/stdc++.h>
using namespace std;
int d[500][500];
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n; cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin.get();
		for (int j = 0; j < n; j++)
		{
			d[i][j] = cin.get() - '0';
		}
	}
	for (int e = 1; e < n; e++)
	{
		for (int s = 0; s < e; s++)
		{
			if (d[s][e])
			{
				for (int i = 0; i < n; i++)
				{
					d[s][i] -= d[e][i];
					d[s][i] = (d[s][i] + 10) % 10;
				}
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << d[i][j];
		}
		cout << '\n';
	}
	return 0;
}