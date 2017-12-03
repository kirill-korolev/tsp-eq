//
//  main.cpp
//  TSP-EQ
//
//  Created by Kirill Korolev on 20/11/2017.
//  Copyright © 2017 Kirill Korolev. All rights reserved.
//


#ifdef DATASET_GENERATION_MODE
#include "dataset_generation.hpp"
//generate_dataset(INPUT_DATASET, OUTPUT_DATASET, NUMBER OF PREV ROWS, ROWS AVERAGE, FEATURES...)
generate_dataset("bitcoin-usd-dataset-small.csv", "example.csv", 720, 5, tsp::set::tspfeature<double>("Weighted_Price"));
#endif

#include <iostream>
#include "tspset.hpp"
#include "tspnet.hpp"

double func(double x){
    return tsp::math::sigmoid(std::pow(10, 2) * std::pow(x / 65 - 1, 3), 1);
}

int main(int argc, const char * argv[]) {
    
    auto dataset = tsp::set::make_set<double>("example.csv");
    
    tsp::math::tspifunction* f =
    new tsp::math::tspfunction<double>(tsp::math::leaky_relu, tsp::math::leaky_relu_deriv, 0.1);
    
    tsp::math::tspifunction* g =
    new tsp::math::tspfunction<double>(tsp::math::sigmoid, tsp::math::sigmoid_deriv, 1);
    
    //Initialization of a neural network
    tsp::net::tspnet<3> net({100, 65, 43}, 0.05);
    
    net.set_function(f);
    net.set_out_function(g);
    
    //Training session
    for(int i = 0; i < 10; ++i){
        //std::cout << "Session " << (i + 1) << std::endl;
        net.train(dataset.at(i));
    }
    

    
    return 0;
}


