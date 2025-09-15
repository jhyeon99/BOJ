#include <bits/stdc++.h>
using namespace std;
const int INF = 2e9;
const int MAX = 100000;
int n, m;
int arr[MAX];
int minTree[MAX << 2], maxTree[MAX << 2];
int InitMin(int idx, int start, int end)
{
	if (start == end)
	{
		return minTree[idx] = arr[start];
	}
	else
	{
		int mid = (start + end) / 2;
		return minTree[idx] = min(InitMin(idx * 2, start, mid), InitMin(idx * 2 + 1, mid + 1, end));
	}
}
int InitMax(int idx, int start, int end)
{
	if (start == end)
	{
		return maxTree[idx] = arr[start];
	}
	else
	{
		int mid = (start + end) / 2;
		return maxTree[idx] = max(InitMax(idx * 2, start, mid), InitMax(idx * 2 + 1, mid + 1, end));
	}
}
int FindMin(int node, int start, int end, int left, int right)
{
	if (start > right || end < left)
		return INF;
	if (left <= start && end <= right)
		return minTree[node];
	return min(FindMin(node * 2, start, (start + end) / 2, left, right), FindMin(node * 2 + 1, (start + end) / 2 + 1, end, left, right));
}
int FindMax(int node, int start, int end, int left, int right)
{
	if (start > right || end < left)
		return 0;
	if (left <= start && end <= right)
		return maxTree[node];
	return max(FindMax(node * 2, start, (start + end) / 2, left, right), FindMax(node * 2 + 1, (start + end) / 2 + 1, end, left, right));
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n >> m;
	for (int i = 0; i < n; i++) cin >> arr[i];
	InitMin(1, 0, n - 1);
	InitMax(1, 0, n - 1);
	for (int i = 0; i < m; i++)
	{
		int a, b; cin >> a >> b;
		cout << FindMin(1, 0, n - 1, a - 1, b - 1) << ' ' << FindMax(1, 0, n - 1, a - 1, b - 1) << '\n';
	}
	return 0;
}