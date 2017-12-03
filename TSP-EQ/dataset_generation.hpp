//
//  dataset_generation.cpp
//  TSP-EQ
//
//  Created by Kirill Korolev on 30/11/2017.
//  Copyright © 2017 Kirill Korolev. All rights reserved.
//

#include "dataset_generation.h"


namespace  {

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

    void generate_dataset(const char* inputFile, const char* outputFile, size_t rows_division, size_t rows_average){
        
        //Dataset reading
        auto dataset = tsp::set::make_set(inputFile, tspfeature<double>("Weighted_Price"));
        
        size_t rows = std::ceil((double)dataset.size() / rows_division);
        
        using tspsetd = std::vector<std::vector<double>>;
        std::vector<tspsetd> gen_rows;
        
        for(int i = 0; i < rows; ++i){
            
            //Data for the last 24 hours
            auto last_set = tsp::set::get_last_rows(dataset, rows_division * (i + 1), rows_division);
            
            //Division on subsequences
            auto intervals = tsp::set::divide(last_set, rows_average);
            
            tspsetd deriv(intervals.size() - 1, std::vector<double>(last_set.front().size(), 0));
            
            //Average on an interval
            auto p1 = average(intervals.front());
            
            //Increment of each interval
            for(int i = 1; i < intervals.size(); ++i){
                auto p2 = average(intervals[i]);
                
                for(int j = 0; j < p1.size(); ++j){
                    deriv[i - 1][j] = normalize(p1[j], p2[j]);
                }
                
                p1 = p2;
            }
            
            gen_rows.push_back(deriv);
        }
        
        
        csv::Writer writer(outputFile, gen_rows);
    }

}
