#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int n;
ll a, b;
int c, d;
int ccnt;
int adj[500001], cn[500001], cs[500001];
bool vst[500001];
void DFS(int c)
{
	vst[c] = true;
	cn[c] = ccnt;
	cs[cn[c]]++;
	if (!vst[adj[c]]) DFS(adj[c]);
}
ll GCD(ll p, ll q)
{
	while (q)
	{
		ll r = p % q;
		p = q;
		q = r;
	}
	return p;
}
ll LCM(ll p, ll q)
{
	return p / GCD(p, q) * q;
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n >> a >> b >> c >> d;
	for (int i = 1; i <= n; i++) cin >> adj[i];
	for (int i = 1; i <= n; i++)
	{
		if (!vst[i]) DFS(i);
		ccnt++;
	}
	ll lcm = 1;
	for (int i = 1 + c; i <= n - d; i++) lcm = LCM(lcm, cs[cn[i]]);
	cout << (b + lcm - 1) / lcm - (a + lcm - 2) / lcm;
	return 0;
}