#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

double a, b;
int m;

void podg(int m)
{
	cout << "exp(x)" << endl;
	//double a = 1, b = 10;
	double h = (b-a)/m;
	for (double i = a; i <= b; i += h)
	{
		cout << "x: " << i << " | f(x): " << exp(i) << endl;
	}

}

double x;

bool comp(double a, double b)
{
	return abs(a - x) < abs(b - x);
}

double f(double x)
{
	double r = sqrt(1 + x*x) + x;
	return r;
}

void interp(double xx, int n)
{
	x = xx;
	//double a = 0, b = 1, m = 15;
	double h = (b - a) / m;
	vector<double> vec;
	vector<double>* pp = new vector<double>[n+1];
	for (double i = a; i <= b; i += h)
		vec.push_back(i);
	sort(vec.begin(), vec.end(), comp);
	//sort(vec.begin(), vec.begin() + n + 1);
	//for (int j = 0; j < vec.size(); j++) cout << vec[j] << ' ';
	//cout << endl;
	for (int j = 0; j < n; j++)
	{
		double t1 = f(vec[j + 1]) - f(vec[j]);
		double t2 = vec[j + 1] - vec[j];
		pp[0].push_back(t1 / t2);
		//cout << pp[0][j] << ' ';
	}
	//cout << endl;
	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < pp[i-1].size() - 1; j++)
		{
			double t1 = (pp[i - 1][j + 1] - pp[i - 1][j]);
			double t2 = (vec[i + j + 1] - vec[j]);
			pp[i].push_back( t1 / t2 );
			//cout << pp[i][pp[i].size() - 1];
		}
		//cout << endl;
	}
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << ' ' << f(vec[i]);
		cout << endl;
	}
	double p = f(vec[0]);
	for (int i = 0; i < n; i++)
	{
		double t = pp[i][0];
		for (int j = 0; j <= i; j++)
			t *= (x - vec[j]);
		p += t;
	}
	cout  << "Newton: " << p << ' ' << abs(f(xx) - p) << endl;
}

void lagranzh(double xx, int n)
{
	x = xx;
	//double a = 0, b = 1, m = 15;
	double h = (b - a) / m;
	vector<double> vec;
	vector<double>* pp = new vector<double>[n + 1];
	for (double i = a; i <= b; i += h)
		vec.push_back(i);
	sort(vec.begin(), vec.end(), comp);
	sort(vec.begin(), vec.begin() + n + 1);

	double res = 0;
	for (int i = 0; i <= n; i++)
	{
		double p = 1;
		for (int j = 0; j <= n; j++)
		{
			if (i == j) continue;
			double p1 = x - vec[j];
			double p2 = vec[i] - vec[j];
			p *= p1 / p2;
		}
		res += p * f(vec[i]);
	}
	cout << "Lagranzh: " << res << ' ' << abs(f(xx) - res) << endl;
}

int main()
{
	cout << std::setprecision(12) << fixed;
	double y;
	while (true) {
		t1:
		cout << "Enter a, b, m: ";
		int n;
		cin >> a >> b >> m;
		if (m < 0)
		{
			cout << "Incorrect m" << endl;
			goto t1;
		}
		else podg(m);
		t2:
		cout << "Enter n <= " << m << endl;
		cin >> n;
		if (n < 0 || n > m ) {
			cout << "Incorrect n" << endl;
			goto t2;
		}
		t3:
		cout << "Enter y: ";
		cin >> y;
		if(y < a || y > b) {
			cout << "Incorrect y" << endl;
			goto t3;
		}
		else {
			interp(y, n);
			lagranzh(y, n);
		}
	}
	system("pause");
}