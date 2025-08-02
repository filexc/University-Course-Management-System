//
//  UniversitySystem.h
//  University Course Management System
//
//  Created by Violet Chaffee on 7/30/25.
//

#ifndef UNIVERSITY_SYSTEM_H
#define UNIVERSITY_SYSTEM_H

#include "Student.h"
#include "Course.h"
#include <string>
#include <map>
#include <utility>

using namespace std;

struct ActivityLogEntry {
    string timestamp;
    string action;
    string studentID;
    string courseCode;
    string details;
    
    ActivityLogEntry(const string& time, const string& a, const string& ID, const string& cc, const string& d);
};

class UniversitySystem {
private:
    map<string, Student> students;
    map<string, Course> courses;
    deque<ActivityLogEntry> activityLog;
    
    string getCurrentTimestamp() const;
    Student* getStudent(const string& studentID);
    Course* getCourse(const string& courseCode);
    int getTotalStudents() const;
    int getTotalCourses() const;
    int getTotalEnrollments() const;
    
    void logActivity(const string& action, const string& studentID, const string& courseCode, const string& details);
    bool studentExists(const string& studentID) const;
    bool courseExists(const string& courseCode) const;
    
public:
    UniversitySystem();
    
    bool addStudent(const string& studentID, const string& fullName);
    bool removeStudent(const string& studentID);
    bool updateStudent(const string& studentID, const string& newName);
        
    bool addCourse(const string& courseCode, const string& title, const string& instructor, int capacity = 30);
    bool removeCourse(const string& courseCode);
    bool updateCourse(const string& courseCode, const string& newTitle, const string& newInstructor, int newCapacity = -1);
    
    bool enrollStudentInCourse(const string& studentID, const string& courseCode);
    bool dropStudentFromCourse(const string& studentID, const string& courseCode);
    
    void listStudentCourses(const string& studentID) const;
    void listCourseStudents(const string& courseCode) const;
    void displayAllStudents() const;
    void displayAllCourses() const;
    void displayActivityLog() const;
    void displayRecentActivities(int count = 10) const;
    
    pair<bool, string> searchStudentByName(const string& name) const;
    pair<bool, string> searchCourseByTitle(const string& title) const;
    map<string, string> getStudentsByInstructor(const string& instructor) const;
    
    void displaySystemStatistics() const;
    
    bool loadFromFile(const string& fileName);
};

#endif // UNIVERSITY_SYSTEM_H
