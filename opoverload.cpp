#include <iostream>
#include <cstring>
using namespace std;

class Gadget {
private:
    int modelNumber;
    double price;
    char brand[50]; // C-string

public:
    // Constructor
    Gadget(int mn = 0, double p = 0.0, const char* b = "") {
        modelNumber = mn;
        price = p;
        strcpy(brand, b);
    }

    // Copy constructor
    Gadget(const Gadget &g) {
        modelNumber = g.modelNumber;
        price = g.price;
        strcpy(brand, g.brand);
    }

    // Assignment operator (=)
    Gadget& operator=(const Gadget &g) {
        if (this != &g) {
            modelNumber = g.modelNumber;
            price = g.price;
            strcpy(brand, g.brand);
        }
        return *this;
    }

    // Addition operator (+) - combines prices, keeps first brand and model
    Gadget operator+(const Gadget &g) {
        Gadget temp;
        temp.modelNumber = modelNumber;
        temp.price = price + g.price;
        strcpy(temp.brand, brand);
        return temp;
    }

    // Increment operator (prefix ++)
    Gadget& operator++() {
        price += 10; // increment price by 10
        return *this;
    }

    // Increment operator (postfix ++)
    Gadget operator++(int) {
        Gadget temp = *this;
        price += 10;
        return temp;
    }

    // Stream insertion operator (cout <<)
    friend ostream& operator<<(ostream &out, const Gadget &g) {
        out << "Model: " << g.modelNumber << ", Price: " << g.price << ", Brand: " << g.brand;
        return out;
    }

    // Stream extraction operator (cin >>)
    friend istream& operator>>(istream &in, Gadget &g) {
        cout << "Enter model number: ";
        in >> g.modelNumber;
        cout << "Enter price: ";
        in >> g.price;
        cout << "Enter brand: ";
        in.ignore(); // clear newline
        in.getline(g.brand, 50);
        return in;
    }

    // Subscript operator [] for brand characters
    char& operator[](int index) {
        if (index >= 0 && index < 50) {
            return brand[index];
        }
        // Return first character if invalid index (simple error handling)
        return brand[0];
    }

    // Equality operator (==)
    bool operator==(const Gadget &g) const {
        return (modelNumber == g.modelNumber) && (price == g.price) && (strcmp(brand, g.brand) == 0);
    }
};

int main() {
    Gadget g1(101, 299.99, "Samsung");
    Gadget g2(102, 399.99, "Apple");

    cout << "Gadget 1: " << g1 << endl;
    cout << "Gadget 2: " << g2 << endl;

    Gadget g3 = g1 + g2;
    cout << "After adding prices (g3 = g1 + g2): " << g3 << endl;

    ++g1; // prefix increment
    cout << "After prefix ++g1: " << g1 << endl;

    g2++; // postfix increment
    cout << "After postfix g2++: " << g2 << endl;

    cout << "Enter a new gadget:" << endl;
    Gadget g4;
    cin >> g4;
    cout << "You entered: " << g4 << endl;

    cout << "Access brand's 3rd character of g4: " << g4[2] << endl; // index 2 is 3rd char

    if (g1 == g2)
        cout << "g1 and g2 are equal" << endl;
    else
        cout << "g1 and g2 are NOT equal" << endl;

    return 0;
}
