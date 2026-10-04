// Algorithm 1: Weighted course recommendation
// Scores a student's interests against each degree program.
// Compile: g++ -std=c++17 course_recommender.cpp -o course_recommender

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

struct Course {
    std::string code;
    std::string name;
    std::vector<std::string> interests;
};

struct Result {
    Course course;
    int score;
};

int main() {
    std::vector<Course> courses = {
        {"BSCRIM", "BS Criminology", {"law", "security", "investigation", "community"}},
        {"BSTM", "BS Tourism Management", {"travel", "hospitality", "events", "people"}},
        {"BSIS", "BS Information Systems", {"technology", "programming", "business", "data"}},
        {"BSAIS", "BS Accounting Information Systems", {"accounting", "technology", "data", "business"}},
        {"BSA", "BS Accountancy", {"accounting", "finance", "audit", "business"}},
        {"BTVTED", "BTVTEd", {"teaching", "technical", "vocational", "training"}}
    };

    std::cout << "Enter 3 interests separated by spaces (example: technology data business): ";
    std::vector<std::string> wanted(3);
    for (auto &word : wanted) std::cin >> word;

    std::vector<Result> results;
    for (const auto &course : courses) {
        int score = 0;
        for (const auto &wantedInterest : wanted) {
            if (std::find(course.interests.begin(), course.interests.end(), wantedInterest)
                != course.interests.end()) {
                score += 10;
            }
        }
        results.push_back({course, score});
    }

    std::sort(results.begin(), results.end(),
              [](const Result &a, const Result &b) { return a.score > b.score; });

    std::cout << "\nRecommended courses:\n";
    for (const auto &r : results) {
        std::cout << std::left << std::setw(8) << r.course.code
                  << " " << std::setw(35) << r.course.name
                  << " score=" << r.score << '\n';
    }
}
