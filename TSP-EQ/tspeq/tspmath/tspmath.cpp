//
//  tspmath.cpp
//  TSP-EQ
//
//  Created by Kirill Korolev on 27/11/2017.
//  Copyright © 2017 Kirill Korolev. All rights reserved.
//

#include "tspmath.hpp"
#include <cmath>
#include <cstdlib>

namespace tsp { namespace math {
    
    double sigmoid(double x, double a)
    {
        return 1 / (1 + exp(-a * x));
    }
    
    double tanh(double x)
    {
        return (exp(2 * x) - 1) / (exp(2 * x) + 1);
    }
    
    double relu(double x)
    {
        if(x < 0) return 0;
        return x;
    }
    
    double leaky_relu(double x, double a)
    {
        if(x < 0) return a * x;
        return x;
    }
    
    double randf()
    {
        return (double) rand() / RAND_MAX;
    }
}}
