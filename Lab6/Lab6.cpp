#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

double a, b;
int n, m;

double f(double x)
{
	return sin(x);
}

double w(double x)
{
	double r1 = sqrt(x);
 	double r2 = sqrt(r1);
	return 1 / r2;
}

double jp(int m, int i)
{
	double h = (b - a) / m;
	double r = 0;
	double aa = a + h / 2;
	for (int k = 1; k <= m; k++)
	{
		r += w(aa) * pow(aa, i);
		aa += h;
	}
	r *= h;
	return r;
}


double js(int m, int i)
{
	double h = (b - a) / (2 * m);
	double r = 0;
	double aa = a;
	for (int k = 0; k <= 2 * m; k++)
	{
		r += w(aa) * pow(aa, i);
		if (k > 0 && k < 2 * m && k % 2 == 1) r += 3 * w(aa) * pow(aa, i);
		else if (k > 0 && k < 2 * m) r += w(aa) * pow(aa, i);
		aa += h;
	}
	r *= h / 3;
	return r;
}

double getAk(int i, vector<double> roots)
{
	double h = (b - a) / m;
	double r = 0;
	double aa = a + h / 2;
	for (int k = 1; k <= m; k++)
	{
		r += w(aa) * (aa - roots[0])*(aa - roots[1])*(aa - roots[2]) / ((aa - roots[i]) * ((roots[i] - roots[1]) * (roots[i] - roots[2]) + (roots[i] - roots[0]) * (roots[i] - roots[2]) + (roots[i] - roots[0]) * (roots[i] - roots[1])));
		aa += h;

	}
	r *= h;
	return r;
}

double det(double* x, double* y, double* z)
{
	return x[0] * y[1] * z[2] + y[0] * z[1] * x[2] + x[1] * y[2] * z[0] - x[2] * y[1] * z[0] - x[1] * y[0] * z[2] - y[2] * z[1] * x[0];
}

double* find(double** at, double* y)
{
	double* x = new double[3];
	double ah, bh, ch;
	x[0] = ah = det(y, at[1], at[2]) / det(at[0], at[1], at[2]);
	x[1] = bh = det(at[0], y, at[2]) / det(at[0], at[1], at[2]);
	x[2] = ch = det(at[0], at[1], y) / det(at[0], at[1], at[2]);
	return x;
}

double poly(double* x, double t)
{
	return t*t*t + x[0] * t * t + x[1] * t + x[2];
}

double bisection(double* x, double l, double r)
{
	int k = 0;
	while (true)
	{
		if (r - l <= 2 * 0.0000001)
		{
			return r;
		}
		double c = (r + l) / 2.0;
		if (poly(x,l) * poly(x,c) < 0)
		{
			k++;
			r = c;
		}
		else if (poly(x,c) * poly(x,r) < 0)
		{
			k++;
			l = c;
		}
	}
}



int main()
{

	cout << std::setprecision(8) << fixed;
t0:
	cout << "Enter a, b, m: ";
	cin >> a >> b >> m;
	if (m <= 0)
	{
		cout << "Incorrect m" << endl;
		goto t0;
	}

	double** at = new double*[3];
	for (int i = 0; i < 3; i++)
		at[i] = new double[3];
	at[0][0] = jp(m, 2);
	at[0][1] = jp(m, 3);
	at[0][2] = jp(m, 4);
	at[1][0] = jp(m, 1);
	at[1][1] = jp(m, 2);
	at[1][2] = jp(m, 3);
	at[2][0] = jp(m, 0);
	at[2][1] = jp(m, 1);
	at[2][2] = jp(m, 2);
	double* y = new double[3];
	y[0] = -jp(m, 3);
	y[1] = -jp(m, 4);
	y[2] = -jp(m, 5);
	double* x = find(at, y);

	cout << "m0 = " << at[2][0] << endl;
	cout << "m1 = " << at[1][0] << endl;
	cout << "m2 = " << at[0][0] << endl;
	cout << "m3 = " << at[0][1] << endl;
	cout << "m4 = " << at[0][2] << endl;
	cout << "m5 = " << -y[2] << endl;
	cout << endl;
	cout << "x^3 + " << x[0] << "*x^2 + " << x[1] << "*x + " << x[2] << endl;

	vector<double> roots;
	double h = (b - a) / m;
	for (double i = a; i + h <= b; i += h)
	{
		if (poly(x, i) * poly(x, i + h) < 0)
		{
			roots.push_back(bisection(x, i, i + h));
		}
	}
	cout << endl;
	cout << "root1 = " << roots[0] << endl;
	cout << "root2 = " << roots[1] << endl;
	cout << "root3 = " << roots[2] << endl;
	cout << endl;

	if(roots.size() < 3) cout << "Not enough roots" << endl;
	else {
		at[0][0] = 1;
		at[0][1] = roots[0];
		at[0][2] = roots[0]*roots[0];
		at[1][0] = 1;
		at[1][1] = roots[1];
		at[1][2] = roots[1] * roots[1];
		at[2][0] = 1;
		at[2][1] = roots[2];
		at[2][2] = roots[2] * roots[2];
		y[0] = jp(m, 0);
		y[1] = jp(m, 1);
		y[2] = jp(m, 2);
		x = find(at, y);

		cout << "A0 = " << x[0] << endl;
		cout << "A1 = " << x[1] << endl;
		cout << "A2 = " << x[2] << endl;
		cout << endl;
		double res = x[0] * f(roots[0]) + x[1] * f(roots[1]) + x[2] * f(roots[2]);
		cout << "Result: " << res << endl;
		cout << abs(jp(m, 5) - x[0] * pow(roots[0], 5) - x[1] * pow(roots[1], 5) - x[2] * pow(roots[2], 5));
	}
	system("pause");
}