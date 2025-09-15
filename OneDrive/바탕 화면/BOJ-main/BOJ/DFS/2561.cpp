#include <bits/stdc++.h>
using namespace std;
int n;
int a[1000];
vector<pair<int, int>> ans;
vector<int> Split()
{
	vector<int> ret;
	int way = 0;
	ret.push_back(0);
	for (int i = 1; i < n - 1; i++)
	{
		if (!(a[i - 1] - a[i] == 1 && a[i] - a[i + 1] == 1
			|| a[i - 1] - a[i] == -1 && a[i] - a[i + 1] == -1))
		{
			ret.push_back(i);
		}
	}
	ret.push_back(n - 1);
	return ret;
}
bool DFS(int c)
{
	bool isSort = true;
	for (int i = 0; i < n; i++)
	{
		if (a[i] != i + 1) isSort = false;
	}
	if (c == 3) return isSort;
	if (c < 3 && isSort)
	{
		for (int i = 0; i < 3 - c; i++)
		{
			ans.push_back(make_pair(0, 0));
		}
		return true;
	}
	vector<int> split = Split();
	for (int i = 0; i < split.size(); i++)
	{
		for (int j = i; j < split.size(); j++)
		{
			int s = split[i], e = split[j];
			if (s > e) swap(s, e);
			reverse(a + s, a + e + 1);
			if (DFS(c + 1))
			{
				ans.push_back(make_pair(s, e));
				return true;
			}
			reverse(a + s, a + e + 1);
		}
	}
	return false;
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	DFS(0);
	for (int i = ans.size() - 1; i >= 0; i--)
	{
		cout << ans[i].first + 1 << ' ' << ans[i].second + 1 << '\n';
	}
	return 0;
}