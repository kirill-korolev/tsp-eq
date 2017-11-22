//
//  tsplayer.cpp
//  TSP-EQ
//
//  Created by Kirill Korolev on 20/11/2017.
//  Copyright © 2017 Kirill Korolev. All rights reserved.
//

#include "tsplayer.hpp"

namespace tsp { namespace net {

    tsplayer::tsplayer(uint32_t neurons, tsplayer* next)
    {
        nextLayer_ = next;
        
        for(int i = 0; i < neurons; ++i)
        {
            tspneuron* neuron = new tspneuron;
            if(next != nullptr) neuron->link(next->neurons_);
            neurons_.push_back(neuron);
        }
    }
    
    tsplayer::~tsplayer()
    {
        for(auto neuron: neurons_)
            delete neuron;
    }
    
    
    tspinput::tspinput(uint32_t neurons, tsplayer* next): tsplayer(neurons, next){}
    
    template <typename... Args>
    void tspinput::init(const itspset<Args...>& set)
    {
        for(int i = 0; i < neurons_.size(); ++i)
        {
            
        }
    }
    
    tspoutput::tspoutput(uint32_t neurons): tsplayer(neurons, nullptr){}
    
}}
