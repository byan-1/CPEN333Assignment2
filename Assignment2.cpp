// Assignment2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CourseSignupPage.h"
#include "PaymentPage.h"
#include "CourseAdminPage.h"
#include "StudentInfoPage.h"
#include "../rt.h"
#include <cassert>

void runTests(StudentDBase* students, CourseDBase* courses) {
    //starts at no courses graded/completed, initial test should fail with a more required credits message (0 credits)
    int testId = 12345678;
    cout << "Testing initial state with no courses complete." << endl;
    assert(students->advanceYear(testId) == "Only 0 of the 12 credits necessary to advance to year 2 obtained.");
    cout << "Test 1 complete." << endl;
    cout << "Testing new message after adding a course." << endl;
    students->addCourse(testId, courses->getCourse("TEST1111", 1));
    students->updateGrade(testId, courses->getCourse("TEST1111", 1), 60, "Pass");
    assert(students->advanceYear(testId) == "Only 3 of the 12 credits necessary to advance to year 2 obtained.");
    cout << "Test 2 complete." << endl;
    cout << "Testing message stays the same after adding a failed course." << endl;
    students->addCourse(testId, courses->getCourse("TEST1115", 2));
    students->updateGrade(testId, courses->getCourse("TEST1115", 2), 40, "Fail");
    assert(students->advanceYear(testId) == "Only 3 of the 12 credits necessary to advance to year 2 obtained.");
    cout << "Test 3 complete." << endl;
    cout << "Testing case when a failed course is retaken and passed: " << endl;
    students->addCourse(testId, courses->getCourse("TEST1115", 2));
    students->updateGrade(testId, courses->getCourse("TEST1115", 2), 60, "Pass");
    assert(students->advanceYear(testId) == "Only 7 of the 12 credits necessary to advance to year 2 obtained.");
    cout << "Test 4 complete." << endl;
    cout << "Testing case where there is enough credits to advance but the second necessary course is missing: " << endl;
    students->addCourse(testId, courses->getCourse("TEST1115", 2));
    students->updateGrade(testId, courses->getCourse("TEST1115", 2), 60, "Pass");
    students->addCourse(testId, courses->getCourse("TEST1116", 2));
    students->updateGrade(testId, courses->getCourse("TEST1116", 2), 60, "Pass");
    students->addCourse(testId, courses->getCourse("TEST1117", 2));
    students->updateGrade(testId, courses->getCourse("TEST1117", 2), 60, "Pass");
    assert(students->advanceYear(testId) == "The student has yet to complete the following courses necessary for advancement: TEST1112");
    cout << "Test 5 complete." << endl;
    cout << "Testing successful case where both the credits necessary have been acquired and the required courses have been completed: " << endl;
    students->addCourse(testId, courses->getCourse("TEST1112", 2));
    students->updateGrade(testId, courses->getCourse("TEST1112", 2), 60, "Pass");
    assert(students->advanceYear(testId) == "Year successfully advanced.");
    cout << "Test 6 complete." << endl;
    cout << "Testing case where both required courses have been completed but the necessary credits have NOT been acquired: " << endl;
    students->removeGrade(testId, courses->getCourse("TEST1115", 2));
    students->removeGrade(testId, courses->getCourse("TEST1116", 2));
    students->removeGrade(testId, courses->getCourse("TEST1117", 2));
    assert(students->advanceYear(testId) == "Only 9 of the 12 credits necessary to advance to year 2 obtained.");
    cout << "Test 7 complete." << endl;
    cout << "Testing case where there is enough course credits but neither required courses are complete: " << endl;
    students->updateGrade(testId, courses->getCourse("TEST1115", 2), 60, "Pass");
    students->updateGrade(testId, courses->getCourse("TEST1116", 2), 60, "Pass");
    students->updateGrade(testId, courses->getCourse("TEST1117", 2), 60, "Pass");
    students->removeGrade(testId, courses->getCourse("TEST1111", 1));
    students->removeGrade(testId, courses->getCourse("TEST1112", 2));
    assert(students->advanceYear(testId) == "The student has yet to complete the following courses necessary for advancement: TEST1111 TEST1112");
    cout << "Test 8 complete. " << endl;
    cout << "Testing case where there is enough course credits but the first required course is missing: " << endl;
    students->updateGrade(testId, courses->getCourse("TEST1112", 2), 60, "Pass");
    assert(students->advanceYear(testId) == "The student has yet to complete the following courses necessary for advancement: TEST1111");
    cout << "Test 9 complete." << endl;
    cout << "Testing case where a course is removed in a term that the student is not signed up in (result should NOT change from last test): ";
    students->removeGrade(testId, courses->getCourse("TEST1111", 2));
    assert(students->advanceYear(testId) == "The student has yet to complete the following courses necessary for advancement: TEST1111");
    cout << "Test 10 complete." << endl;
}

void printWelcomeMsg() {
    cout << "-------------------------------------------------------" << endl;
    cout << "Welcome to the landing page." << endl;
    cout << "Enter 'c' to navigate to the course signup page, 'p' for the course payment page, 's' for the student info page, or 'a' for the course admin page." << endl;
}

int main()
{
    bool isRunning = true;
    char curInput;
    CourseDBase* courses = new CourseDBase();
    StudentDBase* students = new StudentDBase();
    FacultyDBase* faculty = new FacultyDBase();
    ProfessorDBase* professors = new ProfessorDBase();
    CourseSignupPage courseSignup(students, courses, faculty);
    PaymentPage payment(students);
    CourseAdminPage courseAdmin(professors, courses, faculty, students);
    StudentInfoPage studentInfo(professors, courses, faculty, students);
    printWelcomeMsg();
    while (isRunning) {
        curInput = _getch();
        if (curInput == 'c') {
            courseSignup.run();
            courseSignup.signout();
            printWelcomeMsg();
        }
        else if (curInput == 'p') {
            payment.run();
            payment.signout();
            printWelcomeMsg();
        }
        else if (curInput == 'a') {
            courseAdmin.run();
            courseAdmin.signout();
            printWelcomeMsg();
        }
        else if (curInput == 's') {
            studentInfo.run();
            studentInfo.signout();
            printWelcomeMsg();
        }
        else if (curInput == 'd') {
            runTests(students, courses);
        }
        else {
            cout << "Invalid input" << endl;
        }
    }
}
