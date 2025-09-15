#include <bits/stdc++.h>
using namespace std;

int n;
int a[1000];                     // 배열
vector<pair<int, int>> ans;      // 뒤집은 구간 저장

// 배열을 최대한 연속 증가/감소 구간으로 분할하는 함수
vector<int> Split()
{
	vector<int> ret;
	int way = 0;
	ret.push_back(0); // 시작 인덱스
	for (int i = 1; i < n - 1; i++)
	{
		// 연속 증가/감소가 아닌 위치를 분할점으로 선택
		if (!(a[i - 1] - a[i] == 1 && a[i] - a[i + 1] == 1
			|| a[i - 1] - a[i] == -1 && a[i] - a[i + 1] == -1))
		{
			ret.push_back(i);
		}
	}
	ret.push_back(n - 1); // 마지막 인덱스
	return ret;
}

// DFS 기반 구간 뒤집기 탐색
bool DFS(int c) // c = 현재까지 뒤집기 횟수
{
	// 배열이 정렬되었는지 확인
	bool isSort = true;
	for (int i = 0; i < n; i++)
	{
		if (a[i] != i + 1) isSort = false;
	}

	// 최대 3번까지 뒤집기를 시도
	if (c == 3) return isSort;

	// 이미 정렬되어있다면 나머지 뒤집기 구간은 (0,0)으로 채움
	if (c < 3 && isSort)
	{
		for (int i = 0; i < 3 - c; i++)
		{
			ans.push_back(make_pair(0, 0));
		}
		return true;
	}

	// 배열을 연속 증가/감소 구간으로 분할
	vector<int> split = Split();
	for (int i = 0; i < split.size(); i++)
	{
		for (int j = i; j < split.size(); j++)
		{
			int s = split[i], e = split[j];
			if (s > e) swap(s, e);

			// 구간 뒤집기
			reverse(a + s, a + e + 1);

			// DFS 재귀
			if (DFS(c + 1))
			{
				ans.push_back(make_pair(s, e));
				return true;
			}

			// 되돌리기
			reverse(a + s, a + e + 1);
		}
	}
	return false;
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}

	DFS(0);

	// 뒤집은 구간 출력 (역순으로 출력해야 실제 순서대로 적용)
	for (int i = ans.size() - 1; i >= 0; i--)
	{
		cout << ans[i].first + 1 << ' ' << ans[i].second + 1 << '\n';
	}

	return 0;
}
