#include <iostream>
#include <unordered_map>
#include <string>

int main() {
    // Create an unordered_map with key type string and value type int
    std::unordered_map<std::string, int> age_map;

    // Insert key-value pairs into the map
    age_map["Alice"] = 30;
    age_map["Bob"] = 25;
    age_map["Carol"] = 35;

    // Find a value by key
    std::string key = "Alice";
    auto it = age_map.find(key);

    if (it != age_map.end()) {
        std::cout << "Age of " << key << " is: " << it->second << std::endl;
    } else {
        std::cout << key << " not found in the map." << std::endl;
    }

    // Iterate through the map and print key-value pairs
    for (const auto& pair : age_map) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    return 0;
}
