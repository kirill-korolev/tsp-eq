#pragma once
#define DllExport   __declspec( dllexport )

#pragma comment (lib, "TSP.NeuralNet.lib")

#include "TSP.Math.Math.h"
#include "TSP.Math.Function.h"
#include "TSP.NeuralNet.h"

using namespace TSPNeuralNet;

namespace Tsp {
	class DllExport TspNeuralNet {
	public:

		TspNeuralNet() {
			Math::ITspFunction* activation = new Math::TspFunction<double>(Math::TspMath::sigmoid, Math::TspMath::sigmoidDeriv, 1);
			Math::ITspFunction* activationOutput = new Math::TspFunction<double>(Math::TspMath::sigmoid, Math::TspMath::sigmoidDeriv, 1);
			net = new TspNet<3>({96, 144, 48}, 0.1);
			net->setFunction(activation);
			net->setOutFunction(activationOutput);

			//net->initWeights();
		}

		~TspNeuralNet() {
			delete net;
		}

		Set::TspRow getResults(const Set::TspRow& inputs) {
			return net->test(inputs);
		}


	private:
		TSPNeuralNet::TspNet<3> *net = nullptr;
	};
}

extern "C" DllExport Tsp::TspNeuralNet* CreateInstance() {
	return new Tsp::TspNeuralNet();
}

extern "C" DllExport void DisposeInstance(Tsp::TspNeuralNet* instance) {
	if (instance != nullptr) {
		delete instance;
		instance = nullptr;
	}
}