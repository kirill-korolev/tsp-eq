//
//  tspfunction.cpp
//  TSP-EQ
//
//  Created by Kirill Korolev on 01/12/2017.
//  Copyright © 2017 Kirill Korolev. All rights reserved.
//

namespace tsp{ namespace math{
    
    template <typename... Params>
    tspfunction<Params...>::tspfunction(double (*f)(double, Params...), Params... params):
    f_(f), params_(std::forward<Params>(params)...){}
    
    template <typename... Params>
    tspfunction<Params...>::tspfunction(double (*f)(double, Params...), double (*g)(double, Params...), Params... params):
    f_(f), g_(g), params_(std::forward<Params>(params)...){}
    
    template <typename... Params>
    double tspfunction<Params...>::operator()(double x){
        return func(x, params_, true);
    }
    
    template <typename... Params>
    double tspfunction<Params...>::derivative(double x){
        if(g_ == nullptr) throw;
        return func(x, params_, false);
    }
}}
