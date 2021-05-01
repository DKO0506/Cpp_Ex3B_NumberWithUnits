#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

#include "NumberWithUnits.hpp"

using namespace ariel;

int main() {


    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);

    NumberWithUnits a{2, "km"};
    cout << "a:\t" << a << endl;
    cout << "(-a):\t" << (-a) << endl;
    cout << "(3 * a):\t" << (3 * a) << endl;
    cout << "(a * 3):\t" << (a * 3) << endl;


    NumberWithUnits b{300, "m"};

    cout << "(a+b) :\t" << (a + b) << endl;
    cout << "(b-a) :\t" << (b - a) << endl;


    NumberWithUnits d{200, "cm"};

    cout << "(a+d) : \t" << (a + d) << endl;
    cout << "(d-a) : \t" << (d - a) << endl;


    cout << boolalpha;
    cout << "(a>b) :\t" << (a > b) << endl;
    cout << "(a<=b) :\t" << (a <= b) << endl;
    cout << "a=NumberWithUnits{2000, \"m\"}:\t" << (a == NumberWithUnits{2000, "m"}) << endl;


    istringstream sample_input{"700 [ kg ]"};
    sample_input >> a;
    cout << a << endl;
    cout << (a += NumberWithUnits{1, "ton"}) << endl;
    cout << a << endl;


    NumberWithUnits c{1, "km"};
    cout << "postfix inc (should be 1):" << c++ << endl;
    cout << "current (should be 2):" << c << endl;
    cout << "prefix inc (should be 3):" << ++c << endl;
    cout << "current (should be 3):" << c << endl;
    cout << "postfix dec (should be 3):" << c-- << endl;
    cout << "current (should be 2):" << c << endl;
    cout << "prefix dec (should be 1):" << --c << endl;
    cout << c++ << endl;
    try {
        cout << (a + b) << endl;
    } catch (const std::exception &ex) {
        cout << ex.what() << endl; // Prints "Units do not match - [m] cannot be converted to [kg]"
    }
    NumberWithUnits::print();
    cout << "End of demo!" << endl;


    return 0;
}

