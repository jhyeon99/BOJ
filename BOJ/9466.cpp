#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;
const int MAX = 100001;
int s[MAX], ans;
int dep[MAX];
bool vst[MAX];
void DFS(int curr, int depth)
{
	dep[curr] = depth;
	int next = s[curr];
	if (!vst[next])
	{
		vst[next] = true;
		DFS(next, depth + 1);
	}
	else if (dep[next] != INF) ans -= depth + 1 - dep[next];
	dep[curr] = INF;
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int t; cin >> t;
	while (t--)
	{
		int n; cin >> n;
		for (int i = 1; i <= n; i++) cin >> s[i];
		for (int i = 1; i <= n; i++)
		{
			dep[i] = 0;
			vst[i] = false;
		}
		ans = n;
		for (int i = 1; i <= n; i++) if (!vst[i]) DFS(i, 0);
		cout << ans << '\n';
	}
	return 0;
}