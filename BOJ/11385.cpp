#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using cpx = complex<ld>;
const long double PI = acos(-1);
vector<ll> a1, a2, b1, b2, a1b1, a1b2, a2b1, a2b2;
void FFT(vector<cpx>& a, bool invert)
{
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++)
    {
        ll bit = n >> 1;
        for (; j >= bit; bit >>= 1) j -= bit;
        j += bit;
        if (i < j) swap(a[i], a[j]);
    }
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
    if (invert)
    {
        for (int i = 0; i < n; i++) a[i] /= n;
    }
}
void Multiply(vector<ll>& r, const vector<ll>& a, const vector<ll>& b)
{
    vector<cpx> ca(a.begin(), a.end()), cb(b.begin(), b.end());
    int n = 1;
    while (n <= a.size() || n <= b.size()) n <<= 1;
    n <<= 1;
    ca.resize(n); cb.resize(n);
    FFT(ca, false); FFT(cb, false);
    for (int i = 0; i < n; i++) ca[i] *= cb[i];
    FFT(ca, true);
    r.resize(n);
    for (int i = 0; i < n; i++) r[i] = ll(ca[i].real() + (ca[i].real() > 0 ? 0.5 : -0.5));
}
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n; cin >> m;
    int a, b;
    for (int i = 0; i < n + 1; i++)
    {
        cin >> a;
        a1.push_back(a >> 10);
        a2.push_back(a & (1 << 10) - 1);
    }
    for (int i = 0; i < m + 1; i++)
    {
        cin >> b;
        b1.push_back(b >> 10);
        b2.push_back(b & (1 << 10) - 1);
    }
    Multiply(a1b1, a1, b1);
    Multiply(a1b2, a1, b2);
    Multiply(a2b1, a2, b1);
    Multiply(a2b2, a2, b2);
    ll ans = 0;
    for (int i = 0; i < n + m + 1; i++)
    {
        ll ab = (a1b1[i] << 20) + (a1b2[i] + a2b1[i] << 10) + a2b2[i];
        ans ^= ab;
    }
    cout << ans;
    return 0;
}