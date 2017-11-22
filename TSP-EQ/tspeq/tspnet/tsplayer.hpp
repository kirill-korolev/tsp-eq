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

#include "tspneuron.hpp"
#include "../tspset/itspset.hpp"

using tsp::set::itspset;

namespace tsp { namespace net {
    
    class tsplayer
    {
    public:
        tsplayer(uint32_t neurons, tsplayer* next=nullptr);
        virtual ~tsplayer();
        tsplayer(const tsplayer&)=delete;
        tsplayer& operator=(const tsplayer&)=delete;
    protected:
        std::vector<tspneuron*> neurons_;
        tsplayer* nextLayer_;
    };
    
    class tspinput: public tsplayer
    {
    public:
        tspinput(uint32_t neurons, tsplayer* next);
        ~tspinput();
        
        template <typename... Args>
        void init(const itspset<Args...>& set);
    };
    
    class tspoutput: public tsplayer
    {
    public:
        tspoutput(uint32_t neurons);
        ~tspoutput();
    };
    
}}

#endif /* tsplayer_hpp */
