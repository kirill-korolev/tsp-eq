#pragma once

#include <vector>
#include "TSP.Link.h"

namespace TSPNeuralNet {

	class TspNeuron
	{
	public:
		TspNeuron();
		~TspNeuron();

		void link(std::vector<TspNeuron*> neurons);
		std::vector<TspLink*> links;

		double net = 0.0;
		double out = 0.0;
		double error = 0.0;
	};

}
