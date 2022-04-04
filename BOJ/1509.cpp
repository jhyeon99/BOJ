#include <bits/stdc++.h>
using namespace std;
const int MAX = 2501;
const int INF = 1e9;
bool pal[MAX][MAX];
int dp[MAX];
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	string str; cin >> str;
	for (int j = 0; j < str.size(); j++)
	{
		for (int i = 0; i < str.size() - j; i++)
		{
			if (str[i] == str[i + j])
			{
				if (pal[i + 1][i + j - 1] || j < 2)
				{
					pal[i][i + j] = true;
				}
			}
		}
	}
	dp[0] = 0;
	for (int i = 1; i <= str.size(); i++)
	{
		dp[i] = INF;
		for (int j = 0; j < i; j++)
		{
			if (pal[j][i - 1])
			{
				dp[i] = min(dp[i], dp[j] + 1);
			}
		}
	}
	cout << dp[str.size()];
	return 0;
}