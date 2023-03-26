#include <iostream>
#include <set>

int main() {
    // Declare a multiset of integers
    std::multiset<int> num_multiset;

    // Insert elements into the multiset
    num_multiset.insert(5);
    num_multiset.insert(3);
    num_multiset.insert(7);
    num_multiset.insert(5);
    num_multiset.insert(1);

    // Display the contents of the multiset
    std::cout << "Contents of the multiset: ";
    for (const auto &element : num_multiset) {
        std::cout << element << ' ';
    }
    std::cout << std::endl;

    // Find the count of a specific element
    int target = 5;
    size_t count = num_multiset.count(target);
    std::cout << "Count of " << target << " in the multiset: " << count << std::endl;

    // Erase an element
    int to_erase = 3;
    num_multiset.erase(to_erase);

    // Display the contents after erasing
    std::cout << "Contents of the multiset after erasing " << to_erase << ": ";
    for (const auto &element : num_multiset) {
        std::cout << element << ' ';
    }
    std::cout << std::endl;

    return 0;
}
