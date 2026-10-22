#include <iostream>
using namespace std;

class Rectangle {
private:
    double width;
    double length;

public:
    // Constructor: sets the starting size
    Rectangle(double w, double l) {
        width = w;
        length = l;
    }

    // Setters
    void setWidth(double w) { width = w; }
    void setLength(double l) { length = l; }

    // Getters
    double getWidth() const { return width; }
    double getLength() const { return length; }

    // Calculations
    double area() const { return width * length; }
    double perimeter() const { return 2 * (width + length); }
};

int main() {
    // Creating two rectangles
    Rectangle first(6, 4);
    Rectangle second(3, 3);

    cout << "First rectangle:  " << first.getWidth() << " x " << first.getLength() << endl;
    cout << "Second rectangle: " << second.getWidth() << " x " << second.getLength() << endl;

    // Changing the second rectangle's size and outputting it back
    second.setWidth(5);
    second.setLength(7);
    cout << "Second rectangle resized to: " << second.getWidth()
         << " x " << second.getLength() << endl;

    // Area and perimeter of both
    cout << "\nFirst: \n Area: " << first.area() << ", Perimeter: " << first.perimeter() << endl;
    cout << "Second: \n Area: " << second.area() << ", Perimeter: " << second.perimeter() << endl;

    return 0;
}
