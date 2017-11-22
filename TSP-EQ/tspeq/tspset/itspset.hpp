//
//  itspset.hpp
//  TSP-EQ
//
//  Created by Kirill Korolev on 22/11/2017.
//  Copyright © 2017 Kirill Korolev. All rights reserved.
//

#ifndef itspset_hpp
#define itspset_hpp

#include <tuple>

namespace tsp { namespace set {
    
    template <typename... Args>
    class itspset
    {
    public:
        virtual ~itspset(){}
        virtual std::tuple<Args...> at(int i) const=0;
    };
}}

#endif /* itspset_hpp */
