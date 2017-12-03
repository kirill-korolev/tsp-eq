//
//  tspneuron.hpp
//  TSP-EQ
//
//  Created by Kirill Korolev on 20/11/2017.
//  Copyright © 2017 Kirill Korolev. All rights reserved.
//

#ifndef tspneuron_hpp
#define tspneuron_hpp

#include <vector>
#include "tsplink.hpp"


namespace tsp { namespace net {
    
    class tspneuron
    {
    public:
        tspneuron();
        ~tspneuron();
        void link(std::vector<tspneuron*> neurons);
        std::vector<tsplink*> links;
        double net = 0.0;
        double out = 0.0;
    };
    
}}

#endif /* tspneuron_hpp */
