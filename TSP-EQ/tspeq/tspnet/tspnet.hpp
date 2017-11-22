//
//  tspnet.hpp
//  TSP-EQ
//
//  Created by Kirill Korolev on 20/11/2017.
//  Copyright © 2017 Kirill Korolev. All rights reserved.
//

#ifndef tspnet_hpp
#define tspnet_hpp

#include <array>
#include <vector>
#include "../tspset/itspset.hpp"
#include "tsplayer.hpp"

using tsp::set::itspset;

namespace tsp { namespace net {

    template <size_t Layers>
    class tspnet
    {
    public:
        tspnet(std::array<uint32_t, Layers> neurons);
        ~tspnet();
        tspnet(const tspnet&)=delete;
        tspnet& operator=(const tspnet&)=delete;
        
        template <typename... Args>
        void train(const itspset<Args...>& set);
    private:
        tspinput* inputLayer_;
        tspoutput* outputLayer_;
        std::vector<tsplayer*> hiddenLayers_;
    };
    
}}

#include "tspnet_impl.hpp"

#endif /* tspnet_hpp */
