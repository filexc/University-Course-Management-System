//
//  Course.h
//  University Course Management System
//
//  Created by Violet Chaffee on 7/30/25.
//

#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <set>
#include <queue>

using namespace std;

class Course {
private:
    string courseCode;
    string title;
    string instructorName;
    set<string> enrolledStudents;
    queue<string> waitlist;
    int capacity;
    int currentEnrollment;
public:
    Course();
    Course(const string& code, const string& courseTitle, const string& instructor, int maxCapacity = 30);
    
    string getCourseCode() const;
    string getTitle() const;
    string getInstructorName() const;
    set<string> getEnrolledStudents() const;
    int getCapacity() const;
    int getCurrentEnrollment() const;
    int getWaitlistSize() const;
    
    void setCourseCode(const string& code);
    void setTitle(const string& courseTitle);
    void setInstructorName(const string& instructor);
    void setCapacity(int maxCapacity);
    
    bool enrollStudent(const string& studentID);
    bool dropStudent(const string& studentID);
    bool isStudentEnrolled(const string& studentID) const;
    bool addToWaitlist(const string& studentID);
    string removeFromWaitlist();
    
    bool isFull() const;
    bool hasAvailableSeats() const;
    void displayInfo() const;
    void displayEnrolledStudents() const;
    void displayWaitlist() const;
};

#endif // COURSE_H
