#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

vector<pii> v;  // 왼쪽과 오른쪽이 뒤집힌 구간 저장

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n, m; 
	cin >> n >> m;  // n: 구간 개수, m: 기본 길이

	for (int i = 0; i < n; i++)
	{
		int from, to; 
		cin >> from >> to;
		if (from > to)  // 거꾸로 되어 있는 구간만 고려
			v.push_back(pii(to, from));
	}

	// 구간의 시작점 기준으로 오름차순 정렬
	sort(v.begin(), v.end());

	ll ans = m;   // 기본 길이
	int left = -1, right = -1;

	// 구간 합병
	for (pii p : v)
	{
		if (p.first > right)  // 이전 구간과 겹치지 않으면
		{
			ans += 2 * (right - left);  // 이전 구간 길이 추가
			left = p.first;
			right = p.second;
		}
		else 
			right = max(right, p.second);  // 겹치면 오른쪽 끝 갱신
	}

	// 마지막 구간 길이 처리
	ans += 2 * (right - left);

	cout << ans;
	return 0;
}
