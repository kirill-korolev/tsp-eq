#include "TSP.Math.Math.h"
#include "TSP.Link.h"

namespace TSPNeuralNet {

	TspLink::TspLink(TspNeuron* lhs, TspNeuron* rhs)
	{
		left_ = lhs;
		right_ = rhs;
		weight = Math::TspMath::randf() - Math::TspMath::randf();
	}

	TspLink::~TspLink()
	{

	}

}