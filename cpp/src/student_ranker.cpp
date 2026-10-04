// Algorithm 2: Merge sort for student ranking
// Demonstrates a classic O(n log n) sorting algorithm.

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

struct Student {
    std::string name;
    double average;
};

void merge(std::vector<Student>& a, int left, int mid, int right) {
    std::vector<Student> temp;
    int i = left, j = mid + 1;

    while (i <= mid && j <= right) {
        if (a[i].average >= a[j].average) temp.push_back(a[i++]);
        else temp.push_back(a[j++]);
    }
    while (i <= mid) temp.push_back(a[i++]);
    while (j <= right) temp.push_back(a[j++]);

    for (int k = 0; k < static_cast<int>(temp.size()); ++k)
        a[left + k] = temp[k];
}

void mergeSort(std::vector<Student>& a, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(a, left, mid);
    mergeSort(a, mid + 1, right);
    merge(a, left, mid, right);
}

int main() {
    std::vector<Student> students = {
        {"Student A", 1.25},
        {"Student B", 1.75},
        {"Student C", 1.10},
        {"Student D", 2.00},
        {"Student E", 1.50}
    };

    mergeSort(students, 0, static_cast<int>(students.size()) - 1);

    std::cout << "Student ranking (lower GPA is better in this example):\n";
    for (size_t i = 0; i < students.size(); ++i) {
        std::cout << i + 1 << ". " << std::left << std::setw(15)
                  << students[i].name << " GPA: " << students[i].average << '\n';
    }
}
