#include <bits/stdc++.h>
using namespace std;

const int INF = 2e9;        // 무한대 값
const int MAX = 100001;      // 최대 배열 크기
int arr[MAX];                // 실제 값 저장 배열
int tree[MAX << 2];          // 세그먼트 트리 (최솟값 인덱스 저장)

// 세그먼트 트리 초기화 (최솟값 인덱스 저장)
int Init(int node, int start, int end)
{
	if (start == end)
		return tree[node] = start;  // 단일 노드는 자기 자신 인덱스 반환
	else
	{
		int l = Init(node * 2, start, (start + end) / 2);      // 왼쪽 자식 초기화
		int r = Init(node * 2 + 1, (start + end) / 2 + 1, end); // 오른쪽 자식 초기화
		if (arr[l] <= arr[r]) return tree[node] = l;           // 더 작은 값의 인덱스 저장
		else return tree[node] = r;
	}
}

// 세그먼트 트리 업데이트 (index 위치 값 변경 시)
int Update(int node, int start, int end, int index)
{
	if (start > index || end < index)   // 범위 밖이면 그대로 반환
		return tree[node];
	if (start == index && end == index) // 단일 노드라면 인덱스 반환
		return tree[node] = index;

	int l = Update(node * 2, start, (start + end) / 2, index);      // 왼쪽 갱신
	int r = Update(node * 2 + 1, (start + end) / 2 + 1, end, index); // 오른쪽 갱신
	if (arr[l] <= arr[r]) return tree[node] = l;                     // 최소값 인덱스 갱신
	else return tree[node] = r;
}

// 구간 [left, right]의 최솟값 인덱스 반환
int Minimum(int node, int start, int end, int left, int right)
{
	if (start > right || end < left)   // 구간 밖이면 무시
		return 0;                       // arr[0] = INF로 초기화했으므로 안전
	if (left <= start && end <= right) // 구간 내라면 노드 반환
		return tree[node];

	int l = Minimum(node * 2, start, (start + end) / 2, left, right);       // 왼쪽 탐색
	int r = Minimum(node * 2 + 1, (start + end) / 2 + 1, end, left, right); // 오른쪽 탐색
	if (arr[l] <= arr[r]) return l;  // 최소값 인덱스 반환
	else return r;
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n; cin >> n;            // 배열 크기 입력
	arr[0] = INF;               // 0번 인덱스는 INF로 초기화
	for (int i = 1; i <= n; i++) cin >> arr[i];  // 배열 입력
	Init(1, 1, n);              // 세그먼트 트리 초기화

	int m; cin >> m;            // 쿼리 수 입력
	for (int i = 0; i < m; i++)
	{
		int a, b, c; cin >> a >> b >> c;
		if (a == 1)
		{
			arr[b] = c;          // 배열 값 갱신
			Update(1, 1, n, b);  // 세그먼트 트리 업데이트
		}
		else
		{
			cout << Minimum(1, 1, n, b, c) << '\n'; // 구간 최솟값 인덱스 출력
		}
	}
	return 0;
}
