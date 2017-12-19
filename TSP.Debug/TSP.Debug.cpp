// TSP.Debug.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#pragma comment(lib, "../Debug/TSP.NeuralNet.lib")

#include "TSP.NeuralNet.h"
#include "TSP.Math.Math.h"
#include "TSP.Math.Function.h"
#include "TSP.Set.Set.h"

using namespace TSPNeuralNet;

int main()
{
	Math::ITspFunction* activation = new Math::TspFunction<double>(Math::TspMath::sigmoid, Math::TspMath::sigmoidDeriv, 1);
	Math::ITspFunction* out = new Math::TspFunction<double>(Math::TspMath::sigmoid, Math::TspMath::sigmoidDeriv, 1);
	TSPNeuralNet::TspNet<3>* net = new TSPNeuralNet::TspNet<3>({ 96, 144, 48 }, 0.1);
	net->setFunction(activation);
	net->setOutFunction(out);

	//auto weights = Set::makeSet<double>("weights.csv");
	//net->initWeights(weights);

	

    return 0;
}

