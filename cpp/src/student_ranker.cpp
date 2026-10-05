#include <string>
#include <vector>

struct RankedStudent {
    std::string name;
    double average;
};

void mergeStudents(
    std::vector<RankedStudent>& students,
    int left,
    int mid,
    int right
) {
    std::vector<RankedStudent> temp;

    int i = left;
    int j = mid + 1;

    while (i <= mid && j <= right) {
        if (students[i].average >= students[j].average)
            temp.push_back(students[i++]);
        else
            temp.push_back(students[j++]);
    }

    while (i <= mid)
        temp.push_back(students[i++]);

    while (j <= right)
        temp.push_back(students[j++]);

    for (int k = 0; k < static_cast<int>(temp.size()); ++k)
        students[left + k] = temp[k];
}

void mergeSortStudents(
    std::vector<RankedStudent>& students,
    int left,
    int right
) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    mergeSortStudents(students, left, mid);
    mergeSortStudents(students, mid + 1, right);

    mergeStudents(students, left, mid, right);
}

void rankStudents(
    std::vector<RankedStudent>& students
) {
    if (students.empty())
        return;

    mergeSortStudents(
        students,
        0,
        static_cast<int>(students.size()) - 1
    );
}
