#include <bits/stdc++.h>
using namespace std;
struct Query
{
	int i, j, order;
	Query() {}
	Query(int i, int j, int order) : i(i), j(j), order(order) {}
};
int a[100000], ans[100000];
int cnt[1000001], uniqueCnt;
Query q[100000];
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
			int aIdx = a.j / sqrt(n);
			int bIdx = b.j / sqrt(n);
			return aIdx == bIdx ? a.i < b.i : aIdx < bIdx;
		});
	int ci = 0, cj = 0;
	if (!cnt[a[0]]++) { uniqueCnt++; }
	for (int i = 0; i < m; i++)
	{
		int ni = q[i].i, nj = q[i].j;
		for (int i = ci; i < ni; i++) if (!--cnt[a[i]]) { uniqueCnt--; }
		for (int i = ci - 1; i >= ni; i--) if (!cnt[a[i]]++) { uniqueCnt++; }
		for (int i = cj + 1; i <= nj; i++) if (!cnt[a[i]]++) { uniqueCnt++; }
		for (int i = cj; i > nj; i--) if (!--cnt[a[i]]) { uniqueCnt--; }
		ci = ni, cj = nj;
		ans[q[i].order] = uniqueCnt;
	}
	for (int i = 0; i < m; i++) cout << ans[i] << '\n';
	return 0;
}