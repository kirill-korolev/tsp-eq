#include "TSP.NeuralNet.h"
#include "TSP.Math.Math.h"
#include "TSP.Set.Set.h"

using namespace TSPNeuralNet;

int main() {
	//auto dataset = Set::makeSet<double>("test.csv");

	Math::ITspFunction* activation = new Math::TspFunction<double>(Math::TspMath::sigmoid, Math::TspMath::sigmoidDeriv, 1);
	Math::ITspFunction* activationOutput = new Math::TspFunction<double>(Math::TspMath::sigmoid, Math::TspMath::sigmoidDeriv, 1);
	TspNet<3> net({ 100, 144, 44 }, 1.25);

	net.setFunction(activation);
	net.setOutFunction(activationOutput);

	//for (auto &item : dataset) {
	//	net.test(item);
	//}
	
	delete activation;
	delete activationOutput;

	return 0;
}