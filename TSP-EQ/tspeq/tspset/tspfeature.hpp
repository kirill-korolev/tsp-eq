//
//  tspfeature.hpp
//  TSP-EQ
//
//  Created by Kirill Korolev on 29/11/2017.
//  Copyright © 2017 Kirill Korolev. All rights reserved.
//

#ifndef tspfeature_hpp
#define tspfeature_hpp

#include <string>

namespace tsp{ namespace set{
    
    template <typename FeatureType>
    struct tspfeature{
        typedef FeatureType f_type;
        
        tspfeature(const char* str): str_(str){}
        
        inline const char* getTitle() const{
            return str_.c_str();
        }
        
    private:
        std::string str_;
    };
    
}}

#endif /* tspfeature_hpp */
