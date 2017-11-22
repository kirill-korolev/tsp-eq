//
//  tsplink.cpp
//  TSP-EQ
//
//  Created by Kirill Korolev on 20/11/2017.
//  Copyright © 2017 Kirill Korolev. All rights reserved.
//

#include "tsplink.hpp"

namespace tsp { namespace net {

    tsplink::tsplink(tspneuron* lhs, tspneuron* rhs)
    {
        left_ = lhs;
        right_ = rhs;
    }
    
    tsplink::~tsplink()
    {
        
    }
    
}}
