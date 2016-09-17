#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

double a, b;
int n, m;
double x;

void podg()
{
	cout << "exp(x)" << endl;
	double h = (b - a) / m;
	for (int i = 0; i <= m; i++)
	{
		cout << "x: " << a+i*h << " | f(x): " << exp(a+i*h) << endl;
	}
}

double f(double t)
{
	return sin(t) + t*t / 2;
}

void solve()
{
	double h = (b - a) / m;
	vector<double>* vec = new vector<double>[n+1];
	for (int i = 0; i <= m; i++)
	{
		vec[0].push_back(f(a + i*h));
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j < vec[i - 1].size() - 1; j++)
			vec[i].push_back(vec[i - 1][j + 1] - vec[i - 1][j]);
	}

	double res = 0;
	if (x >= a && x <= a + h)
	{
		double t = (x - a) / h;
		double nk = 1;
		for (int i = 0; i <= n; i++)
		{
			res += nk * vec[i][0];
			nk *= (t - i) / (i + 1);
		}
	}
	else if (x >= b - h)
	{
		double t = (x - b) / h;
		double nk = 1;
		for (int i = 0; i <= n; i++)
		{
			res += nk * vec[i][vec[i].size()-1];
			nk *= (t + i) / (i + 1);
		}
	}
	else if (x >= a + h * ((n + 1) / 2) && x <= b - h * ((n+1)/2))
	{
		int c = (int)((x - a) / h);
		double aa = c * h;
		double t = (x - aa) / h;
		double nk = 1;
		int sch = 0;
		for (int i = 0; i <= n; i++)
		{
			if (sch > 1)
			{
				sch = 0;
				c--;
			}
			res += nk * vec[i][c];
			sch++;
			nk *= (t - pow(-1, i+1) * ((i+1)/2)) / (i + 1);
		}
	}

	cout << "P(x): " << res << " |f(x) - P(x)| = " << abs(res - f(x)) << endl;
}

int main()
{
	cout << std::setprecision(12) << fixed;
	t0:
	cout << "Enter a, b, m: ";
	cin >> a >> b >> m;
	if (m < 0)
	{
		cout << "Incorrect m" << endl;
		goto t0;
	}
		podg();
	while (true)
	{
		t1:
		cout << "Enter n <= " << m << endl;
		cin >> n;
		if (n < 0 || n > m)
		{
			cout << "Incorrect n" << endl;
			goto t1;
		}
		t2:
		double h = (b - a) / m;
		cout << "Enter x in [" << a << ", " << a + h << "], or [" << a + ((n + 1) / 2) * h << ", " << b - ((n + 1) / 2) * h << "], or [" << b-h << ", " << b << "]: ";
		cin >> x;
		if (x < a || x > b || x > a + h && x < a + ((n+1) / 2) * h || x > b - ((n+1) / 2) * h && x < b - h)
		{
			cout << "Incorrect x" << endl;
			goto t2;
		}
		solve();
	}
}