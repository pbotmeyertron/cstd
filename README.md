## cstd
This is a header-only library that implements most of the C++ STL container classes in C. Just select the header you want to use and each will contain most of the functionality of its C++ STL equivalent. It currently supports:

- deque
- forward_list
- list
- map
- multimap
- multiset
- set
- unordered_map
- unordered_set
- vector

Most of the STL member functions are supported for each type. Examples for each type are provided in the examples folder along with the equivalent C++ code to get you started.

An example demonstrating commonly-used functionality with std::map:
```c++
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
```
And the C version:
```c++
#include "cstd_map.h"

int32_t string_compare(const void* a, const void* b) {
    return strcmp((const char*)a, (const char*)b);
}

void print_map(map_t* map) {
    for (node_t* node = map->root; node != NULL; node = node->right) {
        printf("%s: %d\n", (char*)node->key, *(int*)node->value);
    }
}

int main() {
    map_t age_map;
    cstd_map_init(&age_map, sizeof(char*), sizeof(int), string_compare);

    // Add key-value pairs to the map
    char* alice_key = "Alice";
    int alice_value = 30;
    cstd_map_insert(&age_map, alice_key, &alice_value);

    char* bob_key = "Bob";
    int bob_value = 25;
    cstd_map_insert(&age_map, bob_key, &bob_value);

    char* charlie_key = "Charlie";
    int charlie_value = 35;
    cstd_map_insert(&age_map, charlie_key, &charlie_value);

    // Access and modify values using the key
    alice_value = 31;
    cstd_map_insert(&age_map, alice_key, &alice_value);

    // Check if a key is present in the map
    char* eve_key = "Eve";
    if (!cstd_map_find(&age_map, eve_key)) {
        printf("Eve is not in the map\n");
    }

    // Iterate and print key-value pairs in the map
    print_map(&age_map);

    // Remove an element from the map
    cstd_map_delete(&age_map, bob_key);

    // Print the map size
    printf("Map size: %zu\n", cstd_map_size(&age_map));

    // Free the map memory
    cstd_map_free(&age_map);

    return 0;
}
```
### Why would you do this?
Why not?
