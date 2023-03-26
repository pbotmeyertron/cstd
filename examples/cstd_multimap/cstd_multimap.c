#include "../../cstd_multimap.h"

int32_t string_compare(const void* a, const void* b) {
    return strcmp((const char*)a, (const char*)b);
}

void print_student_grades(multimap_t* student_grades) {
    for (size_t i = 0; i < cstd_multimap_size(student_grades); ++i) {
        char* student_name = (char*)student_grades->data[i].key;
        vector_t* grades = &(student_grades->data[i].value);

        for (size_t j = 0; j < cstd_vector_size(grades); ++j) {
            int grade = *((int*)cstd_vector_at(grades, j));
            printf("%s: %d\n", student_name, grade);
        }
    }
}

int main() {
    multimap_t student_grades;
    cstd_multimap_init(&student_grades, sizeof(char*), sizeof(int), string_compare);

    char* alice = "Alice";
    char* bob = "Bob";
    char* carol = "Carol";

    int grade1 = 90;
    int grade2 = 85;
    int grade3 = 95;
    int grade4 = 92;
    int grade5 = 88;

    cstd_multimap_insert(&student_grades, alice, &grade1);
    cstd_multimap_insert(&student_grades, bob, &grade2);
    cstd_multimap_insert(&student_grades, alice, &grade3);
    cstd_multimap_insert(&student_grades, carol, &grade4);
    cstd_multimap_insert(&student_grades, bob, &grade5);

    printf("All student grades:\n");
    print_student_grades(&student_grades);

    char* student_name = "Alice";
    vector_t* alice_grades = cstd_multimap_get(&student_grades, student_name);
    if (alice_grades) {
        printf("\nGrades for %s:\n", student_name);
        for (size_t i = 0; i < cstd_vector_size(alice_grades); ++i) {
            int grade = *((int*)cstd_vector_at(alice_grades, i));
            printf("%d\n", grade);
        }
    }

    cstd_multimap_free(&student_grades);
    return 0;
}
