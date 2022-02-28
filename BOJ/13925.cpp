#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;
struct Vector2LL
{
	Vector2LL() : x(1), y(0) {}
	Vector2LL(int x, int y) : x(x), y(y) {}
	ll x, y;
};
int n, m;
ll a[100001];
ll tree[400004];
Vector2LL lazy[400004];
ll init(int node, int start, int end)
{
	if (start == end)
	{
		return tree[node] = a[start];
	}
	else
	{
		return tree[node] = (init(node * 2, start, (start + end) / 2) + init(node * 2 + 1, (start + end) / 2 + 1, end)) % MOD;
	}
}
void update_lazy(int node, int start, int end)
{
	if (lazy[node].x != 1 || lazy[node].y != 0)
	{
		tree[node] *= lazy[node].x;
		tree[node] += (end - start + 1) * lazy[node].y;
		tree[node] %= MOD;
		if (start != end)
		{
			lazy[node * 2].x *= lazy[node].x;
			lazy[node * 2].y *= lazy[node].x;
			lazy[node * 2].y += lazy[node].y;
			lazy[node * 2].x %= MOD;
			lazy[node * 2].y %= MOD;
			lazy[node * 2 + 1].x *= lazy[node].x;
			lazy[node * 2 + 1].y *= lazy[node].x;
			lazy[node * 2 + 1].y += lazy[node].y;
			lazy[node * 2 + 1].x %= MOD;
			lazy[node * 2 + 1].y %= MOD;
		}
		lazy[node] = Vector2LL();
	}
}
void update_range(int node, int start, int end, int left, int right, ll mtp, ll add)
{
	update_lazy(node, start, end);
	if (left > end || right < start)
	{
		return;
	}
	if (left <= start && end <= right)
	{
		lazy[node].x *= mtp;
		lazy[node].x %= MOD;
		lazy[node].y *= mtp;
		lazy[node].y += add;
		lazy[node].y %= MOD;
		update_lazy(node, start, end);
		return;
	}
	update_range(node * 2, start, (start + end) / 2, left, right, mtp, add);
	update_range(node * 2 + 1, (start + end) / 2 + 1, end, left, right, mtp, add);
	tree[node] = (tree[node * 2] + tree[node * 2 + 1]) % MOD;
}
ll sum(int node, int start, int end, int left, int right)
{
	update_lazy(node, start, end);
	if (left > end || right < start)
	{
		return 0;
	}
	if (left <= start && end <= right)
	{
		return tree[node] % MOD;
	}
	return (sum(node * 2, start, (start + end) / 2, left, right) + sum(node * 2 + 1, (start + end) / 2 + 1, end, left, right)) % MOD;
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
	}
	init(1, 1, n);
	cin >> m;
	for (int i = 0; i < m; i++)
	{
		int t;
		cin >> t;
		int x, y;
		cin >> x >> y;
		ll v;
		if (t != 4) cin >> v;
		if (t == 1)
		{
			update_range(1, 1, n, x, y, 1, v);
		}
		else if (t == 2)
		{
			update_range(1, 1, n, x, y, v, 0);
		}
		else if (t == 3)
		{
			update_range(1, 1, n, x, y, 0, v);
		}
		else
		{
			cout << sum(1, 1, n, x, y) << '\n';
		}
	}
}