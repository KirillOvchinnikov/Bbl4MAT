#include <iostream>

using namespace std;

double K1_i, K2_i, K3_i, K4_i;


double function(double &xi, double &yi)
{
	return pow(xi, 2) + yi;
}

double nextXi(double& xi, double& h)
{
	return xi + h;
}

void K1(double xi, double yi)
{
	K1_i = function(xi, yi);
}

void K2(double &xi, double &yi, double &h)
{
	double A = xi + h/2;
	double B = yi + (h * K1_i)/2;
	K2_i = function(A, B);
}

void K3(double& xi, double& yi, double &h)
{
	double A = xi + h / 2;
	double B = yi + (h * K2_i)/2;
	K3_i = function(A, B);
}

void K4(double& xi, double& yi, double &h)
{
	double A = xi + h;
	double B = yi + h * K3_i;
	K4_i = function(A, B);
}

double nextYiEuler(double &yi, double &xi, double &h, double(*func)(double &, double &))
{
	return yi + h * func(xi, yi);
}

double nextYiTrap(double& yi, double& xi, double& h, double(*func)(double &, double &))
{
	double A = nextXi(xi, h);
	double B = yi + h * func(xi,yi);
	return yi + h / 2 * (func(xi, yi) + func(A, B));
}

double nextYiRK(double& yi, double& h, double K1, double K2, double K3, double K4)
{
	return yi + h/6 * (K1 + 2*K2 + 2*K3 + K4);
}

void startEuler(double& yi, double& xi, double& h, int &i)
{
	double x = xi;
	double y = yi;
	cout << "x" << i << " = " << x << endl << "y" << i << " = " << y << endl << endl;
	y = nextYiEuler(yi, xi, h, function);
	x = nextXi(xi, h);
	while (i != 4)
	{
		i++;
		startEuler(y, x, h, i);
	}
	yi = 2.2;
	xi = 0;
	h = 0.5;
}

void startTrapezoidal(double& yi, double& xi, double& h, int& i)
{
	double x = xi;
	double y = yi;
	cout << "x" << i << " = " << x << endl << "y" << i << " = " << y << endl << endl;
	y = nextYiTrap(yi, xi, h, function);
	x = nextXi(xi, h);
	while (i != 4)
	{
		i++;
		startTrapezoidal(y, x, h, i);
	}
	yi = 2.2;
	xi = 0;
	h = 0.5;
}

void startRungeKutta(double& yi, double& xi, double& h, int& i, int &j)
{
	double x = nextXi(xi, h);
	K1(xi, yi);
	K2(xi, yi, h);
	K3(xi, yi, h);
	K4(xi, yi, h);
	double y = nextYiRK(yi, h, K1_i, K2_i, K3_i, K4_i);
	cout << "x" << i << " = " << x << endl
		<< "y" << i << " = " << y << endl
		<< "K1_" << j << " = " << K1_i << endl
		<< "K2_" << j << " = " << K2_i << endl
		<< "K3_" << j << " = " << K3_i << endl
		<< "K4_" << j << " = " << K4_i << endl << endl;
	while (i != 4)
	{
		i++;
		j++;
		startRungeKutta(y, x, h, i, j);
	}
	yi = 2.2;
	xi = 0;
	h = 0.5;
}

int main()
{
	setlocale(0, "");
	double yi = 2.2;
	double xi = 0;
	double h = 0.5;
	int i = 0, j = 0;
	cout << "________________________" << endl;
	cout << "Метод Эйлера:" << endl;
	startEuler(yi, xi, h, i);
	i = 0;
	cout << "________________________" << endl;
	cout << "Метод Трапеций:" << endl;
	startTrapezoidal(yi, xi, h, i);
	i = 1;
	cout << "________________________" << endl;
	cout << "Метод Рунге-Куттa:" << endl;
	startRungeKutta(yi, xi, h, i, j);
	return 0;
}