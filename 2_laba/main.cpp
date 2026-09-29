#include <iostream>
#include <string>
using namespace std;

class Medicine {
private:
    string name;
    string instruction;
    double price;

public:
    Medicine() {
        this->name = "";
        this->instruction = "";
        this->price = 0.0;
    }

    Medicine(string name, string instruction, double price) {
        this->name = name;
        this->instruction = instruction;
        this->price = price;
    }

    ~Medicine() {}

    void setName(string value) {
        this->name = value;
    }

    string getName() {
        return this->name;
    }

    void setInstruction(string value) {
        this->instruction = value;
    }

    string getInstruction() {
        return this->instruction;
    }

    void setPrice(double value) {
        this->price = value;
    }

    double getPrice() {
        return this->price;
    }

    void show() {
        cout << "Medicine: " << this->name << endl;
        cout << "  Instruction: " << this->instruction << endl;
        cout << "  Price: " << this->price << " UAH" << endl;
    }
};

class Pharmacy {
private:
    Medicine* medicines;
    int count;

public:
    Pharmacy(int count) {
        this->count = count;
        this->medicines = new Medicine[this->count];
    }

    ~Pharmacy() {
        delete[] this->medicines;
    }

    void setMedicine(int index, Medicine medicine) {
        if (index >= 0 && index < this->count)
            this->medicines[index] = medicine;
    }

    Medicine getMedicine(int index) {
        return this->medicines[index];
    }

    int getCount() {
        return this->count;
    }

    void showAll() {
        cout << "\n=== List of medicines in the pharmacy ===\n";

        for (int i = 0; i < this->count; i++) {
            this->medicines[i].show();
        }
    }

    bool isAvailable(string medicineName) {
        for (int i = 0; i < this->count; i++) {
            if (this->medicines[i].getName() == medicineName)
                return true;
        }

        return false;
    }

    double getPriceByName(string medicineName) {
        for (int i = 0; i < this->count; i++) {
            if (this->medicines[i].getName() == medicineName)
                return this->medicines[i].getPrice();
        }

        return -1.0;
    }
};

class Prescription {
private:
    string* medicineNames;
    int count;

public:
    Prescription(int count) {
        this->count = count;
        this->medicineNames = new string[this->count];
    }

    ~Prescription() {
        delete[] this->medicineNames;
    }

    void setMedicineName(int index, string name) {
        if (index >= 0 && index < this->count)
            this->medicineNames[index] = name;
    }

    string getMedicineName(int index) {
        return this->medicineNames[index];
    }

    int getCount() {
        return this->count;
    }

    void show() {
        cout << "\n=== Prescription (required medicines) ===\n";

        for (int i = 0; i < this->count; i++) {
            cout << "  - " << this->medicineNames[i] << endl;
        }
    }

    void checkAndCalculate(Pharmacy& pharmacy) {
        double total = 0.0;

        cout << "\n=== Prescription check result ===\n";

        for (int i = 0; i < this->count; i++) {
            string medicine = this->medicineNames[i];

            if (pharmacy.isAvailable(medicine)) {
                double price = pharmacy.getPriceByName(medicine);

                cout << "  " << medicine
                     << " - AVAILABLE, price: "
                     << price << " UAH" << endl;

                total += price;
            }
            else {
                cout << "  " << medicine
                     << " - NOT AVAILABLE" << endl;
            }
        }

        cout << "\nTotal cost of available medicines: "
             << total << " UAH" << endl;
    }
};

int main() {
    Pharmacy pharmacy(5);

    pharmacy.setMedicine(
        0,
        Medicine("Paracetamol", "1 tablet 3 times a day", 25.50)
    );

    pharmacy.setMedicine(
        1,
        Medicine("Aspirin", "1 tablet after a meal", 18.00)
    );

    pharmacy.setMedicine(
        2,
        Medicine("Nurofen", "1 tablet when experiencing pain", 45.90)
    );

    pharmacy.setMedicine(
        3,
        Medicine("Amoxicillin", "1 capsule 2 times a day", 62.30)
    );

    pharmacy.setMedicine(
        4,
        Medicine("No-Spa", "2 tablets when experiencing spasms", 33.75)
    );

    pharmacy.showAll();

    Prescription prescription(3);

    prescription.setMedicineName(0, "Paracetamol");
    prescription.setMedicineName(1, "Nurofen");
    prescription.setMedicineName(2, "Ibuprofen");

    prescription.show();
    prescription.checkAndCalculate(pharmacy);

    return 0;
}