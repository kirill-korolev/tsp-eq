#include "TSP.Neuron.h"

namespace TSPNeuralNet {

	TspNeuron::TspNeuron()
	{

	}

	TspNeuron::~TspNeuron()
	{
		for (auto link : links)
			delete link;
	}

	void TspNeuron::link(std::vector<TspNeuron*> neurons)
	{
		for (auto neuron : neurons)
		{
			TspLink* l = new TspLink(this, neuron);
			links.push_back(l);
		}
	}

}