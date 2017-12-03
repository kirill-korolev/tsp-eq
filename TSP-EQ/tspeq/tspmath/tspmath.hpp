//
//  tspmath.hpp
//  TSP-EQ
//
//  Created by Kirill Korolev on 27/11/2017.
//  Copyright © 2017 Kirill Korolev. All rights reserved.
//

#ifndef tspmath_hpp
#define tspmath_hpp

namespace tsp { namespace math {
    double sigmoid(double x, double a);
    double tanh(double x);
    double relu(double x);
    double leaky_relu(double x, double a);
    double gaussian(double x, double e, double d);
    double linear(double x, double k, double b);
    
    double randf(double max=1);
    
    double sigmoid_deriv(double x, double a);
    double relu_deriv(double x);
    double leaky_relu_deriv(double x, double a);
}}

#endif /* tspmath_hpp */
