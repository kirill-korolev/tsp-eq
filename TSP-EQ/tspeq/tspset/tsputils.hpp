//
//  tsputils.hpp
//  TSP-EQ
//
//  Created by Kirill Korolev on 29/11/2017.
//  Copyright © 2017 Kirill Korolev. All rights reserved.
//

#ifndef tsputils_hpp
#define tsputils_hpp

#include <string>

namespace tsp{ namespace utils {
    
    static inline void ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
            return !std::isspace(ch);
        }));
    }

    static inline void rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
            return !std::isspace(ch);
        }).base(), s.end());
    }

    static inline void trim(std::string &s) {
        ltrim(s);
        rtrim(s);
    }
    
}}

#endif /* tsputils_hpp */
