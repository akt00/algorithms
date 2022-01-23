#ifndef ALGORITHM_UTILS
#define ALGORITHM_UTILS
#include<iostream>
#include<unordered_map>


namespace algorithm {
    namespace util {
        // arr should be either std::array or std::vector
        template<typename T>
        bool validate_sorted_array(T arr);
    }
}

#endif
