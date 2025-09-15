#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n, s;        // n: 배열 크기, s: 목표 합
int arr[40];     // 입력 배열
map<int, int> mp; // 첫 절반 부분합 저장 (합 -> 등장 횟수)
ll ans;          // 결과: 부분집합 합이 s인 경우의 수

// 배열의 첫 절반(0 ~ n/2-1) 부분집합 합 계산
void DFS1(int idx, int sum = 0)
{
    if (idx == n / 2)
    {
        mp[sum]++; // 해당 합 등장 횟수 증가
        return;
    }
    DFS1(idx + 1, sum);          // 현재 원소 포함 X
    DFS1(idx + 1, sum + arr[idx]); // 현재 원소 포함
}

// 배열의 두 번째 절반(n/2 ~ n-1) 부분집합 합 계산 및 첫 절반과 조합
void DFS2(int idx, int sum = 0)
{
    if (idx == n)
    {
        ans += mp[s - sum]; // 첫 절반에서 (s - 현재 합)인 경우 카운트
        return;
    }
    DFS2(idx + 1, sum);           // 현재 원소 포함 X
    DFS2(idx + 1, sum + arr[idx]); // 현재 원소 포함
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n >> s;
    for (int i = 0
