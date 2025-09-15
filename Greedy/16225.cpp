#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii; // pair<int,int>를 간단히 쓰기 위한 typedef
typedef long long ll;

int n, a[200000], b[200000];

// 문제 풀이 함수
ll Solve()
{
	vector<pii> v;
	// (b[i], a[i]) 쌍으로 벡터에 저장
	for (int i = 0; i < n; i++)
	{
		v.push_back(pii(b[i], a[i]));
	}
	sort(v.begin(), v.end()); // b를 기준으로 오름차순 정렬

	ll ret = v[0].second; // 첫 번째 a 값 더하기
	priority_queue<int> pq; // 최대 힙

	// 두 번째 이후 요소들을 2개씩 묶어서 처리
	for (int i = 1; i + 1 < n; i += 2)
	{
		pq.push(v[i].second);     // a 값 힙에 추가
		pq.push(v[i + 1].second); // a 값 힙에 추가
		ret += pq.top();           // 최대값을 결과에 더함
		pq.pop();                  // 최대값 제거
	}
	return ret;
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n;

	for (int i = 0; i < n; i++) cin >> a[i]; // a 배열 입력
	for (int i = 0; i < n; i++) cin >> b[i]; // b 배열 입력

	cout << Solve(); // 결과 출력
	return 0;
}
