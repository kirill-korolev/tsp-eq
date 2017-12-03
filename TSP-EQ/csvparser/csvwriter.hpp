//
//  csvwriter.hpp
//  TSP-EQ
//
//  Created by Kirill Korolev on 30/11/2017.
//  Copyright © 2017 Kirill Korolev. All rights reserved.
//

#ifndef csvwriter_hpp
#define csvwriter_hpp

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

namespace csv{
    
    class Writer{
    public:
        typedef std::vector<std::vector<std::vector<double>>> data_format;
        Writer(const char* fileName, const data_format& data);
        Writer(const Writer&)=delete;
        Writer& operator=(const Writer&)=delete;
    private:
        const int buffer_size = 10000;
    };
}

#endif /* csvwriter_hpp */
