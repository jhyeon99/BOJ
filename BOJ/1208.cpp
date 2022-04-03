#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int n, s;
int arr[40];
map<int, int> mp;
ll ans;
void DFS1(int idx, int sum = 0)
{
	if (idx == n / 2)
	{
		mp[sum]++;
		return;
	}
	DFS1(idx + 1, sum);
	DFS1(idx + 1, sum + arr[idx]);
}
void DFS2(int idx, int sum = 0)
{
	if (idx == n)
	{
		ans += mp[s - sum];
		return;
	}
	DFS2(idx + 1, sum);
	DFS2(idx + 1, sum + arr[idx]);
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n >> s;
	for (int i = 0; i < n; i++) cin >> arr[i];
	DFS1(0);
	DFS2(n / 2);
	if (s == 0) ans--;
	cout << ans;
	return 0;
}