#include <iostream>
#include <vector>

int main() {
    // create an empty vector of integers
    std::vector<int> vec;

    // add some elements to the vector
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    // print the size of the vector
    std::cout << "Size of vector: " << vec.size() << std::endl;

    // print the first element of the vector
    std::cout << "First element: " << vec[0] << std::endl;

    // print the last element of the vector
    std::cout << "Last element: " << vec.back() << std::endl;

    // change the value of the second element
    vec[1] = 40;

    // print all the elements of the vector using iterator
    std::cout << "All elements: ";
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // remove the last element from the vector
    vec.pop_back();

    // print the size of the vector again
    std::cout << "Size of vector after pop_back(): " << vec.size() << std::endl;

    // clear the vector
    vec.clear();

    // print the size of the vector after clear()
    std::cout << "Size of vector after clear(): " << vec.size() << std::endl;

    return 0;
}
