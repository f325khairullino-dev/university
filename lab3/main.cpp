#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

class Subscriber {
private:
    string lastName;
    long long phoneNumber;

public:
    Subscriber() : lastName(""), phoneNumber(0) {}

    Subscriber(string ln, long long pn) {
        if (pn < 1000000) {
            throw invalid_argument("Initialization error: Phone number is too short or negative!");
        }
        lastName = ln;
        phoneNumber = pn;
    }

    string getLastName() const {
        return lastName;
    }

    long long getPhoneNumber() const {
        if (phoneNumber <= 0) {
            throw runtime_error("Read error: Phone number is missing or invalid!");
        }
        return phoneNumber;
    }

    Subscriber& operator=(long long newNumber) {
        if (newNumber < 1000000) {
            throw invalid_argument("Assignment error: Invalid phone number!");
        }
        this->phoneNumber = newNumber;
        return *this;
    }

    friend ostream& operator<<(ostream& os, const Subscriber& s) {
        os << "Last name: " << s.lastName << " | Tel: +" << s.phoneNumber;
        return os;
    }
};

class PhoneBook {
private:
    vector<Subscriber> subscribers;

public:
    PhoneBook() {}

    PhoneBook operator+(const Subscriber& s) {
        PhoneBook temp = *this;
        temp.subscribers.push_back(s);
        return temp;
    }

    void searchPhone(const string& targetLastName) const {
        bool found = false;
        cout << "\n--- Search by last name '" << targetLastName << "' ---" << endl;
        for (const auto& s : subscribers) {
            if (s.getLastName() == targetLastName) {
                cout << "Found: " << s << endl;
                found = true;
            }
        }
        if (!found) cout << "Subscriber with this last name not found." << endl;
    }

    void searchPhone(long long targetNumber) const {
        bool found = false;
        cout << "\n--- Search by number '+" << targetNumber << "' ---" << endl;
        for (const auto& s : subscribers) {
            try {
                if (s.getPhoneNumber() == targetNumber) {
                    cout << "Found: " << s << endl;
                    found = true;
                }
            }
            catch (const exception& e) {
                cout << "Record access error: " << e.what() << endl;
            }
        }
        if (!found) cout << "Subscriber with this number not found." << endl;
    }
};

int main() {
    PhoneBook book;

    cout << "=== Set 1: Valid data ===" << endl;
    try {
        Subscriber s1("Shevchenko", 380991234567);
        Subscriber s2("Franko", 380671112233);

        book = book + s1;
        book = book + s2;

        Subscriber s3("Lesya Ukrainka", 1000000);
        s3 = 380509998877;
        book = book + s3;

        cout << "Subscribers successfully added to the book!" << endl;

        book.searchPhone("Shevchenko");
        book.searchPhone(380509998877);

    }
    catch (const exception& e) {
        cout << "Unexpected error: " << e.what() << endl;
    }

    cout << "\n=== Set 2: Invalid data (Exception testing) ===" << endl;

    try {
        cout << "[Test 1] Attempt to create a subscriber with a negative number:" << endl;
        Subscriber sError("Kotsiubynskyi", -38099);
    }
    catch (const exception& e) {
        cout << "Exception caught: " << e.what() << endl;
    }

    try {
        cout << "\n[Test 2] Attempt to set an invalid number using the (=) operator:" << endl;
        Subscriber sTest("Stus", 380631234567);
        sTest = 123;
    }
    catch (const exception& e) {
        cout << "Exception caught: " << e.what() << endl;
    }

    return 0;
}