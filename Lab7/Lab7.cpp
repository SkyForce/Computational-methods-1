#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>

using namespace std;

pair<int,int> readNumber(string s, int pos)
{
	int ind = pos;
	for (ind = pos; ind < s.size(); ind++)
		if (s[ind] < '0' || s[ind] > '9'){
			break;
		}
	if (ind == pos) return make_pair(228, -1);
	int sum = -0;
	for (int i = ind-1; i >= pos; i--) {
		if (s[i] >= '0' && s[i] <= '9')
			sum += (s[i] - '0')*pow(10, ind - i - 1);
		else return make_pair(228, -1);
	}
	return make_pair(sum, ind);
}

pair<int,int> isCsc(string s, int pos)
{
	try {
		pair<int, int> t = readNumber(s, pos);
		if (t.first != 228) return t;
		if (s[pos] == '(')
		{
			pos++;
			if (s[pos] == '^')
			{
				pos++;
				if (s[pos] == ' ')
				{
					pair<int, int> n1 = isCsc(s, pos + 1);
					if (n1.first != 228)
					{
						if (s[n1.second] == ' ') {
							pair<int, int> number = readNumber(s, n1.second + 1);
							if (number.first != 228 && s[number.second] == ')') {
								return make_pair(pow(n1.first, number.first), number.second + 1);
							}
							else return make_pair(228, -1);
						}
						else return make_pair(228, -1);
					}
					else return make_pair(228, -1);
				}
				else return make_pair(228, -1);
			}
			else if (s[pos] == '*')
			{
				pos++;
				if (s[pos] == ' ')
				{
					pair<int, int> n1 = isCsc(s, pos + 1);
					if (n1.first != 228)
					{
						if (s[n1.second] == ' ') {
							pair<int, int> csc = isCsc(s, n1.second + 1);
							if (csc.first != 228 && s[csc.second] == ')') {
								return make_pair(n1.first * csc.first, csc.second + 1);
							}
							else return make_pair(228, -1);
						}
						else return make_pair(228, -1);
					}
					else return make_pair(228, -1);
				}
				else return make_pair(228, -1);
			}
			else if (s[pos] == '+')
			{
				pos++;
				if (s[pos] == ' ')
				{
					pair<int, int> n1 = isCsc(s, pos + 1);
					if (n1.first != 228)
					{
						if (s[n1.second] == ' ') {
							pair<int, int> csc = isCsc(s, n1.second + 1);
							if (csc.first != 228 && s[csc.second] == ')') {
								return make_pair(n1.first + csc.first, csc.second + 1);
							}
							else return make_pair(228, -1);
						}
						else return make_pair(228, -1);
					}
					else return make_pair(228, -1);
				}
				else return make_pair(228, -1);
			}
			else if (s[pos] == '/')
			{
				pos++;
				if (s[pos] == ' ')
				{
					pair<int, int> n1 = isCsc(s, pos + 1);
					if (n1.first != 228)
					{
						if (s[n1.second] == ' ') {
							pair<int, int> csc = isCsc(s, n1.second + 1);
							if (csc.first != 228 && csc.first != 0 && s[csc.second] == ')') {
								return make_pair(n1.first / csc.first, csc.second + 1);
							}
							else return make_pair(228, -1);
						}
						else return make_pair(228, -1);
					}
					else return make_pair(228, -1);
				}
				else return make_pair(228, -1);
			}
			else if (s[pos] == '-')
			{
				pos++;
				if (s[pos] == ' ')
				{
					pair<int, int> n1 = isCsc(s, pos + 1);
					if (n1.first != 228)
					{
						if (s[n1.second] == ' ') {
							pair<int, int> csc = isCsc(s, n1.second + 1);
							if (csc.first != 228 && s[csc.second] == ')') {
								return make_pair(n1.first - csc.first, csc.second + 1);
							}
							else return make_pair(228, -1);
						}
						else if (s[n1.second] == ')')
						{
							return make_pair(-n1.first, n1.second + 1);
						}
						else return make_pair(228, -1);
					}
					else return make_pair(228, -1);
				}
				else return make_pair(228, -1);
			}
			else return make_pair(228, -1);
		}
		else return make_pair(228, -1);
	}
	catch (...) {
		return make_pair(228, -1);
	}
}

int main()
{
	string s;
	getline(cin, s);
	pair<int, int> r = isCsc(s, 0);
	if (r.second == s.size())
		cout << r.first;
	else cout << "ERROR";
}