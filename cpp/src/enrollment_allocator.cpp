// Algorithm 3: Greedy enrollment-slot allocation
// Allocates limited seats to applicants with the highest admission score.
// This is intentionally separate from the web backend for easy demonstration.

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Applicant {
    std::string name;
    int score;
    std::string course;
};

int main() {
    std::vector<Applicant> applicants = {
        {"Alex", 92, "BSIS"},
        {"Bea", 87, "BSA"},
        {"Carl", 95, "BSCRIM"},
        {"Dana", 89, "BSTM"},
        {"Eli", 91, "BSAIS"},
        {"Faith", 84, "BTVTED"}
    };

    int seats;
    std::cout << "Number of available seats: ";
    std::cin >> seats;

    std::sort(applicants.begin(), applicants.end(),
              [](const Applicant& a, const Applicant& b) {
                  return a.score > b.score;
              });

    std::cout << "\nAllocated applicants:\n";
    for (int i = 0; i < seats && i < static_cast<int>(applicants.size()); ++i) {
        std::cout << applicants[i].name << " | "
                  << applicants[i].course << " | score "
                  << applicants[i].score << '\n';
    }
}
