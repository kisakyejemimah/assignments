#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const double PI = 3.142;

class Component {
public:
    virtual double impedance(double f) const = 0;   // pure virtual
    virtual string name() const = 0;
    virtual ~Component() {}
};
    
class Resistor : public Component {
    double R;
public:
    Resistor(double r) : R(r) {}
    double impedance(double /*f*/) const override { return R; }   // Z = R
    string name() const override { return "Resistor"; }
};

class Inductor : public Component {
    double L;
public:
    Inductor(double l) : L(l) {}
    double impedance(double f) const override { return 2 * PI * f * L; }   // XL = 2 pi f L
    string name() const override { return "Inductor"; }
};

class Capacitor : public Component {
    double C;
public:
    Capacitor(double c) : C(c) {}
    double impedance(double f) const override { return 1.0 / (2 * PI * f * C); } // XC = 1/(2 pi f C)
    string name() const override { return "Capacitor"; }
};

int main() {
    double f = 50;                                    // supply frequency in Hz
    Component* parts[3] = { new Resistor(100),
                            new Inductor(0.1),
                            new Capacitor(100e-6) };

    cout << fixed << setprecision(2);
    for (int i = 0; i < 3; i++) {
        cout << parts[i]->name() << ": "
             << parts[i]->impedance(f) << " ohm at " << f << " Hz\n";
    }

    for (int i = 0; i < 3; i++) delete parts[i];
    return 0;
}