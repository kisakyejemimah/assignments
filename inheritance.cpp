#include <iostream>
#include <string>
using namespace std;

const double PI = 3.142;

class Material {
protected:
    string name;
    double resistivity;          // ohm-metre
public:
    Material(string n, double rho) : name(n), resistivity(rho) {}
    void displayMaterial() const {
        cout << "Material: " << name
             << ", resistivity = " << resistivity << " ohm-m\n";
    }
};

class Wire : public Material {
protected:
    double length;               // metres
    double area;                 // square metres
public:
    Wire(string n, double rho, double L, double A)
        : Material(n, rho), length(L), area(A) {}
    double resistance() const {
        return resistivity * length / area;      // R = rho L / A
    }
};

class Cable : public Wire {
private:
    int cores;
    double current;              // amperes
public:
    Cable(string n, double rho, double L, double A, int c, double I)
        : Wire(n, rho, L, A), cores(c), current(I) {}
    double voltageDrop() const { return current * resistance(); }          // V = IR
    double powerLoss()   const { return current * current * resistance(); } // P = I^2 R
    void displayCable() const {
        cout << "Cores: " << cores << ", current: " << current << " A\n";
    }
};

int main() {
    Cable c1("Copper", 1.68e-8, 100, 2.5e-6, 3, 10);

    c1.displayMaterial();                                  // from Material (grandparent)
    cout << "Resistance  = " << c1.resistance()  << " ohm\n"; // from Wire (parent)
    c1.displayCable();                                     // from Cable (own)
    cout << "Voltage drop = " << c1.voltageDrop() << " V\n";
    cout << "Power loss   = " << c1.powerLoss()   << " W\n";
    return 0;
}