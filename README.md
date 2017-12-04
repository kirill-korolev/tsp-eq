# TSP EQ
Time series prediction based on exchange quotations

## Library
A class library consists of three "modules"

### tspmath
Several activation functions and a special function wrapper class that represents a functor

### tspset
Interface for parsing your csv files with the several options like features description and type casting.
Basic data structure for a neural net class

### tspnet
A bunch of classes which implement basic algorithms of neural networks

## Usage

Divide your basic dataset on pieces and generate a new one
```c++
#include "dataset_generation.hpp"
//generate_dataset(INPUT_DATASET, OUTPUT_DATASET, NUMBER OF PREV ROWS, ROWS AVERAGE, FEATURES...)
generate_dataset("bitcoin-usd-dataset-small.csv", "example.csv", 720, 5, tsp::set::tspfeature<double>("Weighted_Price"));
```

Parse it
```c++
#include "tspset.hpp"
auto dataset = tsp::set::make_set<double>("example.csv");
```

Initialize your network with neurons quantity on each layer and a learning rate
```c++
tsp::net::tspnet<3> net({100, 65, 43}, 0.05);
```

Training session
```c++
for(int i = 0; i < dataset.size(); ++i){
    net.train(dataset.at(i));
}
```
