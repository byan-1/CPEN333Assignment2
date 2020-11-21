#pragma once
#include "DBase.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <iomanip>
#include <iostream>
using namespace std;

struct CourseData {
	CourseData() {};
	CourseData(const CourseData&) = default;
	CourseData(string n, string c, int t, int cr, float f, float i_f, int mc) : name(n), courseCode(c), term(t), credits(cr), fee(f), internationalFee(i_f), prerequisites{}, corequisites{}, currentlyRegistered(0), maxCapacity(mc), assessment{} {};
	unordered_map < string, pair<int, string>> courseGrades;
	string name;
	string courseCode;
	int term;
	int credits;
	//ID of professor(s) teaching the course during the term
	vector<int> professorIDs;
	//ID of students taking the course
	vector<int> studentIDs;
	unordered_map<string, pair<int, bool>> assessment;
	vector<string> prerequisites;
	vector<string> corequisites;
	float fee;
	float internationalFee;
	int currentlyRegistered;
	int maxCapacity;
	void printAssessment() const {
		cout << "Assessment Criteria: " << endl;
		for (auto& p : assessment) {
			cout << p.first + ": " << p.second.first << "%";
			if (p.second.second) cout << " (Must pass to pass the course)";
			cout << endl;
		}
	}
	void printInstructors() const {
		cout << "Instructors: ";
		for (int i = 0; i < professorIDs.size(); i++) {
			if (i != professorIDs.size() - 1)
				cout << to_string(professorIDs[i]) + ", ";
			else
				cout << to_string(professorIDs[i]);
		}
		cout << endl;
	}
	void printCoreqs() const {
		if (corequisites.size()) {
			cout << "Corequisites: ";
			for (int i = 0; i < corequisites.size(); i++) {
				if (i != corequisites.size() - 1)
					cout << corequisites[i] + ", ";
				else
					cout << corequisites[i];
			}
			cout << endl;
		}
	}
	void printPrereqs() const {
		if (prerequisites.size()) {
			cout << "Prerequisites: ";
			for (int i = 0; i < prerequisites.size(); i++) {
				if (i != prerequisites.size() - 1)
					cout << prerequisites[i] + ", ";
				else
					cout << prerequisites[i];
			}
			cout << endl;
		}
	}
	void printFees() const {
		//print in 2 decimal places;
		cout << fixed << setprecision(2) << "Fees (Domestic): $" << fee << endl;
		cout << fixed << setprecision(2) << "Fees (International): $" << internationalFee << endl;
	}
	void printCapacity() const {
		cout << "Currently Registered: " + to_string(currentlyRegistered) + " / " + to_string(maxCapacity) << endl;
	}
};

class CourseDBase : public DBase
{
public:
	CourseDBase(): courseStorage{
		{"TEST1111", unordered_map<int, CourseData>{ {1, CourseData("TestCourse1", "TEST1111", 1, 3, 1500, 3000, 500)} } },
		{"TEST1112", unordered_map<int, CourseData>{ {2, CourseData("TestCourse2", "TEST1112", 2, 3, 1500, 3000, 200)} } },
		{"TEST1113", unordered_map<int, CourseData>{ {2, CourseData("TestCourse3", "TEST1113", 2, 3, 1500, 3000, 100)} } },
		{"TEST1114", unordered_map<int, CourseData>{ {3, CourseData("TestCourse4", "TEST1114", 3, 3, 1500, 3000, 50)} } },
		{"TEST1115", unordered_map<int, CourseData>{ {2, CourseData("TestCourse5", "TEST1115", 2, 4, 1500, 3000, 50)} } },
		{"TEST1116", unordered_map<int, CourseData>{ {2, CourseData("TestCourse6", "TEST1116", 2, 4, 1500, 3000, 50)} } },
		{"TEST1117", unordered_map<int, CourseData>{ {2, CourseData("TestCourse7", "TEST1117", 2, 4, 1500, 3000, 50)} } }
	} {
		courseStorage["TEST1112"][2].prerequisites.push_back("TEST1111");
		courseStorage["TEST1113"][2].prerequisites.push_back("TEST1111");
		courseStorage["TEST1113"][2].corequisites.push_back("TEST1112");
		courseStorage["TEST1114"][3].corequisites.push_back("TEST1113");
	};

	bool courseExists(string courseCode, int term) {
		if (!courseStorage.count(courseCode)) {
			return false;
		}
		return courseStorage[courseCode].count(term);
	}
	CourseData getCourse(string courseCode, int term) {
		return courseStorage[courseCode][term];
	}
	string validateSignup(string courseId, int term);
	void addSignUp(int sId, CourseData& c);
	void addProfessor(int professorId, const CourseData& course) { courseStorage[course.courseCode][course.term].professorIDs.push_back(professorId); };
	void updateCriteria(const CourseData& c, string type, string mark, string mustPass);
	void resetCriteria(const CourseData& c);
	unordered_map<string, pair<int, bool>> getCriteria(int sid, const CourseData& course) { return courseStorage[course.courseCode][course.term].assessment; };
	void updateGrade(const CourseData& course, int percent, string grade) { courseStorage[course.courseCode][course.term].courseGrades[course.courseCode] = { percent, grade }; };
private:
	//key is course code, value is another key value pair with the term as the key and the data as the value to allow for the same course being offered on different terms
	unordered_map<string, unordered_map<int, CourseData>> courseStorage;
};

