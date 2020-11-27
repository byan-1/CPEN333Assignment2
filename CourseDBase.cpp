#include "CourseDBase.h"

string CourseDBase::validateSignup(string courseId, int term)
{
    if (!courseStorage.count(courseId)) {
        return "Course " + courseId + " does not exist.";
    }
    if (!courseStorage[courseId].count(term)) {
        return "Course " + courseId + " is not offered in this term.";
    }
    CourseData c = courseStorage[courseId][term];
    if (c.currentlyRegistered >= c.maxCapacity) {
        return "Course " + courseId + " is full.";
    }
    return "";
}

void CourseDBase::addSignUp(int sId, CourseData& c)
{
    courseStorage[c.courseCode][c.term].currentlyRegistered += 1;
    c.studentIDs.push_back(sId);
}

void CourseDBase::resetCriteria(const CourseData& c) {
    courseStorage[c.courseCode][c.term].assessment = {};
}

void CourseDBase::updateCriteria(const CourseData& c, string type, string percent, string mustPass) {
    bool pass = false;
    //input is sanitized to only be "yes" or "no" before being passed in
    if (mustPass == "yes") {
        pass = true;
    }
    courseStorage[c.courseCode][c.term].assessment[type] = {stoi(percent), pass};
}