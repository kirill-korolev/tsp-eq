//
//  tspnet.cpp
//  TSP-EQ
//
//  Created by Kirill Korolev on 20/11/2017.
//  Copyright © 2017 Kirill Korolev. All rights reserved.
//

namespace tsp { namespace net{
    
    template <size_t Layers>
    tspnet<Layers>::tspnet(std::array<uint, Layers> neurons)
    {
        outputLayer_ = new tspoutput(neurons[Layers - 1]);
        tsplayer* next = outputLayer_;
        
        for(int i = 1; i < Layers - 1; ++i)
        {
            tsplayer* layer = new tsplayer(neurons[i], next);
            hiddenLayers_.push_back(layer);
            next = layer;
        }
        
        inputLayer_ = new tspinput(neurons[0], next);
    }
    
    template <size_t Layers>
    tspnet<Layers>::~tspnet()
    {
        delete inputLayer_;
        
        for(auto layer: hiddenLayers_)
            delete layer;
        
        delete outputLayer_;
    }
    
    template <size_t Layers>
    template <typename... Args>
    void tspnet<Layers>::train(const itspset<Args...>& set)
    {
        inputLayer_->init(set);
    }
    
}}
