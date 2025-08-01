//
//  Student.h
//  University Course Management System
//
//  Created by Violet Chaffee on 7/30/25.
//

#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <set>

using namespace std;

class Student {
private:
    string studentID;
    string fullName;
    set<string> enrolledCourses;
public:
    Student();
    Student(const string& ID, const string& name);
    
    string getStudentID() const;
    string getFullName() const;
    set<string> getEnrolledCourses() const;
    
    void setStudentID(const string& ID);
    void setFullName(const string& name);
    
    void enrollInCourse(const string& courseCode);
    void dropCourse(const string& courseCode);
    bool isEnrolledIn(const string& courseCode) const;
    
    int getEnrollmentCount() const;
    void displayInfo() const;
    void displayEnrolledCourses() const;
};

#endif // STUDENT_H

