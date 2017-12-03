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
#include "tspfunction.hpp"
#include "tsplayer.hpp"

namespace tsp { namespace net {
    
    template <size_t Layers>
    class tspnet: public itask
    {
    public:
        tspnet(std::array<uint32_t, Layers> neurons, double learning_rate);
        ~tspnet();
        tspnet(const tspnet&)=delete;
        tspnet& operator=(const tspnet&)=delete;
        
        void set_function(math::tspifunction* func);
        void set_out_function(math::tspifunction* func);
        void train(const set::tsprow& row);
        
        void didFinishedComputations() override;
    private:
        const set::tsprow* tempRow_ = nullptr;
        double learning_rate_;
        tspinput* inputLayer_;
        tspoutput* outputLayer_;
        std::vector<tsplayer*> hiddenLayers_;
    };
    
}}

#include "tspnet_impl.hpp"

#endif /* tspnet_hpp */
