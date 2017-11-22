//
//  main.cpp
//  TSP-EQ
//
//  Created by Kirill Korolev on 20/11/2017.
//  Copyright © 2017 Kirill Korolev. All rights reserved.
//

#include <iostream>
#include "tspeq/tspset/tspset.hpp"
#include "tspeq/tspnet/tspnet.hpp"

using tsp::net::tspnet;
using tsp::set::make_set;

int main(int argc, const char * argv[]) {
    
    auto set = make_set<int, double, double, double, double>("bitcoin-usd-dataset-small.csv");
    tspnet<3> net({2, 2, 2});
    net.train(set);
    
    return 0;
}

