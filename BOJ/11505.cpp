#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 2e9;
const int MOD = 1e9 + 7;
const int MAX = 1e6;
int n, m, k;
int arr[MAX];
ll tree[MAX << 2];
ll Init(int node, int start, int end)
{
	if (start == end)
		return tree[node] = arr[start];
	else
		return tree[node] = Init(node * 2, start, (start + end) / 2) * Init(node * 2 + 1, (start + end) / 2 + 1, end) % MOD;
}
ll Update(int node, int start, int end, int index, ll val)
{
	if (start > index || end < index)
		return tree[node];
	if (start == index && end == index)
		return tree[node] = val;
	return tree[node] = Update(node * 2, start, (start + end) / 2, index, val) * Update(node * 2 + 1, (start + end) / 2 + 1, end, index, val) % MOD;
}
ll Multiple(int node, int start, int end, int left, int right)
{
	if (start > right || end < left)
		return 1;
	if (left <= start && end <= right)
		return tree[node];
	return Multiple(node * 2, start, (start + end) / 2, left, right) * Multiple(node * 2 + 1, (start + end) / 2 + 1, end, left, right) % MOD;
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++) cin >> arr[i];
	Init(1, 0, n - 1);
	for (int i = 0; i < m + k; i++)
	{
		int a, b, c; cin >> a >> b >> c;
		if (a == 1)
		{
			Update(1, 0, n - 1, b - 1, c);
		}
		else
		{
			cout << Multiple(1, 0, n - 1, b - 1, c - 1) << '\n';
		}
	}
	return 0;
}