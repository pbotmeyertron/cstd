#include <iostream>
#include <map>
#include <string>

int main() {
    // Declare a multimap with std::string as key type and int as value type
    std::multimap<std::string, int> student_grades;

    // Insert key-value pairs into the multimap
    student_grades.insert({"Alice", 90});
    student_grades.insert({"Bob", 85});
    student_grades.insert({"Alice", 95});
    student_grades.insert({"Carol", 92});
    student_grades.insert({"Bob", 88});

    // Print all the key-value pairs in the multimap
    std::cout << "All student grades:" << std::endl;
    for (const auto& student_grade : student_grades) {
        std::cout << student_grade.first << ": " << student_grade.second << std::endl;
    }

    // Find and print all grades of a specific student
    std::string student_name = "Alice";
    auto range = student_grades.equal_range(student_name);

    std::cout << "\nGrades for " << student_name << ":" << std::endl;
    for (auto it = range.first; it != range.second; ++it) {
        std::cout << it->second << std::endl;
    }

    return 0;
}
