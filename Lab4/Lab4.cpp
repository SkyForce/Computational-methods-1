#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

double a, b;
int n, m;
double x;
double e = 0.00000001;

vector<pair<double, double> > vec;
vector<double>* pp;

double f(double xx)
{
	double r = sqrt(1 + xx*xx) + xx;
	return r;
}

void podg()
{
	cout << "exp(x)" << endl;
	double h = (b - a) / m;
	for (int i = 0; i <= m; i++)
	{
		cout << "x: " << a + i*h << " | f(x): " << f(a + i*h) << endl;
	}
}

bool comp(pair<double, double> a, pair<double, double> b)
{
	return abs(a.first - x) < abs(b.first - x);
}
bool comp2(pair<double, double> a, pair<double, double> b)
{
	return a.second < b.second;
}
bool comp3(pair<double, double> a, pair<double, double> b)
{
	return a.first < b.first;
}

double df(double xx)
{
	return xx / sqrt(1+xx*xx) + 1;
}

double df2(double xx)
{
	return (sqrt(1+xx*xx) - (xx*xx) / (sqrt(1+xx*xx))) / (1+xx*xx);
}

void interp0(double xx, int n)
{
	vec.clear();
	double h = (b - a) / m;
	for (double i = a; i <= b; i += h)
		vec.push_back(make_pair(f(i), i));
	sort(vec.begin(), vec.end(), comp);
	sort(vec.begin(), vec.begin() + n + 1);
	//for (int j = 0; j < vec.size(); j++) cout << vec[j] << ' ';
	//cout << endl;
	pp = new vector<double>[n + 1];
	double l, r;
	for (int j = 0; j < n; j++)
	{
		double t1 = (vec[j + 1]).second - (vec[j]).second;
		double t2 = vec[j + 1].first - vec[j].first;
		pp[0].push_back(t1 / t2);
		//cout << pp[0][j] << ' ';
	}
	//cout << endl;
	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < pp[i - 1].size() - 1; j++)
		{
			double t1 = (pp[i - 1][j + 1] - pp[i - 1][j]);
			double t2 = (vec[i + j + 1].first - vec[j].first);
			pp[i].push_back(t1 / t2);
			//cout << pp[i][pp[i].size() - 1];
		}
		//cout << endl;
	}
	double p = vec[0].second;
	for (int i = 0; i < n; i++)
	{
		double t = pp[i][0];
		for (int j = 0; j <= i; j++)
			t *= (xx - vec[j].first);
		p += t;
	}
	cout << "1st Newton: " << p << ' ' << abs(xx - f(p)) << endl;
}


double qq(double tx)
{
	double p = vec[0].second;
	for (int i = 0; i < n; i++)
	{
		double t = pp[i][0];
		for (int j = 0; j <= i; j++)
			t *= (tx - vec[j].first);
		p += t;
	}
	return p;
}

void bisection(double l, double r)
{
	int k = 0;
	cout << "2nd Bisection" << endl;
	while (true)
	{
		if (r - l <= 2 * e)
		{
			cout << "Steps: " << k << " solution : " << r << " discrepancy : " << abs(f(r)-x) << endl;
			return;
		}
		double c = (r + l) / 2.0;
		if ((qq(l)-x) * (qq(c)-x) <= 0)
		{
			k++;
			r = c;
		}
		else if ((qq(c)-x) * (qq(r)-x) <= 0)
		{
			k++;
			l = c;
		}
	}
}

void interp(double xx, int n, int m)
{
	//double a = 0, b = 1, m = 15;
	vec.clear();
	double h = (b - a) / m;
	for (double i = a; i <= b; i += h)
		vec.push_back(make_pair(i, f(i)));
	sort(vec.begin(), vec.end(), comp);
	sort(vec.begin(), vec.begin() + n + 1);
	//for (int j = 0; j < vec.size(); j++) cout << vec[j] << ' ';
	//cout << endl;
	pp = new vector<double>[n + 1];
	double l, r;
	for (int j = 0; j < n; j++)
	{
		double t1 = (vec[j + 1]).second - (vec[j]).second;
		double t2 = vec[j + 1].first - vec[j].first;
		pp[0].push_back(t1 / t2);
		//cout << pp[0][j] << ' ';
	}
	//cout << endl;
	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < pp[i - 1].size() - 1; j++)
		{
			double t1 = (pp[i - 1][j + 1] - pp[i - 1][j]);
			double t2 = (vec[i + j + 1].first - vec[j].first);
			pp[i].push_back(t1 / t2);
			//cout << pp[i][pp[i].size() - 1];
		}
		//cout << endl;
	}
	vector<pair<double, double> > vec2(vec.begin(), vec.end());
	sort(vec2.begin(), vec2.end(), comp2);
	//sort(vec.begin(), vec.end());
	for (int j = 0; j < m; j++)
	{
		if (vec2[j].second <= x && vec2[j + 1].second >= x)
		{
			l = vec2[j].first;
			r = vec2[j + 1].first;
			bisection(l, r);
		}
	}
}

void diff()
{
	sort(vec.begin(), vec.end(), comp3);
	double t = (-3 * vec[0].second + 4 * vec[1].second - vec[2].second) / (2 * (vec[1].first - vec[0].first));
	cout << vec[0].first << ' ' << vec[0].second << ' ' << t << ' ' << abs(df(vec[0].first) - t) << endl;
	for (int i = 1; i < vec.size() - 1; i++)
	{
		t = (vec[i+1].second - vec[i-1].second) / (vec[i+1].first - vec[i-1].first);
		cout << vec[i].first << ' ' << vec[i].second << ' ' << t << ' ' << abs(df(vec[i].first) - t) << ' ';
		t = (vec[i + 1].second - 2 * vec[i].second + vec[i - 1].second) / ((vec[i + 1].first - vec[i].first) * (vec[i + 1].first - vec[i].first));
		cout << t << ' ' << abs(df2(vec[i].first) - t) << endl;
	}
	t = (3 * vec[vec.size() - 1].second - 4 * vec[vec.size() - 2].second + vec[vec.size() - 3].second) / (2 * (vec[vec.size()-1].first - vec[vec.size()-2].first));
	cout << vec[vec.size()-1].first << ' ' << vec[vec.size()-1].second << ' ' << t << ' ' << abs(df(vec[vec.size()-1].first) - t) << endl;
}

int main()
{
	cout << std::setprecision(8) << fixed;
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
		cout << "Enter n <= " << m << ": ";
		cin >> n;
		if (n < 0 || n > m)
		{
			cout << "Incorrect n" << endl;
			goto t1;
		}
	t2:
		cout << "Enter F: ";
		cin >> x;
		/**if (x > f(b) || x < f(a))
		{
			cout << "incorrect F, must be between " << f(a) << ' ' << f(b) << endl;
			goto t2;
		}**/
		interp0(x, n);
		interp(x, n, m);
		sort(vec.begin(), vec.begin() + n + 1);
		diff();
	}
}