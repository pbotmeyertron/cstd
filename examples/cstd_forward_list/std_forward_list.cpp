#include <algorithm>
#include <cstring>
#include <forward_list>
#include <iostream>

// A struct to represent a person
struct Person {
    char name[50];
    int age;
};

// A function to compare two persons by name
bool compare_person_name(const Person& person1, const Person& person2) {
    return std::strcmp(person1.name, person2.name) == 0;
}

int main() {
    // Initialize the list
    std::forward_list<Person> list;

    // Add some people to the front of the list
    Person alice = {"Alice", 25};
    Person bob = {"Bob", 30};
    Person charlie = {"Charlie", 35};
    list.push_front(alice);
    list.push_front(bob);
    list.push_front(charlie);

    // Find a person in the list by name
    Person search = {"Bob", 0};
    auto it = std::find_if(
        list.begin(), list.end(),
        [&search](const Person& p) { return compare_person_name(search, p); });
    if (it != list.end()) {
        std::cout << "Found person: " << it->name << ", " << it->age
                  << std::endl;
    } else {
        std::cout << "Person not found" << std::endl;
    }

    // Erase a person from the list
    auto it2 = list.begin();
    std::advance(it2, 2);
    list.erase_after(list.before_begin(), it2);

    // Print the remaining people in the list
    for (const auto& person : list) {
        std::cout << person.name << ", " << person.age << std::endl;
    }

    // Clean up the list
    list.clear();

    return 0;
}
