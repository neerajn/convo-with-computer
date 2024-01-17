//
// Created by Neeraj Nandakumar on 07/01/2024.


#include <iostream>
#include <algorithm>
#include <vector>

void printAllSubSeq(int pickIndex,
                    const std::vector<int>& v,
                    std::vector<int>& pickList,
                    const int inputSize)
{
    if (pickIndex == inputSize) {
        std::for_each(
            pickList.begin(),
            pickList.end(),
            [](const auto& elem){
                std::cout << elem << " ";
            });

        if (pickList.empty()) {
            std::cout << "{}" <<  std::endl;
        }
        else {
            std::cout << std::endl;
        }
        return;
    }
    //pick the value at pick index
    pickList.push_back(v[pickIndex]);
    printAllSubSeq(pickIndex + 1, v, pickList, inputSize);

    // Don't pick the value at pick index.
    pickList.pop_back();
    printAllSubSeq(pickIndex + 1, v, pickList, inputSize);
}

int main()
{
    //std::vector<int> v = {};
    //std::vector<int> v = {1};
    //std::vector<int> v = {1, 2};
    std::vector<int> v = {3, 1, 2};
    std::vector<int> pickable = {};
    printAllSubSeq(0, v, pickable, v.size());

    return 0;
}