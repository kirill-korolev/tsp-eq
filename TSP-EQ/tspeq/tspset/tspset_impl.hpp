//
//  tspset.cpp
//  TSP-EQ
//
//  Created by Kirill Korolev on 22/11/2017.
//  Copyright © 2017 Kirill Korolev. All rights reserved.
//

#include "tsputils.hpp"

namespace tsp { namespace set {

    template <typename FeatureType>
    inline auto read_row(Row r, std::vector<int>& indexes, FeatureType f) ->
    std::vector<boost::any>
    {
        std::vector<boost::any> t;
        auto value = r.getValue<typename FeatureType::f_type>(indexes.front());
        t.push_back(value);
        return t;
    }
    
    template <typename FeatureType, typename... Features>
    inline std::vector<boost::any> read_row(Row r, std::vector<int>& indexes, FeatureType f, Features... features)
    {
        auto t = read_row(r, indexes, f);
        auto other = read_row(r, indexes, features...);
        t.insert(t.end(), other.begin(), other.end());
        return t;
    }
    
    template <typename T>
    inline std::vector<boost::any> read_row(Row r)
    {
        std::vector<boost::any> result;
        
        for(int i = 0; i < r.size(); ++i){
            auto value = r.getValue<T>(i);
            result.push_back(value);
        }

        return result;
    }

    template <typename FeatureType>
    inline void find_features(std::vector<int>& indexes, const std::vector<std::string>& header, const tspfeature<FeatureType>& f){
        for(int i = 0; i < header.size(); ++i){
            auto s = header.at(i);
            utils::trim(s);
            if(s.compare(f.getTitle()) == 0){
                indexes.push_back(i);
                return;
            }
        }
        throw std::invalid_argument("No such feature in a dataset");
    }
    
    template <typename FeatureType, typename... Features>
    inline void find_features(std::vector<int>& indexes, const std::vector<std::string>& header, const tspfeature<FeatureType>& f, Features... features){
        find_features(indexes, header, f);
        find_features(indexes, header, features...);
    }

    
    template <typename T, size_t Index, size_t Size>
    inline auto make_set(const char* fileName) -> tspset{
        Parser parser(fileName);
        std::vector<std::vector<boost::any>> result;
        
        for(int i = Index; i < (Size == 0 ? parser.rowCount() : Index + Size); ++i)
        {
            auto row = read_row<T>(parser.getRow(i));
            result.push_back(std::move(row));
        }
        
        return result;
    }
    
    template <size_t Index, size_t Size, typename... Features>
    inline auto make_set(const char* fileName, Features... features) ->
    tspset
    {
        Parser parser(fileName);
        auto header = parser.getHeader();
        if(header.size() == 0) throw std::length_error("There is no header in a dataset");
        std::vector<int> indexes;
        find_features(indexes, header, features...);
        
        std::vector<std::vector<boost::any>> result;
        
        for(int i = Index; i < (Size == 0 ? parser.rowCount() : Index + Size); ++i)
        {
            auto row = read_row(parser.getRow(i), indexes, features...);
            result.push_back(std::move(row));
        }
        
        return result;
    }
    

    inline tspset get_last_rows(const tspset& set, uint index, size_t n)
    {
        try{
            tspset s(set.begin() + index - n, set.begin() + index);
            return s;
        }
        catch(std::exception& e)
        {
            throw e;
        }
    }
    
    inline std::vector<tspset> divide(const tspset& set, size_t size)
    {
        size_t set_size = set.size();
        size_t pieces = std::ceil((double)set_size / size);
        
        std::vector<tspset> sets;
        
        for(int i = 0; i < pieces; ++i)
        {
            tspset::const_iterator p = set.begin() + (i + 1) * size;
            tspset subset(set.begin() + i * size, p < set.end() ? p : set.end());
            sets.push_back(std::move(subset));
        }
        
        return sets;
    }

    
}}


