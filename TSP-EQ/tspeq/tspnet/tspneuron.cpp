//
//  tspneuron.cpp
//  TSP-EQ
//
//  Created by Kirill Korolev on 20/11/2017.
//  Copyright © 2017 Kirill Korolev. All rights reserved.
//

#include "tspneuron.hpp"

namespace tsp { namespace net {
  
    tspneuron::tspneuron()
    {
        
    }
    
    tspneuron::~tspneuron()
    {
        for(auto link: links_)
            delete link;
    }
    
    void tspneuron::link(std::vector<tspneuron*> neurons)
    {
        for(auto neuron: neurons)
        {
            tsplink* l = new tsplink(this, neuron);
            links_.push_back(l);
        }
    }
    
}}
