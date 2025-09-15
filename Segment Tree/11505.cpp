#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int INF = 2e9;
const int MOD = 1e9 + 7;   // 모듈러 연산
const int MAX = 1e6;

int n, m, k;
int arr[MAX];       // 원본 배열
ll tree[MAX << 2];  // 세그먼트 트리 (4*N)


// 세그먼트 트리 초기화
ll Init(int node, int start, int end)
{
	if (start == end)
		return tree[node] = arr[start]; // 리프 노드
	else
		return tree[node] = Init(node * 2, start, (start + end) / 2) *
		                    Init(node * 2 + 1, (start + end) / 2 + 1, end) % MOD;
}

// 세그먼트 트리 업데이트 (index 위치 값을 val로 변경)
ll Update(int node, int start, int end, int index, ll val)
{
	if (start > index || end < index)
		return tree[node]; // 범위 밖이면 현재 값 유지
	if (start == index && end == index)
		return tree[node] = val; // 리프 노드 업데이트
	return tree[node] = Update(node * 2, start, (start + end) / 2, index, val) *
	                    Update(node * 2 + 1, (start + end) / 2 + 1, end, index, val) % MOD;
}

// 구간 곱 계산
ll Multiple(int node, int start, int end, int left, int right)
{
	if (start > right || end < left)
		return 1; // 범위 밖이면 곱 항등원 1
	if (left <= start && end <= right)
		return tree[node]; // 범위 안이면 노드 값 반환
	return Multiple(node * 2, start, (start + end) / 2, left, right) *
	       Multiple(node * 2 + 1, (start + end) / 2 + 1, end, left, right) % MOD;
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++) cin >> arr[i];

	Init(1, 0, n - 1); // 세그먼트 트리 초기화

	for (int i = 0; i < m + k; i++)
	{
		int a, b, c; cin >> a >> b >> c;
		if (a == 1)
		{
			Update(1, 0, n - 1, b - 1, c); // 값 업데이트
		}
		else
		{
			cout << Multiple(1, 0, n - 1, b - 1, c - 1) << '\n'; // 구간 곱 출력
		}
	}
	return 0;
}
