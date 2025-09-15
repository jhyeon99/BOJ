#include <bits/stdc++.h>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int d, p, q;
	cin >> d >> p >> q;
	if (p < q) swap(p, q);

	int n = ceil((double)d / p), m = 0;
	int ans = p * n;
	while (n) {
		n--;
		m += ceil((double)(d - (p * n + q * m)) / q);

		if (ans == p * n + q * m) {
			break;
		}
		ans = min(ans, p * n + q * m);
		if (ans == d) {
			break;
		}
	}
	cout << ans;
	return 0;
}