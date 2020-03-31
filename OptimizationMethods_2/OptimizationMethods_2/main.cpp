#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

double functionX(double x, double y)
{
	//return 1 / (1 + pow((x - 2) / 3, 2) + pow((y - 2) / 3, 2)) + 3 / (1 + pow(x - 1, 2) + pow((y - 1) / 2, 2)); /* функция по варианту */
	//return 100 * pow(y - x, 2) + pow(1 - x, 2); /*f(x,y)=100(y-x)^2 +(1-x)^2 */
	return 100 * pow(y - x * x, 2) + pow(1 - x, 2); /* f(x,y)=100(y-x*x)^2 +(1-x)^2 */
}

void gradX(double x, double y, double* grad)
{
	//grad[0] = -((2 * x - 4) / (9 * pow(1 + pow((x - 2) / 3, 2) + pow((y - 2) / 3, 2), 2)) + (6 * x - 6) / pow(1 + pow(x - 1, 2) + pow((y - 1) / 2, 2), 2));
	//grad[1] = -((2 * y - 4) / (9 * pow(1 + pow((x - 2) / 3, 2) + pow((y - 2) / 3, 2), 2)) + (3 * y - 3) / (2 * pow(1 + pow(x - 1, 2) + pow((y - 1) / 2, 2), 2)));

	//grad[0] = 202 * x - 200 * y - 2; /*grad (100(y-x)^2 +(1-x)^2)*/
	//grad[1] = 200 * (y - x);

	grad[0] = 400 * x * x * x - 400 * x * y + 2 * x - 2;
	grad[1] = 200*(y - x * x);
}

double max_lambda(double* x, double* S)
{
	double lambda = 1, h = 0;
	
	if (functionX(x[0] + lambda * S[0], x[1] + lambda * S[1]) < functionX(x[0] + (lambda + 0.1) * S[0], x[1] + (lambda + 0.1) * S[1]))
	{
		lambda += 0.1;
		h = 0.1;
	}
	else if (functionX(x[0] + lambda * S[0], x[1] + lambda * S[1]) < functionX(x[0] + (lambda - 0.1) * S[0], x[1] + (lambda - 0.1) * S[1]))
	{
		lambda -= 0.1;
		h = -0.1;
	}

	while (functionX(x[0] + lambda * S[0], x[1] + lambda * S[1]) < functionX(x[0] + (lambda + h) * S[0], x[1] + (lambda + h) * S[1]))
	{
		lambda += h;
	}

	return lambda;
}

double min_lambda(double* x, double* S)
{
	double lambda = 1, h = 0;

	if (functionX(x[0] + lambda * S[0], x[1] + lambda * S[1]) > functionX(x[0] + (lambda + 0.0001) * S[0], x[1] + (lambda + 0.0001) * S[1]))
	{
		lambda += 0.0001;
		h = 0.0001;
	}
	else if (functionX(x[0] + lambda * S[0], x[1] + lambda * S[1]) > functionX(x[0] + (lambda - 0.0001) * S[0], x[1] + (lambda - 0.0001) * S[1]))
	{
		lambda -= 0.0001;
		h = -0.0001;
	}

	while (functionX(x[0] + lambda * S[0], x[1] + lambda * S[1]) > functionX(x[0] + (lambda + h) * S[0], x[1] + (lambda + h) * S[1]))
	{
		lambda += h;
	}

	return lambda;
}

void flethcer_reeves_CG_max(double* value)
{
	double S[2], grad_x[2], lambda, sigma, eps = 1e-7;
	int k = 0;
	gradX(value[0], value[1], grad_x);

	S[0] = grad_x[0];
	S[1] = grad_x[1];

	while (sqrt(S[0] * S[0] + S[1] * S[1]) > eps)
	{
		lambda = max_lambda(value, S);

		value[0] += lambda * S[0];

		value[1] += lambda * S[1];

		gradX(value[0], value[1], grad_x);

		sigma = (grad_x[0] * grad_x[0] + grad_x[1] * grad_x[1]) / (S[0] * S[0] + S[1] * S[1]);

		S[0] = grad_x[0] + sigma * S[0];
		S[1] = grad_x[1] + sigma * S[1];
		k++;
	}

	cout << "f(x,y)=" << functionX(value[0], value[1]) << ", " << "x: " << value[0] << ", " << "y: " << value[1] << ", ITER:  " << k << "\n";

}

void flethcer_reeves_CG_min(double* value)
{
	double S[2], grad_x[2], lambda, sigma, eps = 1e-7;
	int k = 0;
	gradX(value[0], value[1], grad_x);

	S[0] = -grad_x[0];
	S[1] = -grad_x[1];

	while (sqrt(S[0] * S[0] + S[1] * S[1]) > eps)
	{
		lambda = min_lambda(value, S);

		value[0] += lambda * S[0];

		value[1] += lambda * S[1];

		

		gradX(value[0], value[1], grad_x);

		sigma = (grad_x[0] * grad_x[0] + grad_x[1] * grad_x[1]) / (S[0] * S[0] + S[1] * S[1]);

		S[0] = -grad_x[0] + sigma * S[0];
		S[1] = -grad_x[1] + sigma * S[1];
		k++; //счетчик итераций 
	}



	cout << "f(x,y)=" << functionX(value[0], value[1]) << ", " << "x: " << value[0] << ", " << "y: " << value[1] << ", ITER:  " << k << "\n";


}

bool hesseX(double x, double y, double** hesse)
{
	//hesse[0][0] = 6 / pow(((x - 1) * (x - 1) + ((y - 1) / 2) * ((y - 1) / 2) + 1), 2) + (4 * (x - 2) * (2 * x - 4)) / (81 * pow((((x - 2) / 3) * ((x - 2) / 3) + ((y - 2) / 3) * ((y - 2) / 3) + 1), 3));
	//hesse[0][1] = (4 * (y - 2) * (2 * x - 4)) / (81 * pow((((x - 2) / 3) * ((x - 2) / 3) + ((y - 2) / 3) * ((y - 2) / 3) + 1), 3)) + (6 * (x - 1) * (y - 1)) / pow(((x - 1) * (x - 1) + ((y - 1) / 2) * ((y - 1) / 2) + 1), 3);
	//hesse[1][1] = 2 / (9 * pow((((x - 2) / 3) * ((x - 2) / 3) + ((y - 2) / 3) * ((y - 2) / 3) + 1), 2)) - 3 / (2 * pow(((x - 1) * (x - 1) + ((y - 1) / 2) * ((y - 1) / 2) + 1), 2));
	//hesse[1][0] = (4 * (x - 2) * (2 * y - 4)) / (81 * pow((((x - 2) / 3) * ((x - 2) / 3) + ((y - 2) / 3) * ((y - 2) / 3) + 1), 3)) + (2 * (x - 1) * (3 * y - 3)) / pow(((x - 1) * (x - 1) + ((y - 1) / 2) * ((y - 1) / 2) + 1), 3);

	//hesse[0][0] = 202; /*для квадратичной функции*/
	//hesse[0][1] = -200;
	//hesse[1][1] = 200;
	//hesse[1][0] = -200;

	hesse[0][0] = 1200 * x * x - 400 * y + 2; /*для функции розенброка*/
	hesse[0][1] = -400 * x;
	hesse[1][1] = 200;
	hesse[1][0] = -400 * x;

	double det, temp;

	det = hesse[0][0] * hesse[1][1] - hesse[0][1] * hesse[1][0];

	if (det != 0)
	{
		hesse[0][1] *= -1;
		hesse[1][0] *= -1;

		temp = hesse[0][0];
		hesse[0][0] = hesse[1][1];
		hesse[1][1] = temp;

		hesse[0][0] *= 1 / det; hesse[0][1] *= 1 / det;
		hesse[1][0] *= 1 / det; hesse[1][1] *= 1 / det;

		return true;
	}
	else
		return false;

}


void newton_method_max(double* value)
{
	//double hesse_x[2][2], grad_x[2];
	double lambda, eps = 1e-7;
	double grad_x[2];
	double** hesse_x;
	hesse_x = new double* [2];
	hesse_x[0] = new double[2];
	hesse_x[1] = new double[2];

	int k = 0;

	double S[2];
	
	do 
	{
		if (!hesseX(value[0], value[1], hesse_x))
		{
			cout << "shit\n";
			break;
		}
		gradX(value[0], value[1], grad_x);

		S[0] = -hesse_x[0][0] * grad_x[0] - hesse_x[0][1] * grad_x[1];
		S[1] = -hesse_x[1][0] * grad_x[0] - hesse_x[1][1] * grad_x[1];

		lambda = max_lambda(value, S);

		value[0] += lambda * S[0];
		value[1] += lambda * S[1];
		k++;

	} while (sqrt(S[0] * S[0] + S[1] * S[1]) > eps);

	cout << "f(x,y)=" << functionX(value[0], value[1]) << ", " << "x: " << value[0] << ", " << "y: " << value[1] << ", ITER:  " << k << "\n";
	
}

void newton_method_min(double* value)
{
	//double hesse_x[2][2], grad_x[2];
	double lambda, eps = 1e-7;
	double grad_x[2];
	double** hesse_x;
	hesse_x = new double* [2];
	hesse_x[0] = new double[2];
	hesse_x[1] = new double[2];

	double S[2];
	int k = 0;

	do
	{
		if (!hesseX(value[0], value[1], hesse_x))
		{
			cout << "shit\n";
			break;
		}
		gradX(value[0], value[1], grad_x);

		S[0] = -hesse_x[0][0] * (-grad_x[0]) - hesse_x[0][1] * (-grad_x[1]);
		S[1] = -hesse_x[1][0] * (-grad_x[0]) - hesse_x[1][1] * (-grad_x[1]);

		lambda = min_lambda(value, S);

		value[0] += lambda * S[0];
		value[1] += lambda * S[1];

		k++;

	} while (sqrt(S[0] * S[0] + S[1] * S[1]) > eps);

	cout << "f(x,y)=" << functionX(value[0], value[1]) << ", " << "x: " << value[0] << ", " << "y: " << value[1] << ", ITER:  " << k << "\n";

}


int main()
{
	double x[2];
	x[0] = 2; x[1] = -3;

	cout.precision(7);
	//flethcer_reeves_CG_max(x);
	
	newton_method_min(x);

	return 0;
}