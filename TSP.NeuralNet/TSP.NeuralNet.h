// TSP.NeuralNet.h

#pragma once

#include <array>
#include <vector>
#include "TSP.Math.Function.h"
#include "TSP.Layer.h"

namespace TSPNeuralNet {

	template <size_t Layers>
	class TspNet: public IComputed
	{
	public:
		TspNet(std::array<uint32_t, Layers> neurons, double learningRate);
		~TspNet();
		TspNet(const TspNet&) = delete;
		TspNet& operator=(const TspNet&) = delete;

		void setFunction(Math::ITspFunction* func);
		void setOutFunction(Math::ITspFunction* func);
		void train(const Set::TspRow& row);
		void test(const Set::TspRow& row);
		void initWeights(const std::vector<std::vector<double>>& weights);

		void didFinishedComputations() override;
	private:
		const Set::TspRow* tempRow_ = nullptr;
		double learningRate_;
		TspInput* inputLayer_;
		TspOutput* outputLayer_;
		std::vector<TspLayer*> hiddenLayers_;
	};

}

namespace TSPNeuralNet {

	template <size_t Layers>
	TspNet<Layers>::TspNet(std::array<Set::uint, Layers> neurons, double learningRate)
	{
		learningRate_ = learningRate;

		outputLayer_ = new TspOutput(neurons[Layers - 1]);
		TspLayer* next = outputLayer_;

		for (int i = Layers - 2; i > 0; --i)
		{
			TspLayer* layer = new TspLayer(neurons[i], nullptr, next);

			if (i == Layers - 2) {
				outputLayer_->setPrev(layer);
			}
			else {
				next->setPrev(layer);
			}

			hiddenLayers_.push_back(layer);
			next = layer;
		}

		inputLayer_ = new TspInput(neurons[0], next);

		outputLayer_->delegate = this;
	}

	template <size_t Layers>
	TspNet<Layers>::~TspNet()
	{
		delete inputLayer_;

		for (auto layer : hiddenLayers_)
			delete layer;

		delete outputLayer_;
	}

	template <size_t Layers>
	void TspNet<Layers>::setFunction(Math::ITspFunction* func) {

		for (int i = 0; i < hiddenLayers_.size(); ++i)
			hiddenLayers_[i]->func = func;
	}

	template <size_t Layers>
	void TspNet<Layers>::setOutFunction(Math::ITspFunction* func) {
		outputLayer_->func = func;
	}


	template <size_t Layers>
	void TspNet<Layers>::train(const Set::TspRow& row)
	{
		tempRow_ = &row;
		inputLayer_->feed(row);
	}

	template<size_t Layers>
	void TspNet<Layers>::test(const Set::TspRow& row)
	{
		
	}

	template<size_t Layers>
	void TspNet<Layers>::initWeights(const std::vector<std::vector<double>>& weights) {

	}


	template <size_t Layers>
	void TspNet<Layers>::didFinishedComputations() {
		outputLayer_->initLearning(learningRate_, *tempRow_);
	}
}