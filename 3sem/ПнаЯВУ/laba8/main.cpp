#include <iostream>
#include <vector>
#include <algorithm>

void doubleFunc(int& num) {
    num *= 2;
}

int main() {
    std::vector<int> myVector;
    myVector.push_back(4);
    myVector.push_back(1);
    myVector.push_back(2);
    myVector.push_back(3);

    std::cout << "Vector elements: ";
    for (int i : myVector) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::sort(myVector.begin(), myVector.end());

    std::cout << "Sorted vector elements: ";
    for (int i : myVector) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::for_each(myVector.begin(), myVector.end(), doubleFunc);

    std::cout << "Doubled vector elements: ";
    for (int i : myVector) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}