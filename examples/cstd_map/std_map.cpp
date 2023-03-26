#include <iostream>
#include <map>
#include <string>

int main() {
    // Create a map with string keys and integer values
    std::map<std::string, int> age_map;

    // Add key-value pairs to the map
    age_map["Alice"] = 30;
    age_map["Bob"] = 25;
    age_map["Charlie"] = 35;

    // Access and modify values using the key
    age_map["Alice"] = 31;

    // Check if a key is present in the map
    if (age_map.find("Eve") == age_map.end()) {
        std::cout << "Eve is not in the map" << std::endl;
    }

    // Iterate and print key-value pairs in the map
    for (const auto& pair : age_map) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    // Remove an element from the map
    age_map.erase("Bob");

    // Print the map size
    std::cout << "Map size: " << age_map.size() << std::endl;

    return 0;
}
