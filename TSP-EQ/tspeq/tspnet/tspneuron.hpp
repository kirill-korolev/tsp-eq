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
    private:
        std::vector<tsplink*> links_;
        
    };
    
}}

#endif /* tspneuron_hpp */
