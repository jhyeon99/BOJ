#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 1000003;
const int MAX = 50;
struct Matrix
{
	ll matrix[MAX][MAX] = { {} };
	const Matrix operator*(const Matrix& m) const
	{
		Matrix ret;
		for (int i = 0; i < MAX; i++)
		{
			for (int j = 0; j < MAX; j++)
			{
				for (int k = 0; k < MAX; k++)
				{
					ret.matrix[i][j] += matrix[i][k] * m.matrix[k][j];
				}
				ret.matrix[i][j] %= MOD;
			}
		}
		return ret;
	}
};
Matrix MatrixPow(Matrix base, int exp)
{
	if (exp == 1) return base;
	Matrix ret = MatrixPow(base, exp >> 1);
	ret = ret * ret;
	if (exp & 1) ret = ret * base;
	return ret;
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n, s, e, t; cin >> n >> s >> e >> t;
	s--, e--;
	Matrix route;
	for (int i = 0; i < n; i++)
		for (int j = 1; j < 5; j++)
			route.matrix[i * 5 + j][i * 5 + j - 1] = 1;
	for (int i = 0; i < n; i++)
	{
		string str; cin >> str;
		for (int j = 0; j < n; j++)
		{
			int t = str[j] - '0';
			if (t) route.matrix[i * 5][j * 5 + t - 1] = 1;
		}
	}
	Matrix ans = MatrixPow(route, t);
	cout << ans.matrix[s * 5][e * 5];
	return 0;
}