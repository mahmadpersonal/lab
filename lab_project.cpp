// OOP_Final_Preparation.cpp
#include <iostream>
#include <cstring>        // for C-strings
#include <stdexcept>      // for runtime_error
#include <fstream>        // for file handling

using namespace std;

// Custom Exception Class
class GadgetException : public runtime_error {
public:
    GadgetException(const string& msg) : runtime_error(msg) {
        ofstream file("errorlog.txt");
        if (file.is_open()) file << msg << endl;
        file.close();
    }
};

// Base Class: Encapsulation + Operator Overload + Virtual
class Gadget {
protected:
    int modelNo;
    double price;
    char brand[30];

public:
    Gadget() {
        modelNo = 0;
        price = 0.0;
        strcpy(brand, "Unknown");
    }

    Gadget(int m, double p, const char* b) {
        modelNo = m;
        price = p;
        strcpy(brand, b);
    }

    virtual void show() const {
        cout << "Model: " << modelNo << ", Price: " << price << ", Brand: " << brand << endl;
    }

    friend istream& operator>>(istream& in, Gadget& g) {
        cout << "Enter model no: "; in >> g.modelNo;
        cout << "Enter price: "; in >> g.price;
        cout << "Enter brand: "; in.ignore(); in.getline(g.brand, 30);
        return in;
    }

    friend ostream& operator<<(ostream& out, const Gadget& g) {
        out << "Model: " << g.modelNo << ", Price: " << g.price << ", Brand: " << g.brand << endl;
        return out;
    }

    virtual ~Gadget() {}
};

// Derived Class: Inheritance + Polymorphism
class Smartphone : public Gadget {
    int cameraMP;

public:
    Smartphone() : Gadget() {
        cameraMP = 0;
    }

    Smartphone(int m, double p, const char* b, int cam)
        : Gadget(m, p, b) {
        cameraMP = cam;
    }

    void show() const override {
        Gadget::show();
        cout << "Camera: " << cameraMP << " MP" << endl;
    }
};

// Interface (Abstract class) for pure virtual function
class Printable {
public:
    virtual void printSpec() const = 0;
};

// Derived class with multiple inheritance + pure virtual
class Smartwatch : public Gadget, public Printable {
    int batteryLife;

public:
    Smartwatch(int m, double p, const char* b, int bat)
        : Gadget(m, p, b), batteryLife(bat) {}

    void printSpec() const override {
        cout << "Smartwatch spec — Battery: " << batteryLife << " hrs" << endl;
    }

    void show() const override {
        Gadget::show();
        cout << "Battery Life: " << batteryLife << " hrs" << endl;
    }
};

// MAIN FUNCTION: combines everything
int main() {
    try {
        Gadget* devices[3];

        devices[0] = new Smartphone(101, 999.99, "Samsung", 108);
        devices[1] = new Smartphone(102, 799.99, "Xiaomi", 64);
        devices[2] = new Smartwatch(103, 299.99, "Apple", 18);

        for (int i = 0; i < 3; ++i) {
            devices[i]->show();
        }

        cout << "\n--- Using operator >> and << ---\n";
        Smartphone temp;
        cin >> temp;
        cout << temp;

        if (temp.modelNo < 0) {
            throw GadgetException("Invalid Model Number Entered!");
        }

        Printable* p = new Smartwatch(104, 349.99, "Fitbit", 24);
        p->printSpec();

        for (int i = 0; i < 3; ++i) {
            delete devices[i];
        }
        delete p;

    } catch (const GadgetException& e) {
        cout << "Caught Custom Exception: " << e.what() << endl;
    } catch (const exception& e) {
        cout << "Caught General Exception: " << e.what() << endl;
    }

    return 0;
}
