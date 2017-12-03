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
    
    
    double randf();
}}

#endif /* tspmath_hpp */
