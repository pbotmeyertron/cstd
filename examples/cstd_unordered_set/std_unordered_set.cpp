#include <iostream>
#include <unordered_set>
#include <string>

int main() {
    // Create an unordered_set of strings
    std::unordered_set<std::string> name_set;

    // Insert elements into the set
    name_set.insert("Alice");
    name_set.insert("Bob");
    name_set.insert("Carol");

    // Check if an element exists in the set
    std::string name = "Alice";
    if (name_set.find(name) != name_set.end()) {
        std::cout << name << " found in the set." << std::endl;
    } else {
        std::cout << name << " not found in the set." << std::endl;
    }

    // Iterate through the set and print the elements
    for (const auto& element : name_set) {
        std::cout << element << std::endl;
    }

    return 0;
}
