#pragma once

namespace TSPNeuralNet {

	class TspNeuron;

	class TspLink
	{
	public:
		TspLink(TspNeuron* lhs, TspNeuron* rhs);
		~TspLink();
		double weight;
		TspNeuron* left;
		TspNeuron* right;
	};

}

