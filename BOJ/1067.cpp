#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using cpx = complex<double>;
const double PI = acos(-1);
int x[120000], y[60000];
void FFT(vector<cpx>& f, cpx w)
{
	int n = f.size();
	if (n == 1) return;
	vector<cpx> even(n >> 1), odd(n >> 1);
	for (int i = 0; i < n; i++)
	{
		if (i & 1) odd[i >> 1] = f[i];
		else even[i >> 1] = f[i];
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
vector<cpx> Mul(vector<cpx> a, vector<cpx> b)
{
	int n = 1;
	while (n <= a.size() || n <= b.size()) n <<= 1;
	n <<= 1;
	a.resize(n); b.resize(n); vector<cpx> c(n);
	cpx w(cos(2 * PI / n), sin(2 * PI / n));
	FFT(a, w); FFT(b, w);
	for (int i = 0; i < n; i++) c[i] = a[i] * b[i];
	FFT(c, cpx(1, 0) / w);
	for (int i = 0; i < n; i++)
	{
		c[i] /= cpx(n, 0);
		c[i] = cpx(round(c[i].real()), round(c[i].imag()));
	}
	return c;
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n; cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> x[i];
		x[n + i] = x[i];
	}
	for (int i = 0; i < n; i++)
	{
		cin >> y[i];
	}
	reverse(y, y + n);
	vector<cpx> a, b;
	for (int i = 0; i < 2 * n; i++)
	{
		a.push_back(cpx(x[i], 0));
	}
	for (int i = 0; i < n; i++)
	{
		b.push_back(cpx(y[i], 0));
	}
	vector<cpx> c = Mul(a, b);
	ll ans = 0;
	for (int i = 0; i < c.size(); i++)
	{
		ans = max(ans, (ll)round(c[i].real()));
	}
	cout << ans;
	return 0;
}