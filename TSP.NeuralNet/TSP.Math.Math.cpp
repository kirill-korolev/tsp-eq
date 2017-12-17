#include "TSP.Math.Math.h"

#define _USE_MATH_DEFINES

#include <math.h>
#include <cstdlib>

namespace TSPNeuralNet { namespace Math {

	double TspMath::sigmoid(double x, double a)
	{
		return 1 / (1 + exp(-a * x));
	}

	double TspMath::tanh(double x)
	{
		return (exp(2 * x) - 1) / (exp(2 * x) + 1);
	}

	double TspMath::relu(double x)
	{
		if (x < 0) return 0;
		return x;
	}

	double TspMath::leakyRelu(double x, double a)
	{
		if (x < 0) return a * x;
		return x;
	}

	double TspMath::randf(double max)
	{
		return max * (double)rand() / RAND_MAX;
	}

	double TspMath::gaussian(double x, double e, double d)
	{
		return (1 / (sqrt(d) * sqrt(2 * M_PI))) * exp(-(pow(x - e, 2)) / (2 * d));
	}

	double TspMath::linear(double x, double k, double b)
	{
		return k * x + b;
	}

	double TspMath::sigmoidDeriv(double x, double a)
	{
		return sigmoid(x, a) * (1 - sigmoid(x, a));
	}

	double TspMath::reluDeriv(double x)
	{
		return 1;
	}

	double TspMath::leakyReluDeriv(double x, double a)
	{
		if (x < 0) return a;
		return 1;
	}

}}