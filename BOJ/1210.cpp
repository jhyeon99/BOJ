#include <bits/stdc++.h>
using namespace std;
vector<int> NMK(int n, int m, int k)
{
	vector<int> ret;
	if (m + k - 1 <= n && n <= m * k)
	{
		for (int i = 1; i <= n; i++) ret.push_back(i);
		int section = m, curr = 0, next = k;
		while (section--)
		{
			reverse(ret.begin() + curr, ret.begin() + next);
			curr = next;
			next += min(k, n - curr - (section - 1));
		}
	}
	else ret.push_back(-1);
	return ret;
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n, m, k; cin >> n >> m >> k;
	for (int arr : NMK(n, m, k))
	{
		cout << arr << ' ';
	}
	return 0;
}