#include <bits/stdc++.h>
using namespace std;
const int INF = 1234567890;
struct Query
{
	int i, j, order;
	Query() {}
	Query(int i, int j, int order) : i(i), j(j), order(order) {}
};
int a[100000], ans[100000];
Query q[100000];
int cnt1[100001], cnt2[100001], maxOfCnt;
void Push(int n)
{
	cnt2[cnt1[n]++]--;
	maxOfCnt = max(maxOfCnt, cnt1[n]);
	cnt2[cnt1[n]]++;
}
void Pop(int n)
{
	cnt2[cnt1[n]--]--;
	if (!cnt2[maxOfCnt]) maxOfCnt--;
	cnt2[cnt1[n]]++;
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n; cin >> n;
	for (int i = 0; i < n; i++) cin >> a[i];
	int m; cin >> m;
	for (int k = 0; k < m; k++)
	{
		int i, j; cin >> i >> j;
		q[k] = Query(i - 1, j - 1, k);
	}
	sort(q, q + m, [&](const Query& a, const Query& b)
		{
			int aIdx = a.j / sqrt(n), bIdx = b.j / sqrt(n);
			return aIdx == bIdx ? a.i < b.i : aIdx < bIdx;
		});
	int ci = 0, cj = 0;
	cnt2[0] = INF;
	Push(a[0]);
	for (int i = 0; i < m; i++)
	{
		while (ci < q[i].i) Pop(a[ci++]);
		while (ci > q[i].i) Push(a[--ci]);
		while (cj < q[i].j) Push(a[++cj]);
		while (cj > q[i].j) Pop(a[cj--]);
		ans[q[i].order] = maxOfCnt;
	}
	for (int i = 0; i < m; i++) cout << ans[i] << '\n';
	return 0;
}