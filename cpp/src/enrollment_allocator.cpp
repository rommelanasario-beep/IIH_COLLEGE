#include <algorithm>
#include <string>
#include <vector>

struct Applicant {
    std::string name;
    int score;
    std::string course;
};

std::vector<Applicant> allocateEnrollmentSlots(
    std::vector<Applicant> applicants,
    int seats
) {
    std::sort(
        applicants.begin(),
        applicants.end(),
        [](const Applicant& a,
           const Applicant& b) {
            return a.score > b.score;
        }
    );

    if (seats < 0)
        seats = 0;

    if (seats < static_cast<int>(applicants.size()))
        applicants.resize(seats);

    return applicants;
}
