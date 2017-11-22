//
//  tspset.cpp
//  TSP-EQ
//
//  Created by Kirill Korolev on 22/11/2017.
//  Copyright © 2017 Kirill Korolev. All rights reserved.
//

namespace tsp { namespace set {
    
    template <typename ...Args>
    tspset<Args...>::tspset(vectors_type vectors)
    {
        vectors_ = std::move(vectors);
    }
    
    template <typename ...Args>
    std::tuple<Args...> tspset<Args...>::at(int i) const
    {
        return vectors_[i];
    }
    
    template <size_t Index, typename First>
    std::tuple<First> read_row(Row r)
    {
        auto value = r.getValue<First>(Index);
        return std::make_tuple(value);
    }
    
    template <size_t Index, typename First, typename Second, typename... Args>
    std::tuple<First, Second, Args...> read_row(Row r)
    {
        auto value = r.getValue<First>(Index);
        auto t = read_row<Index + 1, Second, Args...>(r);
        return std::tuple_cat(std::make_tuple(value), t);
    }
    
    
    template <typename... Args>
    tspset<Args...> make_set(const char* fileName)
    {
        Parser parser(fileName);
        typename tspset<Args...>::vectors_type temp;
        
        for(int i = 0; i < parser.rowCount(); ++i)
        {
            auto row = parser.getRow(i);
            auto tuple = read_row<0, Args...>(row);
            temp.push_back(tuple);
        }
        
        return tspset<Args...>(temp);
    }
    
}}
