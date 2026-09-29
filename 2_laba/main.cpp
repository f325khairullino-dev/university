#include <iostream>
#include <string>
using namespace std;


class Liky {
private:
    string name;
    string instruction;
    double price;

public:
    Liky() {
        name = "";
        instruction = "";
        price = 0.0;
    }

    Liky(string name_, string instruction_, double price_) {
        name = name_;
        instruction = instruction_;
        price = price_;
    }

    ~Liky() {}

    void setName(string value) { name = value; }
    string getName() { return name; }

    void setInstruction(string value) { instruction = value; }
    string getInstruction() { return instruction; }

    void setPrice(double value) { price = value; }
    double getPrice() { return price; }

    void show() {
        cout << "Препарат: " << name << endl;
        cout << "  Інструкція: " << instruction << endl;
        cout << "  Вартість: " << price << " грн" << endl;
    }
};


class Apteka {
private:
    Liky* medicines;
    int count;

public:
    Apteka(int n) {
        count = n;
        medicines = new Liky[count];
    }

    ~Apteka() {
        delete[] medicines;
    }

    void setMedicine(int index, Liky med) {
        if (index >= 0 && index < count)
            medicines[index] = med;
    }

    Liky getMedicine(int index) {
        return medicines[index];
    }

    int getCount() { return count; }

    void showAll() {
        cout << "\n=== Список ліків в аптеці ===\n";
        for (int i = 0; i < count; i++) {
            medicines[i].show();
        }
    }


    bool isAvailable(string medName) {
        for (int i = 0; i < count; i++) {
            if (medicines[i].getName() == medName)
                return true;
        }
        return false;
    }


    double getPriceByName(string medName) {
        for (int i = 0; i < count; i++) {
            if (medicines[i].getName() == medName)
                return medicines[i].getPrice();
        }
        return -1.0;
    }
};


class Recept {
private:
    string* medicineNames;
    int count;

public:
    Recept(int n) {
        count = n;
        medicineNames = new string[count];
    }

    ~Recept() {
        delete[] medicineNames;
    }

    void setMedicineName(int index, string name) {
        if (index >= 0 && index < count)
            medicineNames[index] = name;
    }

    string getMedicineName(int index) {
        return medicineNames[index];
    }

    int getCount() { return count; }

    void show() {
        cout << "\n=== Рецепт (потрібні ліки) ===\n";
        for (int i = 0; i < count; i++) {
            cout << "  - " << medicineNames[i] << endl;
        }
    }


    void checkAndCalculate(Apteka& apteka) {
        double total = 0.0;
        cout << "\n=== Результат перевірки рецепту ===\n";
        for (int i = 0; i < count; i++) {
            string med = medicineNames[i];
            if (apteka.isAvailable(med)) {
                double price = apteka.getPriceByName(med);
                cout << "  " << med << " - Є В НАЯВНОСТІ, ціна: " << price << " грн" << endl;
                total += price;
            } else {
                cout << "  " << med << " - НЕМАЄ В НАЯВНОСТІ" << endl;
            }
        }
        cout << "\nЗагальна вартість наявних ліків за рецептом: " << total << " грн" << endl;
    }
};

int main() {
    setlocale(LC_ALL, "Ukrainian");


    Apteka apteka(5);
    apteka.setMedicine(0, Liky("Парацетамол", "По 1 таблетці 3 рази на день", 25.50));
    apteka.setMedicine(1, Liky("Аспірин", "По 1 таблетці після їжі", 18.00));
    apteka.setMedicine(2, Liky("Нурофен", "По 1 таблетці при болю", 45.90));
    apteka.setMedicine(3, Liky("Амоксицилін", "По 1 капсулі 2 рази на день", 62.30));
    apteka.setMedicine(4, Liky("Но-шпа", "По 2 таблетки при спазмах", 33.75));

    apteka.showAll();


    Recept recept(3);
    recept.setMedicineName(0, "Парацетамол");
    recept.setMedicineName(1, "Нурофен");
    recept.setMedicineName(2, "Ібупрофен");

    recept.show();
    recept.checkAndCalculate(apteka);

    return 0;
}