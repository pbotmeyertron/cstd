#include <iostream>
#include <list>
#include <algorithm>

int main() {
    // Create a list of integers
    std::list<int> numbers;

    // Add elements to the list (push_back inserts elements at the end)
    numbers.push_back(10);
    numbers.push_back(20);
    numbers.push_back(30);
    numbers.push_back(40);

    // Insert an element in the middle of the list
    std::list<int>::iterator it = std::next(numbers.begin(), 2);
    numbers.insert(it, 25);

    // Remove an element from the list (erase removes elements by iterator)
    it = std::find(numbers.begin(), numbers.end(), 20);
    if (it != numbers.end()) {
        numbers.erase(it);
    }

    // Iterate and print elements in the list
    for (int num : numbers) {
        std::cout << num << " ";
    }

    std::cout << std::endl;
    return 0;
}
