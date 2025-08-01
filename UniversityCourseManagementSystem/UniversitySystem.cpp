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

ActivityLogEntry::ActivityLogEntry(const string& time, const string& a, const string& ID, const string& cc, const string& d) {
    timestamp = time;
    action = a;
    studentID = ID;
    courseCode = cc;
    details = d;
}

UniversitySystem::UniversitySystem() {}

string UniversitySystem::getCurrentTimestamp() const {
    auto now = time(nullptr);
    auto tm = *localtime(&now);
    ostringstream oss;
    oss << put_time(&tm, "%Y-%m-%d %H:&M:%S");
    return oss.str();
}

void UniversitySystem::logActivity(const string& action, const string& studentID, const string& courseCode, const string& details) {
    string timestamp = getCurrentTimestamp();
    activityLog.emplace_back(timestamp, action, studentID, courseCode, details);
}

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

Student* UniversitySystem::getStudent(const string& studentID) {
    auto iter = students.find(studentID);
    return (iter != students.end()) ? &(iter->second) : nullptr;
}

bool UniversitySystem::studentExists(const string& studentID) const {
    return students.find(studentID) != students.end();
}

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

Course* UniversitySystem::getCourse(const string& courseCode) {
    auto iter = courses.find(courseCode);
    return (iter != courses.end()) ? &(iter->second) : nullptr;
}

bool UniversitySystem::courseExists(const string& courseCode) const {
    return courses.find(courseCode) != courses.end();
}

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

pair<bool, string> UniversitySystem::searchStudentByName(const string& name) const {
    for (const auto& pair : students) {
        if (pair.second.getFullName() == name) {
            return make_pair(true, pair.first);
        }
    }
    return make_pair(false, "");
}

pair<bool, string> UniversitySystem::searchCourseByTitle(const string& title) const {
    for (const auto& pair : courses) {
        if (pair.second.getTitle() == title) {
            return make_pair(true, pair.first);
        }
    }
    return make_pair(false, "");
}

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

int UniversitySystem::getTotalStudents() const {
    return students.size();
}

int UniversitySystem::getTotalCourses() const {
    return courses.size();
}

int UniversitySystem::getTotalEnrollments() const {
    int total = 0;
    for (const auto& pair : students) {
        total += pair.second.getEnrollmentCount();
    }
    return total;
}

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
