#include <iostream>
#include <fstream>
#include <string>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

class Shooter
{
private:
    string ammoName;
    int ammoCount;

protected:
    Shooter()
    {
        ammoName = "немає";
        ammoCount = 0;
    }

    void giveAmmo(string name, int count)
    {
        ammoName = name;
        ammoCount = count;
    }

    void shoot()
    {
        if (ammoCount > 0)
        {
            ammoCount--;
            cout << "постріл! Витрачено: " << ammoName
                 << ". Залишилось: " << ammoCount << endl;
        }
        else
        {
            cout << "амуніції (" << ammoName << ") не залишилось, постріл неможливий!" << endl;
        }
    }
};

class Archer : protected virtual Shooter
{
protected:
    Archer() {}

public:
    void shoot()
    {
        cout << "[Лучник] ";
        Shooter::shoot();
    }
};

class Ranger : protected virtual Shooter
{
protected:
    Ranger() {}

public:
    void shoot()
    {
        cout << "[Рейнджер] ";
        Shooter::shoot();
    }
};

class Catapult : protected Shooter
{
protected:
    Catapult() {}

public:
    void shoot()
    {
        cout << "[Катапульта] ";
        Shooter::shoot();
    }
};

class ArrowTower : public Archer, public Ranger
{
protected:
    ArrowTower() {}
};

class Fortress : public ArrowTower, public Catapult
{
private:
    string name;
    double wallThickness;
    int gateState;

public:
    Fortress(string fortName, double wall, int gate, int arrows, int stones)
    {
        name = fortName;
        wallThickness = wall;
        gateState = gate;

        ArrowTower::giveAmmo("стріла", arrows);
        Catapult::giveAmmo("камінь", stones);

        cout << "Фортецю «" << name << "» збудовано. Стріл: "
             << arrows << ", каменів: " << stones << endl << endl;

        ofstream fout("fortress_info.txt");
        if (!fout.is_open())
        {
            cout << "Помилка: не вдалося відкрити файл!" << endl;
            return;
        }
        fout << "=== Інформація про фортецю ===" << endl;
        fout << "Назва: " << name << endl;
        fout << "Товщина стін: " << wallThickness << " м" << endl;
        fout << "Стан воріт: " << gateState << " %" << endl;
        fout << "Стріл у вежі: " << arrows << endl;
        fout << "Каменів у катапульті: " << stones << endl;
        fout.close();
    }
};

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif

    Fortress fortress("Хотинська фортеця", 5.5, 100, 4, 10);

    cout << "--- Стрільба ---" << endl;
    for (int i = 0; i < 3; i++)
        fortress.Archer::shoot();
    for (int i = 0; i < 2; i++)
        fortress.Ranger::shoot();
    fortress.Catapult::shoot();

    ofstream outFile("fortress_info.txt", ios::app);
    if (!outFile.is_open())
    {
        cout << "Помилка: файл не відкрито!" << endl;
        return 1;
    }
    outFile << endl << "=== Ієрархія класів ===" << endl;
    outFile << "Shooter    (Стрілець)        - базовий клас; поля ammoName, ammoCount (private);" << endl;
    outFile << "                               методи giveAmmo(), shoot() (protected)" << endl;
    outFile << "Archer     (Лучник)          - protected virtual Shooter; shoot() - public" << endl;
    outFile << "Ranger     (Рейнджер)        - protected virtual Shooter; shoot() - public" << endl;
    outFile << "Catapult   (Катапульта)      - protected Shooter; shoot() - public" << endl;
    outFile << "ArrowTower (Стрілкова вежа)  - public Archer, public Ranger" << endl;
    outFile << "Fortress   (Фортеця)         - public ArrowTower, public Catapult" << endl;
    outFile.close();

    ifstream infoFile("fortress_info.txt");
    if (!infoFile.is_open())
    {
        cout << "Помилка: файл не вдалося прочитати!" << endl;
        return 1;
    }
    cout << endl << "--- Вміст файлу fortress_info.txt ---" << endl;
    string line;
    while (getline(infoFile, line))
        cout << line << endl;
    infoFile.close();

    return 0;
}