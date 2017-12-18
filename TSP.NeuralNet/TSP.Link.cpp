#include "TSP.Math.Math.h"
#include "TSP.Link.h"

namespace TSPNeuralNet {

	TspLink::TspLink(TspNeuron* lhs, TspNeuron* rhs)
	{
		left = lhs;
		right = rhs;
		weight = Math::TspMath::randf() - Math::TspMath::randf();
	}

	TspLink::~TspLink()
	{

	}

}