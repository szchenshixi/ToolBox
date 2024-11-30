#include <iostream>
#include <utility>
#include <vector>

#include "max_heap.hpp"

using myType = std::pair<int, std::vector<int>>;

int main() {
    TopK<myType> top100(40);

    top100.emplace(myType{10, {6, 2, 3}});
    top100.emplace(myType{20, {2, 4}});
    top100.emplace(myType{20, {1, 2, 4}});
    top100.emplace(myType{20, {1, 4}});
    top100.emplace(myType{1, {1, 2, 2, 3}});
    top100.emplace(myType{30, {1, 2, 3}});
    top100.emplace(myType{0, {1, 3}});
    top100.emplace(myType{100, {7, 1, 2, 3}});
    top100.emplace(myType{120, {2, 3}});

    std::vector<myType> results = top100.finalize();
    for (const auto& item : results) {
        std::cout << "( " << item.first << ", [";
        bool isFirst = true;
        for (const auto& value : item.second) {
            if (isFirst) {
                std::cout << value;
                isFirst = false;
            } else {
                std::cout << ", " << value;
            }
        }
        std::cout << "] )\n";
    }
};
