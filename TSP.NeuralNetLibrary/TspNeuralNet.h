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
			net = new TspNet<3>({100, 144, 44}, 1.25);
		}

		~TspNeuralNet() {
			delete net;
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