#ifndef ALGORITHM_UTILS
#define ALGORITHM_UTILS

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<unordered_map>

namespace algorithm::utils {
    
        // arr should be either std::array or std::vector
        template<typename T>
        bool validate_sorted_array(T arr);
    }

    // load iris dataset 
    namespace iris {
        using data = std::pair<std::vector<std::vector<float>>, std::vector<int>>;
    }
}

#endif
