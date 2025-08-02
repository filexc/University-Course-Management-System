//
//  UniversitySystem.cpp
//  University Course Management System
//
//  Created by Violet Chaffee on 7/30/25.
//

#include "UniversitySystem.h"
#include <iostream>
#include <sstream>
#include <fstream>


using namespace std;

/**
 @brief constructs an ActivityLogEntry with the specified details
 
 @details initializes an activity log entry to track system operations like adding or removing students/courses
 
 @param time the timestamp of the activity
 @param a the action taken
 @param ID the student ID involved in the action
 @param cc the course code involved in the action
 @param d additional details about the action
 */
ActivityLogEntry::ActivityLogEntry(const string& time, const string& a, const string& ID, const string& cc, const string& d) {
    timestamp = time;
    action = a;
    studentID = ID;
    courseCode = cc;
    details = d;
}

/**
 @brief constructs a UniversitySystem object
*/
UniversitySystem::UniversitySystem() {}

/**
 @brief returns the current system time as a formatted string
 
 @details uses the system clock to generate a timestamp in the format YYYY-MM-DD HH:MM:SS
 
 @return (string) the current timestamp
 */
string UniversitySystem::getCurrentTimestamp() const {
    auto now = time(nullptr);
    auto tm = *localtime(&now);
    ostringstream oss;
    oss << put_time(&tm, "%Y-%m-%d %H:&M:%S");
    return oss.str();
}

/**
 @brief logs a system activity
 
 @details creates an ActivityLogEntry and adds it to the log
 
 @param action the type of activity performed
 @param studentID the student involved with the activity
 @param courseCode the course involved with the activity
 @param details extra details about the activity
 */
void UniversitySystem::logActivity(const string& action, const string& studentID, const string& courseCode, const string& details) {
    string timestamp = getCurrentTimestamp();
    activityLog.emplace_back(timestamp, action, studentID, courseCode, details);
}

/**
 @brief adds a new student to the system
 
 @details fails if the student ID or name is empty or the student ID already exists
 
 @param studentID the unique ID of the student
 @param fullName the full name of the student
 
 @return (bool) true if added successfully, false otherwise
 */
bool UniversitySystem::addStudent(const string& studentID, const string& fullName) {
    if (studentID.empty() || fullName.empty()) {
        cout << "one of the fields is blank -- cannot add a new student" << endl;
        return false;
    }
    
    if (students.find(studentID) != students.end()){
        cout << "student already exists" << endl;
        return false;
    }
    
    students[studentID] = Student(studentID, fullName);
    logActivity("ADD STUDENT", studentID, "", "Added student: " + fullName);
    return true;
}

/**
 @brief removes a student from the system
 
 @details also removes the student from any enrolled courses
 
 @param studentID the ID of the student to remove
 
 @return (bool) true if successfully removed, false if student not found
 */
bool UniversitySystem::removeStudent(const string& studentID) {
    auto iter = students.find(studentID);
    if (iter == students.end()) {
        cout << "student doesn't exist -- can't remove" << endl;
        return false;
    }
    
    Student& student = iter->second;
    set<string> enrolledCourses = student.getEnrolledCourses();
    for (const auto& courseCode : enrolledCourses) {
        auto courseIter = courses.find(courseCode);
        if (courseIter != courses.end()) {
            courseIter->second.dropStudent(studentID);
        }
    }
    
    string studentName = student.getFullName();
    students.erase(iter);
    logActivity("REMOVE STUDENT", studentID, "", "Removed student: " + studentName);
    return true;
}

/**
 @brief updates a student's name
 
 @details if the student ID is valid, the name is updated
 
 @param studentID the ID of the student
 @param newName the new name to set for the student
 
 @return (bool) true if updated, false otherwise
 */
bool UniversitySystem::updateStudent(const string& studentID, const string& newName) {
    auto iter = students.find(studentID);
    if (iter == students.end()) {
        cout << "student doesn't exist -- can't update" << endl;
        return false;
    }
    
    string oldName = iter->second.getFullName();
    iter->second.setFullName(newName);
    logActivity("UPDATE STUDENT", studentID, "", "Updated name from " + oldName + " to " + newName);
    return true;
}

/**
 @brief returns a pointer to the student object
 
 @param studentID the ID of the student
 
 @return (Student*) pointer to the student object or null pointer if not found
 */
Student* UniversitySystem::getStudent(const string& studentID) {
    auto iter = students.find(studentID);
    return (iter != students.end()) ? &(iter->second) : nullptr;
}

/**
 @brief checks if a student exists
 
 @param studentID the ID of the student
 
 @return (bool) true if the student exists, false otherwise
 */
bool UniversitySystem::studentExists(const string& studentID) const {
    return students.find(studentID) != students.end();
}

/**
 @brief adds a course to the system
 
 @details validates that required fields are not empty and the course code does not already exist
 
 @param courseCode the unique code for the course
 @param title the title of the course
 @param instructor the name of the instructor
 @param capacity the maximum number of students allowed in the course
 
 @return (bool) true if added successfully, false otherwise
 */
bool UniversitySystem::addCourse(const string& courseCode, const string& title, const string& instructor, int capacity) {
    if (courseCode.empty() || title.empty() || instructor.empty()) {
        cout << "cannot create a course, at least one field was blank" << endl;
        return false;
    }
    
    if (courses.find(courseCode) != courses.end()) {
        cout << "course already exists" << endl;
        return false;
    }
    
    courses[courseCode] = Course(courseCode, title, instructor, capacity);
    logActivity("ADD COURSE", "", courseCode, "Added course: " + title + " by " + instructor);
    return true;
}

/**
 @brief removes a course from the system
 
 @details also drops all enrolled students from the course
 
 @param courseCode the code of the course to remove
 
 @return (bool) true if removed successfully, false otherwise
 */
bool UniversitySystem::removeCourse(const string& courseCode) {
    auto iter = courses.find(courseCode);
    if (iter == courses.end()) {
        cout << "course doesn't exist, can't remove" << endl;
        return false;
    }
    
    Course& course = iter->second;
    set<string> enrolledStudents = course.getEnrolledStudents();
    for (const auto& studentID : enrolledStudents) {
        auto studentIter = students.find(studentID);
        if (studentIter != students.end()) {
            studentIter->second.dropCourse(courseCode);
        }
    }
    
    string courseTitle = course.getTitle();
    courses.erase(iter);
    logActivity("REMOVE COURSE", "", courseCode, "Removed course: " + courseTitle);
    return true;
}

/**
 @brief updates course information
 
 @details fields are updated only if non-empty (for strings) or positive (for capacity)
 
 @param courseCode the code of the course to update
 @param newTitle the new title of the course (optional)
 @param newInstructor the new instructor's name (optional)
 @param newCapacity the new course capacity (optional)
 
 @return (bool) true if course exists and is updated, false otherwise
 */
bool UniversitySystem::updateCourse(const string& courseCode, const string& newTitle, const string& newInstructor, int newCapacity) {
    auto iter = courses.find(courseCode);
    if (iter == courses.end()) {
        cout << "course doesn't exist -- can't update" << endl;
        return false;
    }
    
    Course& course = iter->second;
    string oldTitle = course.getTitle();
    
    if (!newTitle.empty()) {
        course.setTitle(newTitle);
    }
    
    if (!newInstructor.empty()) {
        course.setInstructorName(newInstructor);
    }
    
    if (newCapacity > 0) {
        course.setCapacity(newCapacity);
    }
    
    logActivity("UPDATE COURSE", "", courseCode, "Updated course from " + oldTitle + " to " + course.getTitle());
    return true;
}

/**
 @brief returns a pointer to a Course object
 
 @param courseCode the course code
 
 @return (Course*) pointer to the Course object or null pointer if not found
 */
Course* UniversitySystem::getCourse(const string& courseCode) {
    auto iter = courses.find(courseCode);
    return (iter != courses.end()) ? &(iter->second) : nullptr;
}

/**
 @brief checks if a course exists
 
 @param courseCode the course code
 
 @return (bool) true if course exists, false otherwise
 */
bool UniversitySystem::courseExists(const string& courseCode) const {
    return courses.find(courseCode) != courses.end();
}

/**
 @brief enrolls a student in a course
 
 @details updates both course and student records. logs the activity
 
 @param studentID the student to enroll
 @param courseCode the course to enroll in
 
 @return (bool) true if enrolled successfully, false otherwise
 */
bool UniversitySystem::enrollStudentInCourse(const string& studentID, const string& courseCode) {
    if (!studentExists(studentID) || !courseExists(courseCode)) {
        cout << "either student or course doesn't exist -- can't enroll" << endl;
        return false;
    }
    
    Student* student = getStudent(studentID);
    Course* course = getCourse(courseCode);
    
    if (course->enrollStudent(studentID)) {
        student->enrollInCourse(courseCode);
        string details = "Enrolled " + student->getFullName() + " in " + course->getTitle();
        logActivity("ENROLL", studentID, courseCode, details);
        return true;
    }
    
    return false;
}

/**
 @brief drops a student from a course
 
 @param studentID the student to drop
 @param courseCode the course to drop from
 
 @return (bool) true if dropped successfully, false otherwise
 */
bool UniversitySystem::dropStudentFromCourse(const string& studentID, const string& courseCode) {
    if (!studentExists(studentID) || !courseExists(courseCode)) {
        cout << "either student or course doesn't exist -- can't drop" << endl;
        return false;
    }
    
    Student* student = getStudent(studentID);
    Course* course = getCourse(courseCode);
    
    if (course->dropStudent(studentID)) {
        student->dropCourse(courseCode);
        string details = "Dropped " + student->getFullName() + " from " + course->getTitle();
        logActivity("DROP", studentID, courseCode, details);
        return true;
    }
    
    return false;
}

/**
 @brief lists all courses a student is enrolled in
 
 @details displays course codes and names for a given student ID
 
 @param studentID the ID of the student
 */
void UniversitySystem::listStudentCourses(const string& studentID) const {
    auto iter = students.find(studentID);
    if (iter == students.end()) {
        cout << "student not found" << endl;
        return;
    }
    
    const Student& student = iter->second;
    cout << "\n=== Courses for " << student.getFullName() << " (ID: " << studentID << ") ===" << endl;
    student.displayEnrolledCourses();
}

/**
 @brief lists all students enrolled in a course
 
 @details includes both enrolled and waitlisted students
 
 @param courseCode the course to list students for
 */
void UniversitySystem::listCourseStudents(const string& courseCode) const {
    auto iter = courses.find(courseCode);
    if (iter == courses.end()) {
        cout << "course not found" << endl;
        return;
    }
    
    const Course& course = iter->second;
    cout << "\n=== Students for " << course.getTitle() << " (Code: " << courseCode << ") ===" << endl;
    course.displayEnrolledStudents();
    course.displayWaitlist();
}

/**
 @brief displays all students in the system
 
 @details outputs each student's ID, name, and number of enrolled courses
 */
void UniversitySystem::displayAllStudents() const {
    if (students.empty()) {
        cout << "no students in the system" << endl;
        return;
    }
    
    cout << "\n=== All Students ===" << endl;
    for (const auto& pair : students) {
        const Student& student = pair.second;
        cout << "ID: " << student.getStudentID() << " | Name: " << student.getFullName() << " | Enrolled: " << student.getEnrollmentCount() << " courses" << endl;
    }
}

/**
 @brief displays all courses in the system
 
 @details shows each course's code, title, instructor, enrollment status, and waitlist size
 */
void UniversitySystem::displayAllCourses() const {
    if (courses.empty()) {
        cout << "no courses in the system" << endl;
        return;
    }
    
    cout << "\n=== All Courses ===" << endl;
    for (const auto& pair : courses) {
        const Course& course = pair.second;
        cout << "Code: " << course.getCourseCode() << " | Title: " << course.getTitle() << " | Instructor: " << course.getInstructorName() << " | Enrollment: " << course.getCurrentEnrollment() << "/" << course.getCapacity() << " | Waitlist: " << course.getWaitlistSize() << endl;
    }
}

/**
 @brief displays all logged system activities
 
 @details includes timestamp, action tyep, student ID (if applicable), course code (if applicable), and details
 */
void UniversitySystem::displayActivityLog() const {
    if (activityLog.empty()) {
        cout << "no activities logged" << endl;
        return;
    }
    
    cout << "\n=== Activity Log ===" << endl;
    for (const auto& entry : activityLog) {
        cout << "[" << entry.timestamp << "] " << entry.action;
        if (!entry.studentID.empty()) {
            cout << " - Student: " << entry.studentID;
        }
        if (!entry.courseCode.empty()) {
            cout << " - Course: " << entry.courseCode;
        }
        cout << " - " << entry.details << endl;
    }
}

/**
 @brief displays the most recent activities from the log
 
 @details outputs the last `count` entries
 
 @param count number of recent activities to show
 */
void UniversitySystem::displayRecentActivities(int count) const {
    if (activityLog.empty()) {
        cout << "no activities logged" << endl;
        return;
    }
    
    cout << "\n=== Recent Activities (Last " << count << ") ===" << endl;
    int start = max(0, static_cast<int>(activityLog.size()) - count);
    for (int i = start; i < activityLog.size(); i++) {
        const auto& entry = activityLog[i];
        cout << "[" << entry.timestamp << "] " << entry.action;
        if (!entry.studentID.empty()) {
            cout << " - Student: " << entry.studentID;
        }
        if (!entry.courseCode.empty()) {
            cout << " - Course: " << entry.courseCode;
        }
        cout << " - " << entry.details << endl;
    }
}

/**
 @brief searches for a student by full name
 
 @param name the name to search
 
 @return (pair<bool, string>) (true, studentID) if found, (false, "") otherwise
 */
pair<bool, string> UniversitySystem::searchStudentByName(const string& name) const {
    for (const auto& pair : students) {
        if (pair.second.getFullName() == name) {
            return make_pair(true, pair.first);
        }
    }
    return make_pair(false, "");
}

/**
 @brief searches for a course by title
 
 @param title the title to search
 
 @return (pair<bool, string>) (true, courseCode) if found, (false, "") otherwise
 */
pair<bool, string> UniversitySystem::searchCourseByTitle(const string& title) const {
    for (const auto& pair : courses) {
        if (pair.second.getTitle() == title) {
            return make_pair(true, pair.first);
        }
    }
    return make_pair(false, "");
}

/**
 @brief returns all students taught by a specific instructor
 
 @param instructor the instructor name to filter by
 
 @return (map<string, string>) of student IDs to names for students taught by the instructor
 */
map<string, string> UniversitySystem::getStudentsByInstructor(const string& instructor) const {
    map<string, string> result;
    
    for (const auto& coursePair : courses) {
        if (coursePair.second.getInstructorName() == instructor) {
            set<string> enrolledStudents = coursePair.second.getEnrolledStudents();
            for (const auto& studentID : enrolledStudents) {
                auto studentIter = students.find(studentID);
                if (studentIter != students.end()) {
                    result[studentID] = studentIter->second.getFullName();
                }
            }
        }
    }
    
    return result;
}

/**
 @brief returns the total number of students in the system
 
 @return (int) total number of students
 */
int UniversitySystem::getTotalStudents() const {
    return students.size();
}

/**
 @brief returns the total number of courses in the system
 
 @return (int) total number of courses
 */
int UniversitySystem::getTotalCourses() const {
    return courses.size();
}

/**
 @brief returns the total number of student-course enrollments
 
 @return (int) total enrollments across all students
 */
int UniversitySystem::getTotalEnrollments() const {
    int total = 0;
    for (const auto& pair : students) {
        total += pair.second.getEnrollmentCount();
    }
    return total;
}

/**
 @brief displays system-wide statistics
 
 @details includes total students, courses, enrollments, and average enrollment per course
 */
void UniversitySystem::displaySystemStatistics() const {
    cout << "\n=== System Statistics ===" << endl;
    cout << "Total Students: " << getTotalStudents() << endl;
    cout << "Total Courses: " << getTotalCourses() << endl;
    cout << "Total Enrollments: " << getTotalEnrollments() << endl;
    cout << "Total Activities Logged: " << activityLog.size() << endl;
    
    if (getTotalCourses() > 0) {
        double avgEnrollments = static_cast<double>(getTotalEnrollments()) / getTotalCourses();
        cout << "Average Enrollments per Course: " << fixed << setprecision(2) << avgEnrollments << endl;
    }
}

/**
 @brief loads student, course, and enrollment data from a file
 
 @details parses a CSV-style filie and updates system state accordingly. lines must begin with STUDENT, COURSE, or ENROLL
 
 @param fileName path to the file to load
 
 @return (bool) true if loading succeeds, false otherwise
 */
bool UniversitySystem::loadFromFile(const string& fileName) {
    ifstream file(fileName);
        if (!file.is_open()) {
            cout << "Error: Could not open file " << fileName << endl;
            return false;
        }
        
        string line;
        int lineNumber = 0;
        int studentsLoaded = 0;
        int coursesLoaded = 0;
        int enrollmentsLoaded = 0;
        
    cout << "Loading data from " << fileName << "..." << endl;
        
        while (getline(file, line)) {
            lineNumber++;
            
            // Skip empty lines and comments
            if (line.empty() || line[0] == '#') {
                continue;
            }
            
            // Parse the line
            stringstream ss(line);
            string command;
            getline(ss, command, ',');
            
            if (command == "STUDENT") {
                string studentID, fullName;
                getline(ss, studentID, ',');
                getline(ss, fullName);
                
                if (addStudent(studentID, fullName)) {
                    studentsLoaded++;
                } else {
                    cout << "Warning: Could not add student " << studentID << " (line " << lineNumber << ")" << endl;
                }
            }
            else if (command == "COURSE") {
                string courseCode, title, instructor, capacityStr;
                getline(ss, courseCode, ',');
                getline(ss, title, ',');
                getline(ss, instructor, ',');
                getline(ss, capacityStr);
                
                int capacity = 30; // default capacity
                if (!capacityStr.empty()) {
                    try {
                        capacity = stoi(capacityStr);
                    } catch (const exception& e) {
                        cout << "Warning: Invalid capacity for course " << courseCode << ", using default 30 (line " << lineNumber << ")" << endl;
                    }
                }
                
                if (addCourse(courseCode, title, instructor, capacity)) {
                    coursesLoaded++;
                } else {
                    cout << "Warning: Could not add course " << courseCode << " (line " << lineNumber << ")" << endl;
                }
            }
            else if (command == "ENROLL") {
                string studentID, courseCode;
                getline(ss, studentID, ',');
                getline(ss, courseCode);
                
                if (enrollStudentInCourse(studentID, courseCode)) {
                    enrollmentsLoaded++;
                } else {
                    cout << "Warning: Could not enroll student " << studentID << " in course " << courseCode << " (line " << lineNumber << ")" << endl;
                }
            }
            else {
                cout << "Warning: Unknown command '" << command << "' on line " << lineNumber << endl;
            }
        }
        
        file.close();
        
        cout << "Load complete:" << endl;
        cout << "  Students loaded: " << studentsLoaded << endl;
        cout << "  Courses loaded: " << coursesLoaded << endl;
        cout << "  Enrollments loaded: " << enrollmentsLoaded << endl;
        
        logActivity("LOAD_FILE", "", "", "Loaded " + to_string(studentsLoaded) + " students, " +
                    to_string(coursesLoaded) + " courses, " + to_string(enrollmentsLoaded) + " enrollments from " + fileName);
        
        return true;
}
