#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
const int MAX = 102;
const int ALPHA = 26;
const int DIR = 4;
char c[MAX][MAX];
bool vst[MAX][MAX];
pii dir[DIR] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int t; cin >> t;
	while (t--)
	{
		int h, w; cin >> h >> w;
		for (int i = 0; i <= h + 1; i++) c[i][0] = c[i][w + 1] = '.';
		for (int j = 0; j <= w + 1; j++) c[0][j] = c[h + 1][j] = '.';
		for (int i = 1; i <= h; i++)
		{
			cin.ignore();
			for (int j = 1; j <= w; j++)
			{
				c[i][j] = cin.get();
			}
		}
		string s;
		cin.ignore();
		getline(cin, s);
		bool key[ALPHA] = {};
		for (char t : s)
		{
			if ('a' <= t && t <= 'z')
			{
				key[t - 'a'] = true;
			}
		}
		queue<pii> q;
		q.push(pii(0, 0));
		for (int i = 0; i <= h + 1; i++)
		{
			for (int j = 0; j <= w + 1; j++)
			{
				vst[i][j] = false;
			}
		}
		vst[0][0] = true;
		vector<pii> d[ALPHA];
		int ans = 0;
		while (q.size())
		{
			pii curr = q.front(); q.pop();
			for (int i = 0; i < DIR; i++)
			{
				pii next = pii(curr.first + dir[i].first, curr.second + dir[i].second);
				if (0 > next.first || next.first > h + 1 || 0 > next.second || next.second > w + 1) continue;
				if (vst[next.first][next.second]) continue;
				if (c[next.first][next.second] == '.' || c[next.first][next.second] == '$' ||
					'a' <= c[next.first][next.second] && c[next.first][next.second] <= 'z' ||
					'A' <= c[next.first][next.second] && c[next.first][next.second] <= 'Z')
				{
					if ('A' <= c[next.first][next.second] && c[next.first][next.second] <= 'Z') if (!key[c[next.first][next.second] - 'A'])
					{
						d[c[next.first][next.second] - 'A'].push_back(next);
						continue;
					}
					vst[next.first][next.second] = true;
					q.push(next);
					if (c[next.first][next.second] == '$') ans++;
					else if ('a' <= c[next.first][next.second] && c[next.first][next.second] <= 'z')
					{
						key[c[next.first][next.second] - 'a'] = true;
						for (pii open : d[c[next.first][next.second] - 'a']) q.push(open);
					}
				}
			}
		}
		cout << ans << '\n';
	}
	return 0;
}