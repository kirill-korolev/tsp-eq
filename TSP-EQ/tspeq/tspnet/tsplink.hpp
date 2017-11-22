//
//  tsplink.hpp
//  TSP-EQ
//
//  Created by Kirill Korolev on 20/11/2017.
//  Copyright © 2017 Kirill Korolev. All rights reserved.
//

#ifndef tsplink_hpp
#define tsplink_hpp

namespace tsp { namespace net{

    class tspneuron;
    
    class tsplink
    {
    public:
        tsplink(tspneuron* lhs, tspneuron* rhs);
        ~tsplink();
    private:
        tspneuron* left_;
        tspneuron* right_;
    };
    
}}

#endif /* tsplink_hpp */
