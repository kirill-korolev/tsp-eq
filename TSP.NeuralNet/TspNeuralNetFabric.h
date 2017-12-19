#pragma once

#include "TSP.NeuralNet.h"
#include "TSP.Math.Math.h"
#include "TSP.Math.Function.h"
#include "TSP.Set.Set.h"


namespace TSPNeuralNet {

	class TspNeuralNetFabric
	{
	public:
		TspNeuralNetFabric();
		~TspNeuralNetFabric();
		Set::TspRow getResults(const Set::TspRow& inputs);
	private:
		TSPNeuralNet::TspNet<3> *net;
	};


	TspNeuralNetFabric::TspNeuralNetFabric() {
		Math::ITspFunction* activation = new Math::TspFunction<double>(Math::TspMath::sigmoid, Math::TspMath::sigmoidDeriv, 1);
		Math::ITspFunction* out = new Math::TspFunction<double>(Math::TspMath::sigmoid, Math::TspMath::sigmoidDeriv, 1);
		net = new TSPNeuralNet::TspNet<3>({ 96, 144, 48 }, 0.1);
		net->setFunction(activation);
		net->setOutFunction(out);
	}

	TspNeuralNetFabric::~TspNeuralNetFabric() {
		delete net;
	}

	Set::TspRow TspNeuralNetFabric::getResults(const Set::TspRow& inputs) {
		return net->test(inputs);
	}

}



