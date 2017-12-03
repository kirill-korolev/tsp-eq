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
#include <array>
#include <exception>
#include <string>
#include <cmath>
#include <boost/any.hpp>

#include "../../csvparser/csvparser.hpp"
#include "tspfeature.hpp"

using csv::Parser;
using csv::Row;

namespace tsp { namespace set {
    
    typedef std::vector<boost::any> tsprow;
    typedef std::vector<tsprow> tspset;
    
    template <typename T, size_t Index=0, size_t Size=0>
    auto make_set(const char* fileName) -> tspset;
    
    template <size_t Index=0, size_t Size=0, typename... Features>
    auto make_set(const char* fileName, Features... features) -> tspset;

    tspset get_last_rows(const tspset& set, uint index, size_t n);
    std::vector<tspset> divide(const tspset& set, size_t size);
}}

#include "tspset_impl.hpp"

#endif /* tspset_hpp */
