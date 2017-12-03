//
//  tsplayer.hpp
//  TSP-EQ
//
//  Created by Kirill Korolev on 20/11/2017.
//  Copyright © 2017 Kirill Korolev. All rights reserved.
//

#ifndef tsplayer_hpp
#define tsplayer_hpp

#include <stdint.h>
#include <vector>
#include <iostream>
#include <boost/any.hpp>

#include "tspneuron.hpp"
#include "tspfunction.hpp"
#include "tspset.hpp"

namespace tsp { namespace net {
    
    class itask{
    public:
        virtual void didFinishedComputations()=0;
        virtual ~itask(){}
    };
    
    template <size_t Layers>
    class tspnet;
    
    class tsplayer
    {
    public:
        tsplayer(uint32_t neurons, tsplayer* prev=nullptr, tsplayer* next=nullptr);
        virtual ~tsplayer();
        tsplayer(const tsplayer&)=delete;
        tsplayer& operator=(const tsplayer&)=delete;
        
        virtual void feed();
        virtual void learn(const double& learning_rate);
        
        void reset() const;
        size_t height() const;
        tspneuron* getNeuron(int i);
        
        void setNext(tsplayer* layer);
        void setPrev(tsplayer* layer);
        
        math::tspifunction* func = nullptr;
    protected:
        std::vector<tspneuron*> neurons_;
        tsplayer* nextLayer_;
        tsplayer* prevLayer_;
    };
    
    class tspinput: public tsplayer
    {
    public:
        tspinput(uint32_t neurons, tsplayer* next=nullptr);
        ~tspinput();
        using tsplayer::feed;
        void feed(const set::tsprow& row);
    };
    
    class tspoutput: public tsplayer
    {
    public:
        
        tspoutput(uint32_t neurons, tsplayer* prev=nullptr);
        ~tspoutput();
        void feed() override;
        void initLearning(const double& learning_rate, const set::tsprow& row);
        itask* delegate;
    private:
    };
    
}}



#endif /* tsplayer_hpp */
