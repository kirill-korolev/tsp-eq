#pragma once

#include <string>

namespace TSPNeuralNet { namespace Set {

	template <typename FeatureType>
	struct TspFeature {
		typedef FeatureType f_type;

		TspFeature(const char* str) : str_(str) {}

		inline const char* getTitle() const {
			return str_.c_str();
		}

	private:
		std::string str_;
	};

}}
