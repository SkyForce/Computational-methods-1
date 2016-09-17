#include <iostream>
#include <iomanip>
using namespace std;

double a, b;

double w(double x)
{
	return 1;
}

double f(double x)
{
	return exp(x)*w(x);
}


double j()
{
	return exp(b) - exp(a);
}

double jp(int m)
{
	double h = (b - a) / m;
	double r = 0;
	double aa = a + h / 2;
	for (int k = 1; k <= m; k++)
	{
		r += f(aa);
		aa += h;
	}
	r *= h;
	return r;
}

double jpl(int m)
{
	double h = (b - a) / m;
	double r = 0;
	double aa = a;
	for (int k = 1; k <= m; k++)
	{
		r += f(aa);
		aa += h;
	}
	r *= h;
	return r;
}

double jpr(int m)
{
	double h = (b - a) / m;
	double r = 0;
	double aa = a+h;
	for (int k = 1; k <= m; k++)
	{
		r += f(aa);
		aa += h;
	}
	r *= h;
	return r;
}

double jt(int m)
{
	double h = (b - a) / m;
	double r = 0;
	double aa = a;
	for (int k = 0; k <= m; k++)
	{
		r += f(aa);
		if (k > 0 && k < m) r += f(aa);
		aa += h;
	}
	r *= h / 2;
	return r;
}

double js(int m)
{
	double h = (b - a) / (2*m);
	double r = 0;
	double aa = a;
	for (int k = 0; k <= 2*m; k++)
	{
		r += f(aa);
		if (k > 0 && k < 2*m && k % 2 == 1) r += 3*f(aa);
		else if (k > 0 && k < 2 * m) r += f(aa);
		aa += h;
	}
	r *= h / 3;
	return r;
}

int main()
{
	cout << std::setprecision(8) << fixed;
t0:
	cout << "Enter a, b, m: ";
	int m;
	cin >> a >> b >> m;
	if (m <= 0)
	{
		cout << "Incorrect m" << endl;
		goto t0;
	}
	cout << "J: " << j() << endl;
	cout << "J(h) by mid rect: " << jp(m) << " |J-J(h)|: " << abs(j() - jp(m)) << endl;
	cout << "J(h) by left rect: " << jpl(m) << " |J-J(h)|: " << abs(j() - jpl(m)) << endl;
	cout << "J(h) by right rect: " << jpr(m) << " |J-J(h)|: " << abs(j() - jpr(m)) << endl;
	cout << "J(h) by trap: " << jt(m) << " |J-J(h)|: " << abs(j() - jt(m)) << endl;
	cout << "J(h) by Simp: " << js(m) << " |J-J(h)|: " << abs(j() - js(m)) << endl;
	system("pause");
}