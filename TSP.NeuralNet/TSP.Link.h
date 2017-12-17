#pragma once

namespace TSPNeuralNet {

	class TspNeuron;

	class TspLink
	{
	public:
		TspLink(TspNeuron* lhs, TspNeuron* rhs);
		~TspLink();
		double weight;
	private:
		TspNeuron* left_;
		TspNeuron* right_;
	};

}

