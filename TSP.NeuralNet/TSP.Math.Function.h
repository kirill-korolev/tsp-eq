#pragma once

#include <tuple>

namespace TSPNeuralNet { namespace Math {

	namespace Utils {
		template <int... Is>
		struct index {};

		template <int N, int... Is>
		struct genSeq : genSeq<N - 1, N - 1, Is...> {};

		template <int... Is>
		struct genSeq<0, Is...> : index<Is...> {};
	}

	class ITspFunction {
	public:
		virtual double operator()(double x) = 0;
		virtual double derivative(double x) = 0;
		virtual ~ITspFunction() {}
	};

	template <typename... Params>
	class TspFunction : public ITspFunction {
	public:
		TspFunction(double(*f)(double, Params...), Params... params);
		TspFunction(double(*f)(double, Params...), double(*g)(double, Params...), Params... params);
		TspFunction& operator=(const TspFunction&) = delete;
		double operator()(double x) override;
		double derivative(double x) override;
	private:

		template <int... Is>
		double func(double x, std::tuple<Params...>& tup, Utils::index<Is...>, bool isAntiDer) {
			return isAntiDer ? f_(x, std::get<Is>(tup)...) : g_(x, std::get<Is>(tup)...);
		}

		double func(double x, std::tuple<Params...>& tup, bool isAntiDer) {
			return func(x, tup, Utils::genSeq<sizeof...(Params)>{}, isAntiDer);
		}

		double(*f_)(double, Params...);
		double(*g_)(double, Params...);
		std::tuple<Params...> params_;
	};

}}

namespace TSPNeuralNet { namespace Math {

		template <typename... Params>
		TspFunction<Params...>::TspFunction(double(*f)(double, Params...), Params... params) :
			f_(f), params_(std::forward<Params>(params)...) {}

		template <typename... Params>
		TspFunction<Params...>::TspFunction(double(*f)(double, Params...), double(*g)(double, Params...), Params... params) :
			f_(f), g_(g), params_(std::forward<Params>(params)...) {}

		template <typename... Params>
		double TspFunction<Params...>::operator()(double x) {
			return func(x, params_, true);
		}

		template <typename... Params>
		double TspFunction<Params...>::derivative(double x) {
			if (g_ == nullptr) throw;
			return func(x, params_, false);
		}

}}

