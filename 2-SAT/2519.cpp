#include <bits/stdc++.h>
using namespace std;

// 2D 점 구조체
struct Point
{
	int x, y;
	Point(int x, int y) : x(x), y(y) {}
};

// 선분 구조체
struct Line
{
	Point a, b;
	Line(Point a, Point b) : a(a), b(b) {}
};

int n; // n개의 3개 선택 옵션이 있는 아이템
int vst[6001], scc[6001]; // 방문 체크, SCC 번호
vector<int> adj[6001], rev[6001], dfn; // 그래프, 역그래프, DFS 순서
vector<Line> line; // 선분 정보

// 변수 x의 부정 값 반환 (2-SAT에서 x, not x 관계)
inline int Inverse(int x)
{
	if (x >= 3 * n) return x - 3 * n;
	else return x + 3 * n;
}

// CCW 계산 (선분 교차 여부 확인용)
int CCW(Point a, Point b, Point c)
{
	int res = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
	return res > 0 ? 1 : -1;
}

// 두 선분이 서로 교차하는지 확인
bool IsCross(Line A, Line B)
{
	int AB = CCW(A.a, A.b, B.a) * CCW(A.a, A.b, B.b);
	int BA = CCW(B.a, B.b, A.a) * CCW(B.a, B.b, A.b);
	return AB < 0 && BA < 0;
}

// 일반 DFS
void DFS(int v)
{
	vst[v] = 1;
	for (auto u : adj[v]) if (!vst[u]) DFS(u);
	dfn.push_back(v);
}

// 역 DFS (SCC 생성)
void RevDFS(int v, int color)
{
	scc[v] = color;
	for (auto u : rev[v]) if (!scc[u]) RevDFS(u, color);
}

// SCC 전체 계산 (Kosaraju)
void SCC(int n)
{
	memset(vst, 0, sizeof vst);
	for (int i = 0; i < 6 * n; i++) if (!vst[i]) DFS(i);
	reverse(dfn.begin(), dfn.end());
	int cnt = 1;
	for (auto i : dfn) if (!scc[i]) RevDFS(i, cnt++);
}

// 2-SAT 그래프에 x -> y 관계 추가
void AddEdge(int i, int j)
{
	adj[i].push_back(j);        // i가 true이면 j도 true
	rev[j].push_back(i);
	adj[Inverse(j)].push_back(Inverse(i)); // not j -> not i
	rev[Inverse(i)].push_back(Inverse(j));
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n;

	// 각 선분 정보 입력 (3*n개의 선분)
	for (int i = 0; i < 3 * n; i++)
	{
		int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
		line.push_back(Line(Point(x1, y1), Point(x2, y2)));
	}

	// 각 아이템에서 3개의 옵션 중 하나만 선택 가능하도록 조건 추가
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				if (j == k) continue;
				AddEdge(3 * i + j, Inverse(3 * i + k)); // 하나를 선택하면 나머지는 선택 불가
			}
		}
	}

	// 교차하는 선분끼리 동시에 선택 불가
	for (int i = 0; i < 3 * n; i++)
	{
		for (int j = i + 1; j < 3 * n; j++)
		{
			if (IsCross(line[i], line[j]))
			{
				AddEdge(Inverse(i), j); // i가 선택되면 j는 선택 불가
			}
		}
	}

	// SCC 계산 (2-SAT 해결)
	SCC(n);

	vector<int> ans;
	for (int i = 0; i < 3 * n; i++)
	{
		// 모순 체크: x와 not x가 같은 SCC에 있으면 불가능
		if (scc[i] == scc[Inverse(i)])
		{
			cout << -1;
			return 0;
		}
		// SCC 번호가 큰 쪽이 true
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
