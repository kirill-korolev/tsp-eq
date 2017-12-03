//
//  tsplayer.cpp
//  TSP-EQ
//
//  Created by Kirill Korolev on 20/11/2017.
//  Copyright © 2017 Kirill Korolev. All rights reserved.
//

#include "tsplayer.hpp"

namespace tsp { namespace net {

    tsplayer::tsplayer(uint32_t neurons, tsplayer* prev, tsplayer* next)
    {
        prevLayer_ = prev;
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
    
    void tsplayer::reset() const
    {
        for(int i = 0; i < neurons_.size(); ++i)
        {
            neurons_[i]->net = 0.0;
            neurons_[i]->out = 0.0;
        }
    }
    
    void tsplayer::learn(const double& learning_rate)
    {
        if(prevLayer_ != nullptr){
            for(int i = 0; i < prevLayer_->neurons_.size(); ++i){
                for(int j = 0; j < prevLayer_->neurons_[i]->links.size(); ++j){
                    prevLayer_->neurons_[i]->links[j]->weight =
                    prevLayer_->neurons_[i]->links[j]->weight - learning_rate * 1;
                }
            }
            
            prevLayer_->learn(learning_rate);
        }
    }
    
    void tsplayer::feed()
    {
        nextLayer_->reset();
        
        for(int i = 0; i < nextLayer_->height(); ++i){
            for(int j = 0; j < neurons_.size(); ++j){
                nextLayer_->getNeuron(i)->net +=
                neurons_[j]->net * neurons_[j]->links[i]->weight;
            }
            
            if(nextLayer_->func == nullptr) continue;
            
            nextLayer_->getNeuron(i)->out = nextLayer_->func->operator()(nextLayer_->getNeuron(i)->net);
        }
        
        nextLayer_->feed();
    }
    
    size_t tsplayer::height() const
    {
        return neurons_.size();
    }
    
    tspneuron* tsplayer::getNeuron(int i)
    {
        return neurons_[i];
    }
    
    void tsplayer::setNext(tsplayer* layer){
        nextLayer_ = layer;
    }
    
    void tsplayer::setPrev(tsplayer* layer){
        prevLayer_ = layer;
    }

    
    tspinput::tspinput(uint32_t neurons, tsplayer* next): tsplayer(neurons, nullptr, next){}
    tspinput::~tspinput(){}
    
    void tspinput::feed(const set::tsprow& row)
    {
        for(int i = 0; i < neurons_.size(); ++i)
            neurons_[i]->net = boost::any_cast<double>(row[i]);
        
        tsplayer::feed();
    }
    
    tspoutput::tspoutput(uint32_t neurons, tsplayer* prev): tsplayer(neurons, prev, nullptr){}
    tspoutput::~tspoutput(){}
    
    void tspoutput::feed()
    {
        if(delegate != nullptr)
            delegate->didFinishedComputations();
    }
    
    void tspoutput::initLearning(const double& learning_rate, const set::tsprow& row){
        
        set::tsprow outputs(row.end() - neurons_.size(), row.end());
        double total_error = 0.0;

        for(int i = 0; i < neurons_.size(); ++i){
            double error = pow(neurons_[i]->out - boost::any_cast<double>(outputs[i]), 2) / 2;
            total_error += error;
        }

        std::cout << "total error: " << total_error << std::endl;
        
        learn(learning_rate);
    }
    
    
}}
