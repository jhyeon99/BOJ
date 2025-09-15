#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
const int MAX = 100000;

// 3차원 좌표를 가진 점 구조체
struct Vector3Int
{
	int x, y, z, idx;  // 좌표와 원래 인덱스
	Vector3Int() {}
	Vector3Int(int x, int y, int z, int idx) : x(x), y(y), z(z), idx(idx) {}
	int Coordinate(int i)  // i번째 좌표 반환: 0->x,1->y,2->z
	{
		switch (i)
		{
		case 0: return x;
		case 1: return y;
		case 2: return z;
		default: return 0;
		}
	}
	Vector3Int operator=(Vector3Int v)
	{
		x = v.x, y = v.y, z = v.z, idx = v.idx;
		return Vector3Int(x, y, z, idx);
	}
};

// 좌표 기준 정렬 함수
bool CompareByX(Vector3Int v1, Vector3Int v2){ return v1.x < v2.x; }
bool CompareByY(Vector3Int v1, Vector3Int v2){ return v1.y < v2.y; }
bool CompareByZ(Vector3Int v1, Vector3Int v2){ return v1.z < v2.z; }

Vector3Int p[3][MAX];  // x, y, z 기준으로 정렬된 점들 저장
vector<pii> adj[MAX];  // MST 그래프 인접리스트 (가중치, 인접점)
bool vst[MAX];         // 방문 여부

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n; cin >> n;

	// 점 입력
	for (int i = 0; i < n; i++)
	{
		cin >> p[0][i].x >> p[0][i].y >> p[0][i].z;
		p[0][i].idx = i;
		p[1][i] = p[0][i];  // y 기준, z 기준 배열 초기화
		p[2][i] = p[0][i];
	}

	// 좌표별 정렬 후 인접한 점끼리 간선 추가
	bool (*compare[3])(Vector3Int, Vector3Int) = { CompareByX, CompareByY, CompareByZ };
	for (int i = 0; i < 3; i++)
	{
		sort(p[i], p[i] + n, compare[i]);
		for (int j = 0; j < n - 1; j++)
		{
			int w = p[i][j + 1].Coordinate(i) - p[i][j].Coordinate(i);
			int u = p[i][j].idx;
			int v = p[i][j + 1].idx;
			adj[u].push_back({w, v});
			adj[v].push_back({w, u});
		}
	}

	// 프림(Prim) 알고리즘으로 MST 계산
	priority_queue<pii, vector<pii>, greater<pii>> pq;
	pq.push({0, 0});  // 시작점 0
	int ans = 0;

	while (!pq.empty())
	{
		int weight = pq.top().first;
		int curr = pq.top().second;
		pq.pop();

		if (vst[curr]) continue;  // 이미 MST에 포함
		vst[curr] = true;
		ans += weight;

		for (auto nextP : adj[curr])
		{
			int next = nextP.second;
			if (!vst[next])
				pq.push(nextP);  // 인접점 MST 후보로 추가
		}
	}

	cout << ans;
	return 0;
}
