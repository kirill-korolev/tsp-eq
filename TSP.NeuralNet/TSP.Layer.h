#pragma once

#include <stdint.h>
#include <vector>
#include <iostream>

#include "TSP.Math.Function.h"
#include "TSP.Set.Set.h"
#include "TSP.Neuron.h"

namespace TSPNeuralNet {

	class IComputed {
	public:

		enum class ComputingMode {
			Learning, Testing
		};

		virtual void didFinishedComputations() = 0;
		virtual void didFinishedTesting(const Set::TspRow& answers) = 0;
		virtual ~IComputed() {}
		ComputingMode mode;
	};

	template <size_t Layers>
	class TspNet;

	class TspLayer
	{
	public:
		TspLayer(uint32_t neurons, TspLayer* prev = nullptr, TspLayer* next = nullptr);
		virtual ~TspLayer();
		TspLayer(const TspLayer&) = delete;
		TspLayer& operator=(const TspLayer&) = delete;

		virtual void feed();
		virtual void learn(const double& learningRate);

		void reset() const;
		size_t height() const;
		TspNeuron* getNeuron(int i);

		void initWeights(const std::vector<double>& weights);

		void setNext(TspLayer* layer);
		void setPrev(TspLayer* layer);

		Math::ITspFunction* func = nullptr;
	protected:
		std::vector<TspNeuron*> neurons_;
		TspLayer* nextLayer_;
		TspLayer* prevLayer_;
	};

	class TspInput : public TspLayer
	{
	public:
		TspInput(uint32_t neurons, TspLayer* next = nullptr);
		~TspInput();
		using TspLayer::feed;
		void feed(const Set::TspRow& row);
	};

	class TspOutput : public TspLayer
	{
	public:

		TspOutput(uint32_t neurons, TspLayer* prev = nullptr);
		~TspOutput();
		void feed() override;
		void initLearning(const double& learningRate, const  Set::TspRow& row);
		IComputed* delegate;
	};

}


