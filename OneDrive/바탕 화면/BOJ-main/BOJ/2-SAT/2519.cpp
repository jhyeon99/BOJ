#include <bits/stdc++.h>
using namespace std;
struct Point
{
	int x, y;
	Point(int x, int y) : x(x), y(y) {}
};
struct Line
{
	Point a, b;
	Line(Point a, Point b) : a(a), b(b) {}
};
int n;
int vst[6001], scc[6001];
vector<int> adj[6001], rev[6001], dfn;
vector<Line> line;
inline int Inverse(int x)
{
	if (x >= 3 * n) return x - 3 * n;
	else return x + 3 * n;
}
int CCW(Point a, Point b, Point c)
{
	int res = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
	return res > 0 ? 1 : -1;
}
bool IsCross(Line A, Line B)
{
	int AB = CCW(A.a, A.b, B.a) * CCW(A.a, A.b, B.b);
	int BA = CCW(B.a, B.b, A.a) * CCW(B.a, B.b, A.b);
	return AB < 0 && BA < 0;
}
void DFS(int v)
{
	vst[v] = 1;
	for (auto u : adj[v]) if (!vst[u]) DFS(u);
	dfn.push_back(v);
}
void RevDFS(int v, int color)
{
	scc[v] = color;
	for (auto u : rev[v]) if (!scc[u]) RevDFS(u, color);
}
void SCC(int n)
{
	memset(vst, 0, sizeof vst);
	for (int i = 0; i < 6 * n; i++) if (!vst[i]) DFS(i);
	reverse(dfn.begin(), dfn.end());
	int cnt = 1;
	for (auto i : dfn) if (!scc[i]) RevDFS(i, cnt++);
}
void AddEdge(int i, int j)
{
	adj[i].push_back(j);
	rev[j].push_back(i);
	adj[Inverse(j)].push_back(Inverse(i));
	rev[Inverse(i)].push_back(Inverse(j));
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n;
	for (int i = 0; i < 3 * n; i++)
	{
		int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
		line.push_back(Line(Point(x1, y1), Point(x2, y2)));
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				if (j == k) continue;
				AddEdge(3 * i + j, Inverse(3 * i + k));
			}
		}
	}
	for (int i = 0; i < 3 * n; i++)
	{
		for (int j = i + 1; j < 3 * n; j++)
		{
			if (IsCross(line[i], line[j]))
			{
				AddEdge(Inverse(i), j);
			}
		}
	}
	SCC(n);
	vector<int> ans;
	for (int i = 0; i < 3 * n; i++)
	{
		if (scc[i] == scc[Inverse(i)])
		{
			cout << -1;
			return 0;
		}
		if (scc[i] > scc[Inverse(i)])
		{
			ans.push_back(i + 1);
		}
	}
	cout << ans.size() << '\n';
	for (auto i : ans)
	{
		cout << i << ' ';
	}
	return 0;
}