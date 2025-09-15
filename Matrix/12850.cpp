#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MOD = 1000000007; // 결과 모듈로
const int MAX = 8;           // 행렬 크기

// 행렬 구조체
struct Matrix
{
    ll matrix[MAX][MAX];
    
    // 행렬 곱 연산 정의
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
                ret.matrix[i][j] %= MOD; // MOD 연산
            }
        }
        return ret;
    }
};

// 문제에서 주어진 초기 경로 행렬
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

// 행렬의 거듭제곱을 계산 (분할 정복)
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

    int d; 
    cin >> d; // 이동 횟수

    // 행렬 거듭제곱 계산
    route = MatrixPow(route, d);

    // 결과 출력: 출발점에서 d번 이동 후 자기 자신으로 돌아오는 경로 수
    cout << route.matrix[0][0];
    return 0;
}
