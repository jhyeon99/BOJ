#include <bits/stdc++.h>
using namespace std;
const int INF = 2e9;
const int MAX = 1000000;
int arr[MAX];
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n; cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
	}
	sort(arr, arr + n);
	int ans = INF;
	pair<int, int> p;
	for (int i = 0; i < n; i++)
	{
		int l = 0, r = n - 1;
		while (l <= r)
		{
			if (l == r)
			{
				if (i == l)
				{
					if (l == 0) l = 1;
					else if (l == n - 1) l = n - 2;
					else
					{
						if (abs(arr[i] + arr[l - 1]) < abs(arr[i] + arr[l + 1])) l--;
						else l++;
					}
				}
				if (ans > abs(arr[i] + arr[l]))
				{
					ans = abs(arr[i] + arr[l]);
					p = make_pair(i, l);
				}
				break;
			}
			int m1 = (l + r) / 2, m2 = m1 + 1;
			if (abs(arr[i] + arr[m1]) < abs(arr[i] + arr[m2]))
			{
				r = m1;
			}
			else
			{
				l = m2;
			}
		}
	}
	cout << arr[p.first] << ' ' << arr[p.second];
	return 0;
}