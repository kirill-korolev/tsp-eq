// ֳכאגםûי DLL-פאיכ.

#include "stdafx.h"
#include <algorithm>
#include <cliext\vector>
#include "TSP.NeuralNetLibrary.h"

namespace TSPNeuralNetLibrary {


	TspNeuralNet::TspNeuralNet() {
		fabric = new TSPNeuralNet::TspNeuralNetFabric();
	}

	TspNeuralNet::~TspNeuralNet() {
		delete fabric;
	}

	Collections::Generic::List<double>^ TspNeuralNet::GetResults(Collections::Generic::List<double>^ inputs){
		std::vector<double> vectorInputs;
		
		for (int i = 0; i < inputs->Count; ++i) {
			vectorInputs.push_back(inputs[i]);
		}

		std::vector<double> results = fabric->getResults(vectorInputs);

		array<double>^ ret = gcnew array<double>(results.size());

		if (results.size()){
			pin_ptr<double> dest = &ret[0];
			std::memcpy(dest, &results[0], results.size() * sizeof(double));
		}

		return gcnew Collections::Generic::List<double>(ret);
	}
}