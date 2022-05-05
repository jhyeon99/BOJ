#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 1000000007;
const int MAX = 8;
struct Matrix
{
	ll matrix[MAX][MAX];
	const Matrix operator*(const Matrix& m) const
	{
		Matrix ret = { {} };
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
Matrix route =
{
	{
	{0, 1, 1, 0, 0, 0, 0, 0},
	{1, 0, 1, 1, 0, 0, 0, 0},
	{1, 1, 0, 1, 1, 0, 0, 0},
	{0, 1, 1, 0, 1, 1, 0, 0},
	{0, 0, 1, 1, 0, 1, 1, 0},
	{0, 0, 0, 1, 1, 0, 0, 1},
	{0, 0, 0, 0, 1, 0, 0, 1},
	{0, 0, 0, 0, 0, 1, 1, 0}
	}
};
Matrix MatrixPow(Matrix base, int exp)
{
	if (exp == 1) return base;
	if (exp & 1) {
		return MatrixPow(base, exp - 1) * base;
	}
	else {
		Matrix x = MatrixPow(base, exp >> 1);
		return x * x;
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int d; cin >> d;
	route = MatrixPow(route, d);
	cout << route.matrix[0][0];
	return 0;
}