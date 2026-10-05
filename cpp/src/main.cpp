#include <iostream>
#include <vector>

#include "../include/student.hpp"
#include "../include/course.hpp"
#include "../include/enrollment.hpp"
#include "../include/admission.hpp"
#include "../include/dashboard.hpp"

int main() {
    std::cout << "=====================================\n";
    std::cout << "       IIH COLLEGE C++ ENGINE\n";
    std::cout << "=====================================\n";

    Student student{
        1001,
        "Demo Student",
        "demo@iihcollege.com",
        "BSIS",
        92.5
    };

    std::cout << "\nSTUDENT\n";
    std::cout << "Name: " << student.fullName << "\n";
    std::cout << "Course: " << student.course << "\n";
    std::cout << "Status: " << studentStatus(student) << "\n";

    std::cout << "\nCOURSES\n";

    const std::vector<std::string> courses = {
        "BSCRIM",
        "BSTM",
        "BSIS",
        "BSAIS",
        "BSA",
        "BTVTED"
    };

    for (const auto& course : courses) {
        std::cout << course
                  << " | Capacity: "
                  << getCourseCapacity(course)
                  << "\n";
    }

    Enrollment enrollment{
        student.id,
        student.course,
        "PENDING"
    };

    std::cout << "\nENROLLMENT\n";
    std::cout << "Student ID: " << enrollment.studentId << "\n";
    std::cout << "Course: " << enrollment.courseCode << "\n";
    std::cout << "Result: " << processEnrollment(enrollment) << "\n";

    Admission admission{
        "Demo Student",
        "demo@iihcollege.com",
        "BSIS",
        92.5
    };

    std::cout << "\nADMISSION\n";
    std::cout << "Applicant: " << admission.applicantName << "\n";
    std::cout << "Result: " << evaluateAdmission(admission) << "\n";

    DashboardStats dashboard =
        calculateDashboard(1, 1, 0, 6);

    std::cout << "\nDASHBOARD\n";
    std::cout << "Students: "
              << dashboard.totalStudents << "\n";
    std::cout << "Enrollments: "
              << dashboard.totalEnrollments << "\n";
    std::cout << "Pending Admissions: "
              << dashboard.pendingAdmissions << "\n";
    std::cout << "Available Courses: "
              << dashboard.availableCourses << "\n";

    std::cout << "\n=====================================\n";
    std::cout << "       ENGINE RUN SUCCESSFULLY\n";
    std::cout << "=====================================\n";

    return 0;
}
