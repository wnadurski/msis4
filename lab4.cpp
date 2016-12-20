#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <cstdlib>

using namespace std;

double f(double y, double t) {
	return -3 * t * t * t - 15 * t * t - 22.5 * t + 13 + y;
}


void makePlot(vector<double> *x, vector<double> *y)
{
	ofstream file;
	file.open("result.txt");

	for(int i = 0; i < x->size(); ++i)
	{
		file << x->at(i) << " " << y->at(i) << endl;
	}
	file.close();
	system("gnuplot -p -e \""
				   "set terminal jpeg;"
				   "set output 'plot.jpg';"
				   "plot 'result.txt';"
				   "exit;"
				   "\"");
	system("gnome-open plot.jpg");
}

typedef double (*derivativeFunc)(double, double);

double euler(derivativeFunc f	, double xn, double yn, double h)
{
	return xn + h*f(xn,yn);
}

int main() {
	vector<double> t;
	vector<double> x;
	double fromT = 0;
	double toT = 1;
	double x0;
	double e;
	double h;
	double xn;
	double tn;
	double xNext;

	cin >> x0 >> e;
	t.push_back(fromT);
	x.push_back(x0);

	h = sqrt(e);

	for(double curT = fromT + h; curT < toT; curT+=h)
	{
		xn = x.back();
		tn = t.back();

		xNext = euler(f, xn, tn, h);

		x.push_back(xNext);
		t.push_back(curT);
	}

	makePlot(&t, &x);

	return 0;
}
