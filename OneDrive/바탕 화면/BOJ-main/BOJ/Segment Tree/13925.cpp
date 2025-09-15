#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;

// 곱셈, 덧셈 lazy propagation을 위한 구조체
struct Vector2LL
{
	Vector2LL() : x(1), y(0) {} // 기본값: 곱셈 1, 덧셈 0
	Vector2LL(int x, int y) : x(x), y(y) {}
	ll x, y;
};

int n, m;
ll a[100001];          // 초기 배열
ll tree[400004];       // 세그먼트 트리 (범위 합 저장)
Vector2LL lazy[400004]; // lazy propagation용 배열

// 세그먼트 트리 초기화
ll init(int node, int start, int end)
{
	if (start == end)
	{
		return tree[node] = a[start]; // 단일 노드
	}
	else
	{
		// 왼쪽과 오른쪽 합
		return tree[node] = (init(node * 2, start, (start + end) / 2) + 
		                     init(node * 2 + 1, (start + end) / 2 + 1, end)) % MOD;
	}
}

// lazy 값 적용
void update_lazy(int node, int start, int end)
{
	if (lazy[node].x != 1 || lazy[node].y != 0)
	{
		// 현재 노드에 lazy 적용
		tree[node] = (tree[node] * lazy[node].x + (end - start + 1) * lazy[node].y) % MOD;

		if (start != end)
		{
			// 자식에게 lazy 전파 (곱셈과 덧셈)
			lazy[node * 2].x = (lazy[node * 2].x * lazy[node].x) % MOD;
			lazy[node * 2].y = (lazy[node * 2].y * lazy[node].x + lazy[node].y) % MOD;

			lazy[node * 2 + 1].x = (lazy[node * 2 + 1].x * lazy[node].x) % MOD;
			lazy[node * 2 + 1].y = (lazy[node * 2 + 1].y * lazy[node].x + lazy[node].y) % MOD;
		}

		// 현재 노드 lazy 초기화
		lazy[node] = Vector2LL();
	}
}

// 범위 업데이트
// mtp: 곱셈 값, add: 덧셈 값
void update_range(int node, int start, int end, int left, int right, ll mtp, ll add)
{
	update_lazy(node, start, end); // 현재 노드 lazy 적용

	if (left > end || right < start) return; // 범위 벗어남
	if (left <= start && end <= right)
	{
		// 완전히 포함될 경우 lazy에 값 적용 후 즉시 업데이트
		lazy[node].x = (lazy[node].x * mtp) % MOD;
		lazy[node].y = (lazy[node].y * mtp + add) % MOD;
		update_lazy(node, start, end);
		return;
	}

	// 왼쪽, 오른쪽 자식 재귀 업데이트
	update_range(node * 2, start, (start + end) / 2, left, right, mtp, add);
	update_range(node * 2 + 1, (start + end) / 2 + 1, end, left, right, mtp, add);

	// 자식 합으로 현재 노드 갱신
	tree[node] = (tree[node * 2] + tree[node * 2 + 1]) % MOD;
}

// 범위 합 질의
ll sum(int node, int start, int end, int left, int right)
{
	update_lazy(node, start, end); // 현재 노드 lazy 적용

	if (left > end || right < start) return 0; // 범위 벗어남
	if (left <= start && end <= right) return tree[node]; // 범위 내 포함

	// 왼쪽, 오른쪽 합
	return (sum(node * 2, start, (start + end) / 2, left, right) +
	        sum(node * 2 + 1, (start + end) / 2 + 1, end, left, right)) % MOD;
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i]; // 초기 배열 입력
	}

	init(1, 1, n); // 세그먼트 트리 초기화

	cin >> m; // 쿼리 개수
	for (int i = 0; i < m; i++)
	{
		int t;
		cin >> t;
		int x, y;
		cin >> x >> y;
		ll v;
		if (t != 4) cin >> v;

		if (t == 1)
		{
			// 범위 덧셈
			update_range(1, 1, n, x, y, 1, v);
		}
		else if (t == 2)
		{
			// 범위 곱셈
			update_range(1, 1, n, x, y, v, 0);
		}
		else if (t == 3)
		{
			// 범위 단순 덧셈
			update_range(1, 1, n, x, y, 0, v);
		}
		else
		{
			// 범위 합 질의
			cout << sum(1, 1, n, x, y) << '\n';
		}
	}
}
