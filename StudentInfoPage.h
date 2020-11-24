#pragma once
#include "Page.h"
#include <string>
#include "StudentDBase.h"
#include "CourseDBase.h"
#include "FacultyDBase.h"
#include "ProfessorDBase.h"

class StudentInfoPage :
    public Page
{
public:
    StudentInfoPage(ProfessorDBase* p, CourseDBase* c, FacultyDBase* f, StudentDBase* s) : professors(p), courses(c), faculty(f), students(s), curUserId() {};
    void login(string id, string password);
    void printStudentDetails(int studentId);
    void run();
    static vector<string> splitString(string input);
    string validateCourseInput(vector<string> inputs);
    void signout() { curUserId = 0; };
    static bool isValidId(const string& id);
private:
    int curUserId;
    StudentDBase* students;
    CourseDBase* courses;
    FacultyDBase* faculty;
    ProfessorDBase* professors;
};

