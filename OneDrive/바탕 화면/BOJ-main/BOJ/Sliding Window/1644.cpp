#include <bits/stdc++.h>
using namespace std;
const int MAX = 4000001;
bool isPrime[MAX];
vector<int> prime;
void Seive()
{
	for (int i = 2; i < MAX; i++) isPrime[i] = true;
	for (int i = 2; i * 2 < MAX; i++) {
		if (!isPrime[i]) continue;
		for (int j = 2; i * j < MAX; j++) {
			isPrime[i * j] = false;
		}
	}
	for (int i = 2; i < MAX; i++) if (isPrime[i]) prime.push_back(i);
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n; cin >> n;
	Seive();
	int l = 0, r = 0, s = prime[0], a = 0;
	while (true)
	{
		if (s <= n)
		{
			if (s == n) a++;
			if (++r == prime.size()) break;
			s += prime[r];
		}
		else
		{
			s -= prime[l++];
		}

	}
	cout << a;
	return 0;
}