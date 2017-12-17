#include "TSP.Layer.h"

namespace TSPNeuralNet {

	TspLayer::TspLayer(uint32_t neurons, TspLayer* prev, TspLayer* next)
	{
		prevLayer_ = prev;
		nextLayer_ = next;

		for (int i = 0; i < neurons; ++i)
		{
			TspNeuron* neuron = new TspNeuron;
			if (next != nullptr) neuron->link(next->neurons_);
			neurons_.push_back(neuron);
		}
	}

	TspLayer::~TspLayer()
	{
		for (auto neuron : neurons_)
			delete neuron;

		if (func != nullptr)
			delete func;
	}

	void TspLayer::reset() const
	{
		for (int i = 0; i < neurons_.size(); ++i)
		{
			neurons_[i]->net = 0.0;
			neurons_[i]->out = 0.0;
			neurons_[i]->error = 0.0;
		}
	}

	void TspLayer::learn(const double& learningRate)
	{
		if (prevLayer_ != nullptr) {
			for (int i = 0; i < prevLayer_->neurons_.size(); ++i) {
				for (int j = 0; j < prevLayer_->neurons_[i]->links.size(); ++j) {
					prevLayer_->neurons_[i]->links[j]->weight =
						prevLayer_->neurons_[i]->links[j]->weight - learningRate * 1;
				}
			}

			prevLayer_->learn(learningRate);
		}
	}

	void TspLayer::feed()
	{
		nextLayer_->reset();

		for (int i = 0; i < nextLayer_->height(); ++i) {
			for (int j = 0; j < neurons_.size(); ++j) {
				nextLayer_->getNeuron(i)->net +=
					neurons_[j]->net * neurons_[j]->links[i]->weight;
			}

			if (nextLayer_->func == nullptr) continue;

			nextLayer_->getNeuron(i)->out = nextLayer_->func->operator()(nextLayer_->getNeuron(i)->net);
		}

		nextLayer_->feed();
	}

	size_t TspLayer::height() const
	{
		return neurons_.size();
	}

	TspNeuron* TspLayer::getNeuron(int i)
	{
		return neurons_[i];
	}

	void TspLayer::setNext(TspLayer* layer) {
		nextLayer_ = layer;
	}

	void TspLayer::setPrev(TspLayer* layer) {
		prevLayer_ = layer;
	}
}


namespace TSPNeuralNet {

	TspInput::TspInput(uint32_t neurons, TspLayer* next) : TspLayer(neurons, nullptr, next) {}

	TspInput::~TspInput() {}

	void TspInput::feed(const Set::TspRow& row)
	{
		for (int i = 0; i < neurons_.size(); ++i)
			neurons_[i]->net = row[i];

		TspLayer::feed();
	}

}


namespace TSPNeuralNet {

	TspOutput::TspOutput(uint32_t neurons, TspLayer* prev) : TspLayer(neurons, prev, nullptr) {}
	TspOutput::~TspOutput() {}

	void TspOutput::feed()
	{
		if (delegate != nullptr)
			delegate->didFinishedComputations();
	}

	void TspOutput::initLearning(const double& learningRate, const Set::TspRow& row) {

		Set::TspRow outputs(row.end() - neurons_.size(), row.end());

		for (int i = 0; i < neurons_.size(); ++i) {
			neurons_[i]->error = neurons_[i]->out - outputs[i];
		}


		learn(learningRate);
	}
}