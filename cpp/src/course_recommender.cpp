#include <algorithm>
#include <string>
#include <vector>

struct Recommendation {
    std::string code;
    std::string name;
    int score;
};

std::vector<Recommendation> recommendCourses(
    const std::vector<std::string>& wanted
) {
    struct Course {
        std::string code;
        std::string name;
        std::vector<std::string> interests;
    };

    const std::vector<Course> courses = {
        {"BSCRIM", "BS Criminology",
         {"law", "security", "investigation", "community"}},

        {"BSTM", "BS Tourism Management",
         {"travel", "hospitality", "events", "people"}},

        {"BSIS", "BS Information Systems",
         {"technology", "programming", "business", "data"}},

        {"BSAIS", "BS Accounting Information Systems",
         {"accounting", "technology", "data", "business"}},

        {"BSA", "BS Accountancy",
         {"accounting", "finance", "audit", "business"}},

        {"BTVTED", "BTVTEd",
         {"teaching", "technical", "vocational", "training"}}
    };

    std::vector<Recommendation> results;

    for (const auto& course : courses) {
        int score = 0;

        for (const auto& interest : wanted) {
            if (std::find(
                    course.interests.begin(),
                    course.interests.end(),
                    interest
                ) != course.interests.end()) {
                score += 10;
            }
        }

        results.push_back({
            course.code,
            course.name,
            score
        });
    }

    std::sort(
        results.begin(),
        results.end(),
        [](const Recommendation& a,
           const Recommendation& b) {
            return a.score > b.score;
        }
    );

    return results;
}
