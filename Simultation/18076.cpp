#include <bits/stdc++.h>
using namespace std;

int d[500][500]; // 입력 행렬 및 계산용 배열

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n; 
    cin >> n; // 행렬 크기

    // 행렬 입력 (문자 '0'~'9'를 숫자로 변환)
    for (int i = 0; i < n; i++)
    {
        cin.get(); // 개행 문자 제거
        for (int j = 0; j < n; j++)
        {
            d[i][j] = cin.get() - '0';
        }
    }

    // 행렬 변환
    for (int e = 1; e < n; e++) // 기준 행
    {
        for (int s = 0; s < e; s++) // 비교 행
        {
            if (d[s][e]) // 기준 열이 0이 아니면
            {
                for (int i = 0; i < n; i++) // 모든 열에 대해
                {
                    d[s][i] -= d[e][i]; // 기준 행 빼기
                    d[s][i] = (d[s][i] + 10) % 10; // 0~9로 변환 (mod 10)
                }
            }
        }
    }

    // 결과 출력
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << d[i][j];
        }
        cout << '\n';
    }

    return 0;
}
