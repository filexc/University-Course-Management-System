//
//  main.cpp
//  University Course Management System
//
//  Created by Violet Chaffee on 7/30/25.
//

#include "UniversitySystem.h"
#include <iostream>

using namespace std;

/**
 @brief displays the main menu options to the user
 
 @details prints a numbered list of available actions in the University Course Management system
 */
void displayMenu() {
    cout << "\n=== University Course Management System ===" << endl;
    cout << "1. Add Student" << endl;
    cout << "2. Add Course" << endl;
    cout << "3. Enroll Student in Course" << endl;
    cout << "4. Drop Student from Course" << endl;
    cout << "5. List Student's Courses" << endl;
    cout << "6. List Course's Student" << endl;
    cout << "7. Display All Students" << endl;
    cout << "8. Display All Courses" << endl;
    cout << "9. Search Student by Name" << endl;
    cout << "10. Search Course by Title" << endl;
    cout << "11. Get Students by Instructor" << endl;
    cout << "12. Display System Statistics" << endl;
    cout << "13. Display Activity Log" << endl;
    cout << "14. Display Recent Activities" << endl;
    cout << "15. Remove Student" << endl;
    cout << "16. Remove Course" << endl;
    cout << "17. Update Student" << endl;
    cout << "18. Update Course" << endl;
    cout << "19. Load Data from File" << endl;
    cout << "20. Demo Mode (Run all features)" << endl;
    cout << "21.  Exit" << endl;
    cout << "Enter your choice: ";
}

/**
 @brief clears invalid input from the input buffer

 @details useful when a user enters non-integer input when an integer is expected
 */
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

/**
 @brief gets a string input from the user
 
 @details prompts the user with a given message and reads and entire line of input
 
 @param prompt the message displayed to prompt the user for input
 
 @return (string) the user's input
 */
string getStringInput(const string& prompt) {
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

/**
 @brief gets an integer input from the user
 
 @details prompts the user with a given message until the user enters a valid integer
 
 @param prompt the message displayed to prompt the user for input
 
 @return (int) the user's input
 */
int getIntInput(const string& prompt) {
    int input;
    cout << prompt;
    while (!(cin >> input)) {
        cout << "Invalid input. Please enter a number: ";
        clearInput();
    }
    clearInput();
    return input;
}

/**
 @brief runs a demonstration of system features
 
 @details add demo students and courses, enrolls them, tests edge cases like waitlists, performs searches, and displays data
 
 @param system the reference to the UniversitySystem object being used
 */
void demoMode(UniversitySystem& system) {
    cout << "\n=== DEMO MODE - Testing All Features ===" << endl;
    
    // Add students
    cout << "\n1. Adding students..." << endl;
    system.addStudent("S001", "Alice Johnson");
    system.addStudent("S002", "Bob Smith");
    system.addStudent("S003", "Carol Davis");
    system.addStudent("S004", "David Wilson");
    system.addStudent("S005", "Eva Brown");
    
    // Add courses
    cout << "\n2. Adding courses..." << endl;
    system.addCourse("CS101", "Introduction to Computer Science", "Dr. Smith", 25);
    system.addCourse("MATH201", "Calculus I", "Dr. Johnson", 30);
    system.addCourse("ENG101", "English Composition", "Dr. Davis", 20);
    system.addCourse("PHYS101", "Physics I", "Dr. Wilson", 15);
    system.addCourse("HIST101", "World History", "Dr. Brown", 35);
    
    // Enroll students in courses
    cout << "\n3. Enrolling students in courses..." << endl;
    system.enrollStudentInCourse("S001", "CS101");
    system.enrollStudentInCourse("S001", "MATH201");
    system.enrollStudentInCourse("S002", "CS101");
    system.enrollStudentInCourse("S002", "ENG101");
    system.enrollStudentInCourse("S003", "MATH201");
    system.enrollStudentInCourse("S003", "PHYS101");
    system.enrollStudentInCourse("S004", "HIST101");
    system.enrollStudentInCourse("S005", "CS101");
    system.enrollStudentInCourse("S005", "MATH201");
    system.enrollStudentInCourse("S005", "ENG101");
    
    // Test waitlist functionality
    cout << "\n4. Testing waitlist functionality..." << endl;
    for (int i = 6; i <= 20; ++i) {
        string studentID = "S" + string(3 - to_string(i).length(), '0') + to_string(i);
        string name = "Student" + to_string(i);
        system.addStudent(studentID, name);
        system.enrollStudentInCourse(studentID, "PHYS101"); // Small capacity course
    }
    
    // Display results
    cout << "\n5. Displaying results..." << endl;
    system.displayAllStudents();
    system.displayAllCourses();
    system.displaySystemStatistics();
    
    // Test search operations
    cout << "\n6. Testing search operations..." << endl;
    auto studentSearch = system.searchStudentByName("Alice Johnson");
    if (studentSearch.first) {
        cout << "Found student: " << studentSearch.second << endl;
    }
    
    auto courseSearch = system.searchCourseByTitle("Introduction to Computer Science");
    if (courseSearch.first) {
        cout << "Found course: " << courseSearch.second << endl;
    }
    
    // Test instructor search
    cout << "\n7. Testing instructor search..." << endl;
    auto studentsByInstructor = system.getStudentsByInstructor("Dr. Smith");
    cout << "Students taught by Dr. Smith:" << endl;
    for (const auto& pair : studentsByInstructor) {
        cout << "  " << pair.first << " - " << pair.second << endl;
    }
    
    // Test administrative tools
    cout << "\n8. Testing administrative tools..." << endl;
    system.listStudentCourses("S003");
    system.listCourseStudents("PHYS101");
    
    // Test activity log
    cout << "\n9. Testing activity log..." << endl;
    system.displayRecentActivities(10);
    
    // Test drop functionality
    cout << "\n10. Testing drop functionality..." << endl;
    system.dropStudentFromCourse("S003", "PHYS101");
    system.listStudentCourses("S003");
    
    //Test waitlist updating functionality
    cout << "\n11. Testing updated waitlist functionality..." << endl;
    system.listCourseStudents("PHYS101");
    
    cout << "\n=== DEMO COMPLETE ===" << endl;
}

/**
 @brief entry point of the application
 
 @details initializes the UniversitySystem and displays a menu loop for user interaction
 */
int main(int argc, const char * argv[]) {
    UniversitySystem system;
    int choice;
    
    do {
        displayMenu();
        choice = getIntInput("");

        switch (choice) {
            case 1: { // Add Student
                string studentID = getStringInput("Enter student ID: ");
                string name = getStringInput("Enter student name: ");
                if (system.addStudent(studentID, name)) {
                    cout << "Student added successfully!" << endl;
                } else {
                    cout << "Failed to add student. Student ID might already exist" << endl;
                }
                break;
            }
            case 2: { // Add Course
                string courseCode = getStringInput("Enter course code: ");
                string title = getStringInput("Enter course title: ");
                string instructor = getStringInput("Enter instructor name: ");
                int capacity = getIntInput("Enter course capacity: ");
                if (system.addCourse(courseCode, title, instructor, capacity)) {
                    cout << "Course added successfully!" << endl;
                } else {
                    cout << "Failed to add course. Course code might already exist" << endl;
                }
                break;
            }
            case 3: { // Enroll Student in Course
                string studentID = getStringInput("Enter student ID: ");
                string courseCode = getStringInput("Enter course code: ");
                if (system.enrollStudentInCourse(studentID, courseCode)) {
                    cout << "Student enrolled successfully!" << endl;
                } else {
                    cout << "Failed to enroll student. Check if student and course exist" << endl;
                }
                break;
            }
            case 4: { // Drop Student from Course
                string studentID = getStringInput("Enter student ID: ");
                string courseCode = getStringInput("Enter course code: ");
                if (system.dropStudentFromCourse(studentID, courseCode)) {
                    cout << "Student dropped successfully!" << endl;
                } else {
                    cout << "Failed to drop student. Check if student is enrolled in the course" << endl;
                }
                break;
            }
            case 5: { // List Student's Courses
                string studentID = getStringInput("Enter student ID: ");
                system.listStudentCourses(studentID);
                break;
            }
            case 6: { // List Course's Students
                string courseCode = getStringInput("Enter course code: ");
                system.listCourseStudents(courseCode);
                break;
            }
            case 7: { // Display All Students
                system.displayAllStudents();
                break;
            }
            case 8: { // Display All Courses
                system.displayAllCourses();
                break;
            }
            case 9: { // Search Student by Name
                string name = getStringInput("Enter student name: ");
                auto result = system.searchStudentByName(name);
                if (result.first) {
                    cout << "Student found with ID: " << result.second << endl;
                } else {
                    cout << "Student not found" << endl;
                }
                break;
            }
            case 10: { // Search Course by Title
                string title = getStringInput("Enter course title: ");
                auto result = system.searchCourseByTitle(title);
                if (result.first) {
                    cout << "Course found with code: " << result.second << endl;
                } else {
                    cout << "Course not found" << endl;
                }
                break;
            }
            case 11: { // Get Students by Instructor
                string instructor = getStringInput("Enter instructor name: ");
                auto students = system.getStudentsByInstructor(instructor);
                if (students.empty()) {
                    cout << "No students found for this instructor" << endl;
                } else {
                    cout << "Students taught by " << instructor << ":" << endl;
                    for (const auto& pair : students) {
                        cout << " " << pair.first << " - " << pair.second << endl;
                    }
                }
                break;
            }
            case 12: { // Display System Statistics
                system.displaySystemStatistics();
                break;
            }
            case 13: { // Display Activity Log
                system.displayActivityLog();
                break;
            }
            case 14: { // Display Recent Activities
                int count = getIntInput("Enter number of recent activities to display: ");
                system.displayRecentActivities(count);
                break;
            }
            case 15: { // Remove Student
                string studentID = getStringInput("Enter student ID to remove: ");
                if (system.removeStudent(studentID)) {
                    cout << "Student removed successfully!" << endl;
                } else {
                    cout << "Failed to remove student. Student not found" << endl;
                }
                break;
            }
            case 16: { // Remove Course
                string courseCode = getStringInput("Enter course code to remove: ");
                if (system.removeCourse(courseCode)) {
                    cout << "Course removed successfully!" << endl;
                } else {
                    cout << "Failed to remove course. Course not found" << endl;
                }
                break;
            }
            case 17: { // Update Student
                string studentID = getStringInput("Enter student ID: ");
                string newName = getStringInput("Enter new name: ");
                if (system.updateStudent(studentID, newName)) {
                    cout << "Student updated successfully!" << endl;
                } else {
                    cout << "Failed to update student. Student not found" << endl;
                }
                break;
            }
            case 18: { // Update Course
                string courseCode = getStringInput("Enter course code: ");
                string newTitle = getStringInput("Enter new title (or press Enter to skip): ");
                string newInstructor = getStringInput("Enter new instructor (or press Enter to skip): ");
                int newCapacity = getIntInput("Enter new capacity (or 0 to skip): ");
                if (system.updateCourse(courseCode, newTitle, newInstructor, newCapacity)) {
                    cout << "Course updated successfully!" << endl;
                } else {
                    cout << "Failed to update course. Course not found" << endl;
                }
                break;
            }
            case 19: { // Load Data from File
                string filename = getStringInput("Enter filename to load from: ");
                if (system.loadFromFile(filename)) {
                    cout << "Data loaded successfully from " << filename << endl;
                } else {
                    cout << "Failed to load data from " << filename << endl;
                }
                break;
            }
            case 20: { // Demo Mode (Run all features)
                demoMode(system);
                break;
            }
            case 21: { // Exit
                cout << "Thanks for using the University Course Management System!" << endl;
                break;
            }
            default:
                cout << "Invalid choice. Please try again" << endl;
                break;
        }
    } while (choice != 21);
    
    return 0;
}
