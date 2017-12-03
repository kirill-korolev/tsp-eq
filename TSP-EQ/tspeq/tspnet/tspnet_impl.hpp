//
//  tspnet.cpp
//  TSP-EQ
//
//  Created by Kirill Korolev on 20/11/2017.
//  Copyright © 2017 Kirill Korolev. All rights reserved.
//

#pragma once

#include "tspset.hpp"
#include "tspmath.hpp"

namespace tsp { namespace net{

    template <size_t Layers>
    tspnet<Layers>::tspnet(std::array<uint, Layers> neurons, double learning_rate)
    {
        learning_rate_ = learning_rate;
        
        outputLayer_ = new tspoutput(neurons[Layers - 1]);
        tsplayer* next = outputLayer_;
        
        for(int i = Layers - 2; i > 0; --i)
        {
            tsplayer* layer = new tsplayer(neurons[i], nullptr, next);
            
            if(i == Layers - 2) {
                outputLayer_->setPrev(layer);
            }
            else{
                next->setPrev(layer);
            }
            
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
    void tspnet<Layers>::set_function(math::tspifunction* func){
        
        for(int i = 0; i < hiddenLayers_.size(); ++i)
            hiddenLayers_[i]->func = func;
    }
    
    template <size_t Layers>
    void tspnet<Layers>::set_out_function(math::tspifunction* func){
        outputLayer_->func = func;
    }

    
    template <size_t Layers>
    void tspnet<Layers>::train(const set::tsprow& row)
    {
        tempRow_ = &row;
        outputLayer_->delegate = this;
        inputLayer_->feed(row);
    }
    
    
    template <size_t Layers>
    void tspnet<Layers>::didFinishedComputations(){
        outputLayer_->initLearning(learning_rate_, *tempRow_);
    }
    
}}
