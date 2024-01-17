//
// Created by Neeraj Nandakumar on 07/01/2024.
//
#include <iostream>
#include <vector>
#include <algorithm>


int countSubSeqAddingToSum(int pickIndex,
                          const std::vector<int>& v,
                          const int inputSize,
                          int currentSum,
                          const int sum)
{
    if (pickIndex == inputSize) {
        if (currentSum == sum) {
            return 1;
        }
        return 0;
    }
    const int currentValue = v[pickIndex];
    currentSum += currentValue;
    int l = countSubSeqAddingToSum(pickIndex + 1, v, inputSize, currentSum, sum);

    currentSum -= currentValue;
    int r = countSubSeqAddingToSum(pickIndex + 1, v, inputSize, currentSum, sum);

    return l + r;
}

bool hasSubSeqAddingToSum(int pickIndex,
                            const std::vector<int>& v,
                            std::vector<int>& pickable,
                            const int inputSize,
                            int currentSum,
                            const int sum)
{
    if (pickIndex == inputSize) {
        if (currentSum == sum) {
            return true;
        }
        return false;
    }
    const int currentValue = v[pickIndex];
    pickable.push_back(currentValue);
    currentSum += currentValue;
    if (hasSubSeqAddingToSum(pickIndex + 1, v, pickable, inputSize, currentSum, sum)) {
        return true;
    }

    pickable.pop_back();
    currentSum -= currentValue;
    return hasSubSeqAddingToSum(pickIndex + 1, v, pickable, inputSize, currentSum, sum);
}

void printSubSeqAddingToSum(int pickIndex,
                            const std::vector<int>& v,
                            std::vector<int>& pickable,
                            const int inputSize,
                            int currentSum,
                            const int sum)
{
    if (pickIndex == inputSize) {
        if (currentSum == sum) {
            std::for_each(
                begin(pickable),
                end(pickable),
                  [](const auto& elem) {
                        std::cout << elem << " ";
                });
            std::cout << std::endl;
        }
        return;
    }
    const int currentValue = v[pickIndex];
    pickable.push_back(currentValue);
    currentSum += currentValue;
    printSubSeqAddingToSum(pickIndex + 1, v, pickable, inputSize, currentSum, sum);

    pickable.pop_back();
    currentSum -= currentValue;
    printSubSeqAddingToSum(pickIndex + 1, v, pickable, inputSize, currentSum, sum);
}

int main()
{
    std::vector<int> v = {1, 1, 2};
    std::vector<int> pickable = {};

    const int sum = 2;
    std::cout << "Print all subsequences that add to: " << sum << std::endl;
    printSubSeqAddingToSum(0, v, pickable, v.size(), 0, sum);

    std::cout << "Has subsequences that add to: " << sum << std::endl;
    pickable.clear();
    std::string has = hasSubSeqAddingToSum(0, v, pickable, v.size(), 0, sum) ?
    "true" : "false";
    std::cout << has << std::endl;

    std::cout << "Count of subsequences that add to: " << sum << std::endl;
    std::cout << countSubSeqAddingToSum(0, v, v.size(), 0, sum) << std::endl;

    return 0;
}