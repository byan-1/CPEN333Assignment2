#pragma once
#include "Page.h"
#include <string>
#include "StudentDBase.h"

using namespace std;
class PaymentPage :
    public Page
{
public:
    PaymentPage(StudentDBase* s) : students(s), curUserId() {}
    void login(string id, string password);
    void run();
    void signout() { curUserId = 0; };
    static vector<string> splitString(string input);
    static bool isValidId(const string& id);
private:
    int curUserId;
    StudentDBase* students;
};

