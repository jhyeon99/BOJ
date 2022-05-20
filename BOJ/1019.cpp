#include <bits/stdc++.h>
using namespace std;
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n; cin >> n;
	int arr[10] = {};
	for (int curr = n, e = 1; curr; e *= 10)
	{
		int t = curr % 10, next = curr / 10;
		for (int i = 0; i < 10; i++)
			arr[i] += (next + (1 <= i && i <= t)) * e;
		arr[t] -= e - (n % e) - 1;
		curr = next;
	}
	for (int i = 0; i < 10; i++)
		cout << arr[i] << ' ';
	return 0;
}