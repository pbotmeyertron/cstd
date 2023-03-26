#include "../../cstd_forward_list.h"

// A struct to represent a person
typedef struct {
    char name[50];
    int age;
} Person;

// A function to compare two persons by name
bool compare_person_name(void* person1, void* person2) {
    return strcmp(((Person*)person1)->name, ((Person*)person2)->name) == 0;
}

int main() {
    // Initialize the list
    forward_list_t list;
    cstd_forward_list_init(&list, sizeof(Person));

    // Add some people to the front of the list
    Person alice = {"Alice", 25};
    Person bob = {"Bob", 30};
    Person charlie = {"Charlie", 35};
    cstd_forward_list_push_front(&list, &alice);
    cstd_forward_list_push_front(&list, &bob);
    cstd_forward_list_push_front(&list, &charlie);

    // Find a person in the list by name
    Person search = {"Bob", 0};
    forward_list_node_t* node =
        cstd_forward_list_find(&list, &search, compare_person_name);
    if (node != NULL) {
        printf("Found person: %s, %d\n",
               ((Person*)cstd_forward_list_data(node))->name,
               ((Person*)cstd_forward_list_data(node))->age);
    } else {
        printf("Person not found\n");
    }

    // Erase a person from the list
    cstd_forward_list_erase_after(
        &list, cstd_forward_list_next(cstd_forward_list_next(list.head)));

    // Print the remaining people in the list
    forward_list_node_t* current = list.head;
    while (current != NULL) {
        printf("%s, %d\n", ((Person*)cstd_forward_list_data(current))->name,
               ((Person*)cstd_forward_list_data(current))->age);
        current = cstd_forward_list_next(current);
    }

    // Clean up the list
    cstd_forward_list_clear(&list);

    return 0;
}
