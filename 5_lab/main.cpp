#include <iostream>
#include <cmath>
using namespace std;

const double PI = 3.14159265358979;

class Triangle {
protected:
    double a;
    double b;
    double angle;
public:
    Triangle(double a, double b, double angle) {
        this->a = a;
        this->b = b;
        this->angle = angle;
    }
    virtual double area() const = 0;
    virtual ~Triangle() {}
};

class RightTriangle : public Triangle {
public:
    RightTriangle(double a, double b) : Triangle(a, b, 90) {}
    virtual double area() const {
        return a * b / 2;
    }
};

class IsoscelesTriangle : public Triangle {
public:
    IsoscelesTriangle(double a, double angle) : Triangle(a, a, angle) {}
    virtual double area() const {
        return a * a * sin(angle * PI / 180) / 2;
    }
};

class EquilateralTriangle : public Triangle {
public:
    EquilateralTriangle(double a) : Triangle(a, a, 60) {}
    virtual double area() const {
        return a * a * sqrt(3.0) / 4;
    }
};

int main() {
    double a1, b1;
    double a2, ang2;
    double a3;

    cout << "Right triangle. Enter legs a and b: ";
    cin >> a1 >> b1;

    cout << "Isosceles triangle. Enter side a and the angle between the equal sides (degrees): ";
    cin >> a2 >> ang2;

    cout << "Equilateral triangle. Enter side a: ";
    cin >> a3;

    if (a1 <= 0 || b1 <= 0 || a2 <= 0 || ang2 <= 0 || ang2 >= 180 || a3 <= 0) {
        cout << "Error: sides must be greater than 0, angle must be between 0 and 180." << endl;
        return 1;
    }

    Triangle* t[3];
    t[0] = new RightTriangle(a1, b1);
    t[1] = new IsoscelesTriangle(a2, ang2);
    t[2] = new EquilateralTriangle(a3);

    const char* names[3] = { "Right", "Isosceles", "Equilateral" };

    cout << endl << "Results:" << endl;
    for (int i = 0; i < 3; i++) {
        cout << names[i] << " triangle: S = " << t[i]->area() << endl;
    }

    for (int i = 0; i < 3; i++) {
        delete t[i];
    }

    return 0;
}