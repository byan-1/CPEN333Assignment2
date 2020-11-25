#pragma once
#include "Page.h"
#include "ProfessorDBase.h"
#include "CourseDBase.h"
#include "FacultyDBase.h"
class CourseAdminPage :
    public Page
{
public:
    CourseAdminPage(ProfessorDBase* p, CourseDBase* c, FacultyDBase* f, StudentDBase* s) : professors(p), courses(c), faculty(f), students(s), curUserId() {};
    void login(string id, string password);
    void run();
    static vector<string> splitString(string input);
    string validateCourseInput(vector<string> inputs);
    string validateUpdateInput(vector<string> inputs);
    void signout() { curUserId = 0; };
    static bool isValidId(const string& id);
    bool isValidGrade(const string& id);
private:
    int curUserId;
    ProfessorDBase* professors;
    CourseDBase* courses;
    FacultyDBase* faculty;
    StudentDBase* students;
};

