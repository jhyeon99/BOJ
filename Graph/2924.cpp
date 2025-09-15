#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n;                // 총 원소 수
ll a, b;              // 범위 [a, b]에서 LCM 배수 개수 계산
int c, d;             // 제외할 앞 c개, 뒤 d개 인덱스
int ccnt;             // 사이클 개수 카운트
int adj[500001];      // 각 노드가 가리키는 노드 (1-indexed)
int cn[500001];       // 노드가 속한 사이클 번호
int cs[500001];       // 각 사이클의 크기
bool vst[500001];     // 방문 여부

// DFS로 사이클 탐색 및 사이클 크기 계산
void DFS(int c)
{
    vst[c] = true;
    cn[c] = ccnt;       // 현재 노드의 사이클 번호
    cs[cn[c]]++;        // 해당 사이클 크기 증가
    if (!vst[adj[c]]) DFS(adj[c]);  // 다음 노드 방문
}

// 최대공약수 계산 (유클리드 호제법)
ll GCD(ll p, ll q)
{
    while (q)
    {
        ll r = p % q;
        p = q;
        q = r;
    }
    return p;
}

// 최소공배수 계산
ll LCM(ll p, ll q)
{
    return p / GCD(p, q) * q;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    // 입력 받기
    cin >> n >> a >> b >> c >> d;
    for (int i = 1; i <= n; i++) cin >> adj[i];  // 각 원소가 가리키는 위치

    // 사이클 탐색
    for (int i = 1; i <= n; i++)
    {
        if (!vst[i]) DFS(i);
        ccnt++;  // 새로운 사이클 번호 증가
    }

    // 범위 [1+c, n-d]의 사이클 크기들의 LCM 계산
    ll lcm = 1;
    for (int i = 1 + c; i <= n - d; i++) 
        lcm = LCM(lcm, cs[cn[i]]);

    // 범위 [a, b]에서 LCM 배수 개수 계산
    cout << (b + lcm - 1) / lcm - (a + lcm - 2) / lcm;
    
    return 0;
}
