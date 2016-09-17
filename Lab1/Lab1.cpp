#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

double A = -1, B = 4, e = 0.00000001;

double f(double x)
{
	return sin(3*x);
}

double df(double x)
{
	return 3*cos(3*x);
}

void bisection(double l, double r)
{
	int k = 0;
	cout << "Bisection" << endl;
	while (true)
	{
		if (r - l <= 2 * e)
		{
			cout << "Steps: " << k << " solution : " << r << " discrepancy : " << abs(f(r)) << endl;
			return;
		}
		double c = (r + l) / 2.0;
		if (f(l) * f(c) < 0)
		{
			k++;
			r = c;
		}
		else if (f(c) * f(r) < 0)
		{
			k++;
			l = c;
		}
	}
}

void newton(double l, double r)
{
	cout << "Newton" << endl;
	int k = 1;
	double x0 = (l + r) / 2, x1 = x0 - f(x0) / df(x0);
	while (true)
	{
		if (abs(x1 - x0) < e) break;
		x0 = x1;
		x1 = x0 - f(x0) / df(x0);
		k++;
	}
	cout << "Steps: " << k << " solution : " << x1 << " discrepancy : " << abs(f(x1)) << endl;
}

void newtonx(double l, double r)
{
	cout << "Newton Mod" << endl;
	double x0 = l;

	//if (a == 0) x0 = b;

	double x1 = x0 - f(x0) / df(x0);
	int count = 1;
	int p = 1;

	//while (df(x1) == 0) p += 1;

	double xn = x1 - p * (f(x1) / df(x0));

	while (abs(xn - x1) >= e)
	{
		x1 = xn;
		if (f(x1) == 0) p += 1;
		xn = x1 - p * (f(x1) / df(x0));
		count += 1;
	}
	cout << "Steps: " << count << " solution : " << xn << " discrepancy : " << abs(f(xn)) << endl;
}

void chord(double l, double r)
{
	cout << "Chord" << endl;
	int k = 1;
	double x1 = l, x0 = r, xn = x1 - (f(x1) / (f(x1) - f(x0))) * (x1 - x0);
	while (true)
	{
		if (abs(xn - x1) < e) break;
		x0 = x1;
		x1 = xn;
		xn = x1 - (f(x1) / (f(x1) - f(x0))) * (x1 - x0);
		k++;
	}
	cout << "Steps: " << k << " solution : " << xn << " discrepancy : " << abs(f(xn)) << endl;
}


int main()
{
	cout << std::setprecision(12) << fixed;
	cout << "CHISLENNIE METODY RESHENIYA NELINEININYH ALGEBRAICHESKIH I TRANCEDENTNYH URAVNENII" << endl;
	//cout << "Enter A, B, e: ";
	//cin >> A >> B >> e;
	cout << "f(x) = sin(x), A = " << A << " B = " << B << " e = " << e  << endl;
	double h = (B - A) / 50;
	vector<pair<double, double> > v;
	for (double ta = A; ta < B; ta += h)
	{
		if (f(ta) * f(ta + h) < 0)
		{
			v.push_back(make_pair(ta, ta + h));
		}
	}
	cout << "Number of segments: " << v.size() << ": ";
	for (int i = 0; i < v.size(); i++)
		cout << '[' << v[i].first << ',' << v[i].second << "], ";
	cout << endl;
	for (int i = 0; i < v.size(); i++)
	{
		double ta = v[i].first;
		double tb = v[i].second;
		cout << ta << ' ' << ta + h << endl;
		bisection(ta, ta + h);
		newton(ta, ta + h);
		newtonx(ta, ta + h);
		chord(ta, ta + h);
	}
}