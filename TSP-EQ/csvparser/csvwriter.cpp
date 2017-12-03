//
//  csvwriter.cpp
//  TSP-EQ
//
//  Created by Kirill Korolev on 30/11/2017.
//  Copyright © 2017 Kirill Korolev. All rights reserved.
//

#include "csvwriter.hpp"

namespace csv{
    
    Writer::Writer(const char* fileName, const data_format& data){
        
        std::ofstream file;
        std::vector<char> buf;
        buf.resize(buffer_size);
        file.rdbuf()->pubsetbuf(&buf[0], buffer_size);
        
        file.open(fileName);
        
        if(file.is_open())
        {
            size_t rows_number = data.size();
            size_t row_size = data.front().size();
            size_t tuple_size = data.front().front().size();
            
            for(int i = 0; i < tuple_size; ++i){
                for(int j = 0; j < row_size; ++j){
                    file << "r_" << (j + 1) << "_" << (i + 1);
                    if(j != row_size - 1) file << ",";
                }
            }
            
            file << std::endl;
            
            for(int i = 0; i < rows_number; ++i){
                for(int j = 0; j < tuple_size; ++j){
                    for(int k = 0; k < row_size; ++k){
                        file << data[i][k][j];
                        if(k != row_size - 1) file << ",";
                    }
                }
                
                file << std::endl;
            }

            
        }
        
        file.close();
    }
    
}
