#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MOD = 1000003; // 답 MOD 연산
const int MAX = 50;      // 최대 노드 수

// 행렬 구조체 정의
struct Matrix
{
    ll matrix[MAX][MAX] = { {} };

    // 행렬 곱셈
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

// 행렬 거듭제곱
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

    int n, s, e, t;
    cin >> n >> s >> e >> t;
    s--, e--; // 0-indexed

    Matrix route;

    // 각 정점을 5단계 상태로 확장 (1~4 단계 이동)
    for (int i = 0; i < n; i++)
        for (int j = 1; j < 5; j++)
            route.matrix[i * 5 + j][i * 5 + j - 1] = 1;

    // 입력 그래프 처리
    for (int i = 0; i < n; i++)
    {
        string str; cin >> str;
        for (int j = 0; j < n; j++)
        {
            int t = str[j] - '0';
            if (t) route.matrix[i * 5][j * 5 + t - 1] = 1;
        }
    }

    // t 시간 후 경로 수 계산
    Matrix ans = MatrixPow(route, t);

    cout << ans.matrix[s * 5][e * 5]; // 시작 -> 끝 경로 수
    return 0;
}
