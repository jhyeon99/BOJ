#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using cpx = complex<double>;
const double PI = acos(-1);

int x[120000], y[60000];

// FFT 구현 (재귀적 Cooley-Tukey 방식)
void FFT(vector<cpx>& f, cpx w)
{
    int n = f.size();
    if (n == 1) return;

    vector<cpx> even(n >> 1), odd(n >> 1);
    for (int i = 0; i < n; i++)
    {
        if (i & 1) odd[i >> 1] = f[i];    // 홀수 인덱스
        else even[i >> 1] = f[i];         // 짝수 인덱스
    }

    FFT(even, w * w); FFT(odd, w * w);
    cpx wp(1, 0);
    for (int i = 0; i < n / 2; i++)
    {
        f[i] = even[i] + wp * odd[i];
        f[i + n / 2] = even[i] - wp * odd[i];
        wp *= w;
    }
}

// 다항식 곱셈 (FFT 활용)
vector<cpx> Mul(vector<cpx> a, vector<cpx> b)
{
    int n = 1;
    while (n <= a.size() || n <= b.size()) n <<= 1;
    n <<= 1;
    a.resize(n); b.resize(n); vector<cpx> c(n);

    cpx w(cos(2 * PI / n), sin(2 * PI / n));
    FFT(a, w); FFT(b, w);

    for (int i = 0; i < n; i++) c[i] = a[i] * b[i];

    // 역 FFT
    FFT(c, cpx(1, 0) / w);
    for (int i = 0; i < n; i++)
    {
        c[i] /= cpx(n, 0);
        c[i] = cpx(round(c[i].real()), round(c[i].imag())); // 반올림
    }
    return c;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n; cin >> n;

    // 배열 x 입력 및 원형 확장
    for (int i = 0; i < n; i++)
    {
        cin >> x[i];
        x[n + i] = x[i]; // 원형 컨볼루션 처리
    }

    // 배열 y 입력
    int y[60000];
    for (int i = 0; i < n; i++) cin >> y[i];
    reverse(y, y + n); // 최대 내적 계산 위해 뒤집기

    // 벡터 변환
    vector<cpx> a, b;
    for (int i = 0; i < 2 * n; i++) a.push_back(cpx(x[i], 0));
    for (int i = 0; i < n; i++) b.push_back(cpx(y[i], 0));

    // FFT 기반 곱셈
    vector<cpx> c = Mul(a, b);

    // 최대 내적 계산
    ll ans = 0;
    for (int i = 0; i < c.size(); i++)
        ans = max(ans, (ll)round(c[i].real()));

    cout << ans;

    return 0;
}
