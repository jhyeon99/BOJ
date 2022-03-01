#include <bits/stdc++.h>
using namespace std;
struct Lazy
{
	int max;
	int min;
	Lazy() : max(0), min(1e9) {}
	Lazy(int max, int min) : max(max), min(min) {}
};
int n, k;
int num[2000001];
Lazy lazy[8000004];
void update(int node, int op, int height)
{
	if (op == 1)
	{
		lazy[node].max = max(lazy[node].max, height);
		lazy[node].min = max(lazy[node].min, height);
	}
	else
	{
		lazy[node].max = min(lazy[node].max, height);
		lazy[node].min = min(lazy[node].min, height);
	}
}
void update_range(int node, int start, int end, int left, int right, int op, int height)
{
	if (left > end || right < start)
	{
		return;
	}
	if (left <= start && end <= right)
	{
		update(node, op, height);
		if (left == right)
		{
			num[left] = lazy[node].max;
		}
		return;
	}
	for (int n = node * 2; n <= node * 2 + 1; n++)
	{
		update(n, 1, lazy[node].max);
		update(n, 2, lazy[node].min);
	}
	lazy[node] = Lazy();
	update_range(node * 2, start, (start + end) / 2, left, right, op, height);
	update_range(node * 2 + 1, (start + end) / 2 + 1, end, left, right, op, height);
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n >> k;
	for (int i = 0; i < k; i++)
	{
		int op, left, right, height;
		cin >> op >> left >> right >> height;
		if (op == 1)
		{
			update_range(1, 0, n - 1, left, right, op, height);
		}
		else
		{
			update_range(1, 0, n - 1, left, right, op, height);
		}
	}
	for (int i = 0; i < n; i++)
	{
		update_range(1, 0, n - 1, i, i, 1, 0);
		cout << num[i] << '\n';
	}
	return 0;
}