#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using cpx = complex<ld>;
const long double PI = acos(-1);

// 다항식 분할 저장용
vector<ll> a1, a2, b1, b2;
vector<ll> a1b1, a1b2, a2b1, a2b2;

// FFT 구현 (Cooley-Tukey)
void FFT(vector<cpx>& a, bool invert)
{
    int n = a.size();
    // 비트 반전 순서 정렬
    for (int i = 1, j = 0; i < n; i++)
    {
        ll bit = n >> 1;
        for (; j >= bit; bit >>= 1) j -= bit;
        j += bit;
        if (i < j) swap(a[i], a[j]);
    }

    // 길이 len의 블록으로 FFT 수행
    for (int len = 2; len <= n; len <<= 1)
    {
        ld ang = 2 * PI / len * (invert ? -1 : 1);
        cpx wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len)
        {
            cpx w(1);
            for (int j = 0; j < len / 2; j++)
            {
                cpx u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }

    // 역 FFT 시 나누기 n
    if (invert)
    {
        for (int i = 0; i < n; i++) a[i] /= n;
    }
}

// 다항식 곱셈
void Multiply(vector<ll>& r, const vector<ll>& a, const vector<ll>& b)
{
    vector<cpx> ca(a.begin(), a.end()), cb(b.begin(), b.end());
    int n = 1;
    while (n <= a.size() || n <= b.size()) n <<= 1;
    n <<= 1; // 충분히 큰 2의 거듭제곱
    ca.resize(n); cb.resize(n);

    FFT(ca, false);
    FFT(cb, false);

    for (int i = 0; i < n; i++) ca[i] *= cb[i];
    FFT(ca, true);

    r.resize(n);
    for (int i = 0; i < n; i++)
        r[i] = ll(ca[i].real() + (ca[i].real() > 0 ? 0.5 : -0.5));
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    int a, b;

    // 다항식 계수 분할 (상위 10비트, 하위 10비트)
    for (int i = 0; i < n + 1; i++)
    {
        cin >> a;
        a1.push_back(a >> 10);          // 상위 10비트
        a2.push_back(a & ((1 << 10) - 1)); // 하위 10비트
    }
    for (int i = 0; i < m + 1; i++)
    {
        cin >> b;
        b1.push_back(b >> 10);
        b2.push_back(b & ((1 << 10) - 1));
    }

    // 다항식 곱셈: Karatsuba 스타일 분할 곱
    Multiply(a1b1, a1, b1);
    Multiply(a1b2, a1, b2);
    Multiply(a2b1, a2, b1);
    Multiply(a2b2, a2, b2);

    ll ans = 0;
    // 최종 계수 합성 후 XOR
    for (int i = 0; i < n + m + 1; i++)
    {
        ll ab = (a1b1[i] << 20) + ((a1b2[i] + a2b1[i]) << 10) + a2b2[i];
        ans ^= ab;
    }

    cout << ans;
    return 0;
}
