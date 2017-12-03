//
//  dataset_generation.hpp
//  TSP-EQ
//
//  Created by Kirill Korolev on 30/11/2017.
//  Copyright © 2017 Kirill Korolev. All rights reserved.
//

#ifndef dataset_generation_h
#define dataset_generation_h

#include <iostream>
#include <vector>
#include <boost/any.hpp>
#include "csvparser/csvwriter.hpp"
#include "tspeq/tspset/tspset.hpp"
#include "tspeq/tspset/tspfeature.hpp"
#include "tspeq/tspmath/tspmath.hpp"

using tsp::set::tspfeature;

namespace {

    std::vector<double> average(const tsp::set::tspset& set){
        std::vector<double> sum(set.front().size(), 0);
        std::vector<double> avg(set.front().size(), 0);
        
        for(int i = 0; i < set.size(); ++i){
            for(int j = 0; j < set[i].size(); ++j){
                sum[j] += boost::any_cast<double>(set[i][j]);
            }
        }
        
        for(int i = 0; i < sum.size(); ++i)
            avg[i] = sum[i] / set.size();
        
        return avg;
    }

    double normalize(double x, double y){
        double f = y / x;
        return tsp::math::sigmoid(std::pow(10, 9) * std::pow(f - 1, 3), 1);
    }
    
    template <typename... Features>
    void generate_dataset(const char* inputFile, const char* outputFile, size_t rows_division, size_t rows_average, Features... features){
        
        //Dataset reading
        auto dataset = tsp::set::make_set(inputFile, features...);
        
        size_t rows = dataset.size() / rows_division;
        
        using tspsetd = std::vector<std::vector<double>>;
        std::vector<tspsetd> gen_rows;
        
        for(int i = 0; i < rows; ++i){
            
            //Data for the last N hours
            auto last_set = tsp::set::get_last_rows(dataset, rows_division * (i + 1), rows_division);
            
            //Division on subsequences
            auto intervals = tsp::set::divide(last_set, rows_average);
            
            tspsetd deriv(intervals.size() - 1, std::vector<double>(last_set.front().size(), 0));
            
            //Average on an interval
            auto p1 = average(intervals.front());
            
            //Increment of each interval
            for(int k = 1; k < intervals.size(); ++k){
                auto p2 = average(intervals[k]);
                
                for(int j = 0; j < p1.size(); ++j){
                    deriv[k - 1][j] = normalize(p1[j], p2[j]);
                }
                
                p1 = p2;
            }
            
            gen_rows.push_back(deriv);
        }
        
        
        csv::Writer writer(outputFile, gen_rows);
    }

}

#endif /* dataset_generation_h */
