//
//  tspfunction.hpp
//  TSP-EQ
//
//  Created by Kirill Korolev on 01/12/2017.
//  Copyright © 2017 Kirill Korolev. All rights reserved.
//

#ifndef tspfunction_hpp
#define tspfunction_hpp

#include <tuple>

namespace tsp{ namespace math{
    
    namespace utils{
        template <int... Is>
        struct index {};
        
        template <int N, int... Is>
        struct gen_seq : gen_seq<N - 1, N - 1, Is...> {};
        
        template <int... Is>
        struct gen_seq<0, Is...> : index<Is...> {};
    }
    
    class tspifunction{
    public:
        virtual double operator()(double x)=0;
        virtual double derivative(double x)=0;
        virtual ~tspifunction(){}
    };
    
    template <typename... Params>
    class tspfunction: public tspifunction{
    public:
        tspfunction(double (*f)(double, Params...), Params... params);
        tspfunction(double (*f)(double, Params...), double (*g)(double, Params...), Params... params);
        tspfunction& operator=(const tspfunction&)=delete;
        double operator()(double x);
        double derivative(double x);
    private:
        
        template <int... Is>
        double func(double x, std::tuple<Params...>& tup, utils::index<Is...>, bool isAntiDer){
            return isAntiDer ? f_(x, std::get<Is>(tup)...) : g_(x, std::get<Is>(tup)...);
        }
        
        double func(double x, std::tuple<Params...>& tup, bool isAntiDer){
            return func(x, tup, utils::gen_seq<sizeof...(Params)>{}, isAntiDer);
        }
        
        double (*f_)(double, Params...);
        double (*g_)(double, Params...);
        std::tuple<Params...> params_;
    };
    
}}

#include "tspfunction_impl.hpp"

#endif /* tspfunction_hpp */
