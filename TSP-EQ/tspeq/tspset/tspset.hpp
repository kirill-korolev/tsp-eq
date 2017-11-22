//
//  tspset.hpp
//  TSP-EQ
//
//  Created by Kirill Korolev on 22/11/2017.
//  Copyright © 2017 Kirill Korolev. All rights reserved.
//

#ifndef tspset_hpp
#define tspset_hpp

#include <vector>
#include <tuple>

#include "../../csvparser/csvparser.hpp"
#include "itspset.hpp"

using csv::Parser;
using csv::Row;

namespace tsp { namespace set {

    template <typename ...Args>
    class tspset: public itspset<Args...>{
    public:
        typedef std::vector<std::tuple<Args...>> vectors_type;
        explicit tspset(vectors_type);
        std::tuple<Args...> at(int i) const;
    private:
        vectors_type vectors_;
    };
    
    template <size_t Index, typename First>
    std::tuple<First> read_row(Row r);
    
    template <size_t Index, typename First, typename Second, typename... Args>
    std::tuple<First, Second, Args...> read_row(Row r);

    template <typename... Args>
    tspset<Args...> make_set(const char* fileName="");
    
}}

#include "tspset_impl.hpp"

#endif /* tspset_hpp */
