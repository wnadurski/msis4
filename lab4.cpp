#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>

using namespace std;

typedef double (*derivativeFunc)(double, double);

double f(double y, double t)
{
	return -2 * t * t * t + 12 * t * t - 20 * t + 8.5 + y;
}

double euler(derivativeFunc f, double xn, double yn, double h)
{
	return xn + h*f(xn,yn);
}

void makePlot(vector<double> *x, vector<double> *y)
{
	ofstream file;
	file.open("data.txt");

	for(int i = 0; i < x->size(); ++i)
	{
		file << x->at(i) << " " << y->at(i) << endl;
	}
	file.close();
	system("gnuplot < plot_script");
	system("gnome-open wykres.jpg");
}

int main() {
	double fromT = 0;
	double toT = 1;
	double x0;
	double e;
	double h;

	cin >> x0 >> e;

	h = sqrt(e);

	vector<double> t;
	vector<double> x;

	t.push_back(fromT);
	x.push_back(x0);

	for(double curT = fromT + h; curT < toT; curT+=h)
	{
		double xn = x.back();
		double tn = t.back();

		double xNext = euler(f, xn, tn, h);

		x.push_back(xNext);
		t.push_back(curT);
	}

	makePlot(&t, &x);

	return 0;
}
