#include <bits/stdc++.h>

using namespace std;

const int MAX = 1000000;

int failFunc[MAX];
vector<int> ans;

void CalcFailFunc(string s) {
	for (int i = 1, j = 0; i < s.length(); i++) {
		while (j && s[i] != s[j]) {
			j = failFunc[j - 1];
		}
		if (s[i] == s[j]) {
			j++;
		}
		failFunc[i] = j;
	}
}

void KMP(string t, string p) {
	for (int i = 0, j = 0; i < t.length(); i++) {
		while (j && t[i] != p[j]) {
			j = failFunc[j - 1];
		}
		if (t[i] == p[j]) {
			if (++j == p.length()) {
				j = failFunc[j - 1];
				ans.push_back(i - p.length() + 2);
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	string t, p;
	getline(cin, t);
	getline(cin, p);

	CalcFailFunc(p);
	KMP(t, p);

	cout << ans.size() << '\n';
	for (int a : ans) {
		cout << a << ' ';
	}
	return 0;
}