#include <bits/stdc++.h>
using namespace std;
const int INF = 2e9;
const int MAX = 100001;
int arr[MAX];
int tree[MAX << 2];
int Init(int node, int start, int end)
{
	if (start == end)
		return tree[node] = start;
	else
	{
		int l = Init(node * 2, start, (start + end) / 2);
		int r = Init(node * 2 + 1, (start + end) / 2 + 1, end);
		if (arr[l] <= arr[r]) return tree[node] = l;
		else return tree[node] = r;
	}
}
int Update(int node, int start, int end, int index)
{
	if (start > index || end < index)
		return tree[node];
	if (start == index && end == index)
		return tree[node] = index;
	int l = Update(node * 2, start, (start + end) / 2, index);
	int r = Update(node * 2 + 1, (start + end) / 2 + 1, end, index);
	if (arr[l] <= arr[r]) return tree[node] = l;
	else return tree[node] = r;
}
int Minimum(int node, int start, int end, int left, int right)
{
	if (start > right || end < left)
		return 0;
	if (left <= start && end <= right)
		return tree[node];
	int l = Minimum(node * 2, start, (start + end) / 2, left, right);
	int r = Minimum(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
	if (arr[l] <= arr[r]) return l;
	else return r;
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n; cin >> n;
	arr[0] = INF;
	for (int i = 1; i <= n; i++) cin >> arr[i];
	Init(1, 1, n);
	int m; cin >> m;
	for (int i = 0; i < m; i++)
	{
		int a, b, c; cin >> a >> b >> c;
		if (a == 1)
		{
			arr[b] = c;
			Update(1, 1, n, b);
		}
		else
		{
			cout << Minimum(1, 1, n, b, c) << '\n';
		}
	}
	return 0;
}