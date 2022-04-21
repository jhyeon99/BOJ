#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
const int MAX = 100000;
struct Vector3Int
{
	int x, y, z, idx;
	Vector3Int() {}
	Vector3Int(int x, int y, int z, int idx) : x(x), y(y), z(z), idx(idx) {}
	int Coordinate(int i)
	{
		switch (i)
		{
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		default:
			return 0;
		}
	}
	Vector3Int operator=(Vector3Int v)
	{
		x = v.x, y = v.y, z = v.z, idx = v.idx;
		return Vector3Int(x, y, z, idx);
	}
};
bool CompareByX(Vector3Int v1, Vector3Int v2)
{
	return v1.x < v2.x;
}
bool CompareByY(Vector3Int v1, Vector3Int v2)
{
	return v1.y < v2.y;
}
bool CompareByZ(Vector3Int v1, Vector3Int v2)
{
	return v1.z < v2.z;
}
Vector3Int p[3][MAX];
vector<pii> adj[MAX];
bool vst[MAX];
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n; cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> p[0][i].x >> p[0][i].y >> p[0][i].z;
		p[0][i].idx = i;
		p[1][i] = p[0][i];
		p[2][i] = p[0][i];
	}
	bool (*compare[3])(Vector3Int, Vector3Int) = { CompareByX, CompareByY, CompareByZ };
	for (int i = 0; i < 3; i++)
	{
		sort(p[i], p[i] + n, compare[i]);
		for (int j = 0; j < n - 1; j++)
		{
			adj[p[i][j].idx].push_back(pii(p[i][j + 1].Coordinate(i) - p[i][j].Coordinate(i), p[i][j + 1].idx));
			adj[p[i][j + 1].idx].push_back(pii(p[i][j + 1].Coordinate(i) - p[i][j].Coordinate(i), p[i][j].idx));
		}
	}
	priority_queue<pii, vector<pii>, greater<pii>> pq;
	pq.push(pii(0, 0));
	int ans = 0;
	while (pq.size())
	{
		int weight = pq.top().first;
		int curr = pq.top().second;
		pq.pop();
		if (vst[curr]) continue;
		vst[curr] = true;
		ans += weight;
		for (auto nextP : adj[curr])
		{
			int next = nextP.second;
			if (!vst[next])
			{
				pq.push(nextP);
			}
		}
	}
	cout << ans;
	return 0;
}