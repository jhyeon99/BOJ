#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAX = 5e5;
int a[MAX];
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n; cin >> n;
	for (int i = 0; i < n; i++) cin >> a[i];
	deque<int> s;
	s.push_front(a[0]);
	ll ans = 0;
	for (int i = 1; i < n; i++)
	{
		ans += min((int)s.size(), (int)(upper_bound(s.begin(), s.end(), a[i]) - s.begin()) + 1);
		while (s.front() < a[i])
		{
			s.pop_front();
			if (s.empty()) break;
		}
		s.push_front(a[i]);
	}
	cout << ans;
	return 0;
}