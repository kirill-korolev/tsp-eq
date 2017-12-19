// TSP.NeuralNetLibrary.h

#pragma once
#pragma comment (lib, "../Debug/TSP.NeuralNet.lib")

#include <cliext\list>
#include "TspNeuralNetFabric.h"

using namespace System;

namespace TSPNeuralNetLibrary {

	public ref class TspNeuralNet
	{
	public:
		TspNeuralNet();
		~TspNeuralNet();
		Collections::Generic::List<double>^ GetResults(Collections::Generic::List<double>^ inputs);
	private:
		TSPNeuralNet::TspNeuralNetFabric* fabric;
	};
}
