#include <bits/stdc++.h>
using namespace std;

const int INF = 2e9;          // 충분히 큰 값
const int MAX = 100000;       // 배열 최대 크기

int n, m;                     // n: 배열 크기, m: 쿼리 수
int arr[MAX];                  // 입력 배열
int minTree[MAX << 2];         // 세그먼트 트리 (최솟값용)
int maxTree[MAX << 2];         // 세그먼트 트리 (최댓값용)

// 최솟값 세그먼트 트리 초기화
int InitMin(int idx, int start, int end)
{
	if (start == end) // 리프 노드
	{
		return minTree[idx] = arr[start];
	}
	else
	{
		int mid = (start + end) / 2;
		// 왼쪽과 오른쪽 서브트리의 최솟값 비교
		return minTree[idx] = min(InitMin(idx * 2, start, mid), InitMin(idx * 2 + 1, mid + 1, end));
	}
}

// 최댓값 세그먼트 트리 초기화
int InitMax(int idx, int start, int end)
{
	if (start == end) // 리프 노드
	{
		return maxTree[idx] = arr[start];
	}
	else
	{
		int mid = (start + end) / 2;
		// 왼쪽과 오른쪽 서브트리의 최댓값 비교
		return maxTree[idx] = max(InitMax(idx * 2, start, mid), InitMax(idx * 2 + 1, mid + 1, end));
	}
}

// 구간 [left, right] 최솟값 조회
int FindMin(int node, int start, int end, int left, int right)
{
	// 범위를 벗어난 경우
	if (start > right || end < left)
		return INF;

	// 완전히 포함되는 경우
	if (left <= start && end <= right)
		return minTree[node];

	// 부분적으로 겹치는 경우
	return min(FindMin(node * 2, start, (start + end) / 2, left, right),
	           FindMin(node * 2 + 1, (start + end) / 2 + 1, end, left, right));
}

// 구간 [left, right] 최댓값 조회
int FindMax(int node, int start, int end, int left, int right)
{
	// 범위를 벗어난 경우
	if (start > right || end < left)
		return 0; // 최댓값이므로 0 반환 (입력 범위에 따라 적절히 수정 가능)

	// 완전히 포함되는 경우
	if (left <= start && end <= right)
		return maxTree[node];

	// 부분적으로 겹치는 경우
	return max(FindMax(node * 2, start, (start + end) / 2, left, right),
	           FindMax(node * 2 + 1, (start + end) / 2 + 1, end, left, right));
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	cin >> n >> m;

	// 배열 입력
	for (int i = 0; i < n; i++) cin >> arr[i];

	// 세그먼트 트리 초기화
	InitMin(1, 0, n - 1);
	InitMax(1, 0, n - 1);

	// 쿼리 처리
	for (int i = 0; i < m; i++)
	{
		int a, b; cin >> a >> b;
		// [a-1, b-1] 범위의 최솟값과 최댓값 출력
		cout << FindMin(1, 0, n - 1, a - 1, b - 1) << ' '
		     << FindMax(1, 0, n - 1, a - 1, b - 1) << '\n';
	}

	return 0;
}
