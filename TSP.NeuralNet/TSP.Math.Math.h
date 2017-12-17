#pragma once

namespace TSPNeuralNet { namespace Math {

	class TspMath
	{
	public:
		static double sigmoid(double x, double a);
		static double tanh(double x);
		static double relu(double x);
		static double leakyRelu(double x, double a);
		static double gaussian(double x, double e, double d);
		static double linear(double x, double k, double b);

		static double randf(double max = 1);

		static double sigmoidDeriv(double x, double a);
		static double reluDeriv(double x);
		static double leakyReluDeriv(double x, double a);
	};

}}