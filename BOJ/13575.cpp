#include <bits/stdc++.h>
using namespace std;
using cpx = complex<double>;
const double PI = acos(-1);
void FFT(vector<cpx>& a, bool invert)
{
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++)
    {
        int bit = n >> 1;
        for (; j >= bit; bit >>= 1) j -= bit;
        j += bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1)
    {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cpx wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len)
        {
            cpx w(1, 0);
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
vector<int> Multiply(const vector<int>& a, const vector<int>& b)
{
    vector<cpx> ca(a.begin(), a.end()), cb(b.begin(), b.end());
    int n = 1;
    while (n <= a.size() || n <= b.size()) n <<= 1;
    ca.resize(n); cb.resize(n);
    FFT(ca, false); FFT(cb, false);
    for (int i = 0; i < n; i++) ca[i] *= cb[i];
    FFT(ca, true);
    vector<int> ret(n);
    for (int i = 0; i < n; i++)
    {
        ret[i] = round(ca[i].real());
        if (ret[i]) ret[i] = 1;
    }
    return ret;
}
vector<int> x(1024);
vector<int> Power(vector<int> a, int b)
{
    vector<int> ret = x; b--;
    while (b)
    {
        if (b & 1) ret = Multiply(ret, a);
        a = Multiply(a, a); b >>= 1;
    }
    return ret;
}
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n, k; cin >> n >> k;
    for (int i = 0; i < n; i++)
    {
        int a; cin >> a;
        x[a] = 1;
    }
    vector<int> res = Power(x, k);
    for (int i = 0; i < res.size(); i++)
    {
        if (res[i]) cout << i << ' ';
    }
    return 0;
}