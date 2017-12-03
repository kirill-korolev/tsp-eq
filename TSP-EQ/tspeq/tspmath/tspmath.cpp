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
    
    double randf(double max)
    {
        return max * (double) rand() / RAND_MAX;
    }
    
    double gaussian(double x, double e, double d)
    {
        return (1 / (sqrt(d) * sqrt(2 * M_PI))) * exp(-(pow(x - e, 2)) / (2 * d));
    }
    
    double linear(double x, double k, double b)
    {
        return k * x + b;
    }
    
    
    double sigmoid_deriv(double x, double a)
    {
        return sigmoid(x, a) * (1 - sigmoid(x, a));
    }
    
    double relu_deriv(double x)
    {
        return 1;
    }
    
    double leaky_relu_deriv(double x, double a)
    {
        if(x < 0) return a;
        return 1;
    }
    
}}
