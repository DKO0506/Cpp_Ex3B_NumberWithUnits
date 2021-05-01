#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <map>
#include "NumberWithUnits.hpp"


using namespace std;

const double EPSI = 0.001;


namespace ariel {

    static map<string, map<string, double> > units_map;


    NumberWithUnits::NumberWithUnits(double value, const string &unit) {
        if (units_map.count(unit) == 0) {
            throw invalid_argument{"Unit doesn't exist! "};
        }
        this->unit_val = value;
        this->unit_str = unit;
    }

    void NumberWithUnits::read_units(std::ifstream &units_file) {
        string str1;
        string str2;
        string buff;

        double val1 = 0;
        double val2 = 0;

        while (units_file >> val1 >> str1 >> buff >> val2 >> str2) {
            units_map[str1][str1] = 1;
            units_map[str1][str2] = val2 / val1;
            units_map[str2][str1] = val1 / val2;

            assist(str1, str2);
            assist(str2, str1);


            for (const auto &i : units_map) {
                std::cout << i.first << "--- >";
                for (const auto &j : units_map[i.first]) {
                    std::cout << "{" << i.first << ", " << units_map[i.first][j.first] << "}";
                }
                cout << endl;
            }
            cout
                    << "************************************************************************************************************\n";
        }
    }

    void NumberWithUnits::assist(string st1, string st2) {
        for (pair<string, double> v : units_map[st1]) {
            units_map[st2][v.first] = units_map[st1][v.first] * units_map[st2][st1];
            units_map[v.first][st2] = 1 / units_map[st2][v.first];
        }
    }


    double connect(double val, const string &src, const string &dest) {
        if (src == dest) {
            return val;
        }
        try {
            return val * units_map.at(src).at(dest);
        }
        catch (const exception &e) {
            throw invalid_argument{"Units do not match - [" + src + "] can't be converted to [" + dest + "]"};
        }
    }


    /****************************  OverLoading Input&Output Operators ****************************************/
    ostream &operator<<(ostream &out, const NumberWithUnits &num) {
        out << num.unit_val << "[" << num.unit_str << "]";
        return out;
    }

    istream &operator>>(istream &in, NumberWithUnits &num) {
        string str;
        double value;

        in >> value;

        getline(in, str, ']');


        str.erase(remove(str.begin(), str.end(), ' '), str.end());


        str = str.substr(1, str.size() - 1);

        num = NumberWithUnits{value, str};

        return in;
    }
    /*********************************************************************************************************/


    /***************** OverLoading Arithmetic Operators Such As : {+,+=,-,-=,*,*=}  **************************/

    NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits &num) {
        double val = connect(num.unit_val, num.unit_str, this->unit_str);
        return NumberWithUnits(this->unit_val + val, this->unit_str);
    }

    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits &num) {
        double val = connect(num.unit_val, num.unit_str, this->unit_str);
        return NumberWithUnits(this->unit_val - val, this->unit_str);
    }

    NumberWithUnits NumberWithUnits::operator+() {
        return NumberWithUnits(+this->unit_val, this->unit_str);
    }

    NumberWithUnits NumberWithUnits::operator-() {
        return NumberWithUnits(-this->unit_val, this->unit_str);

    }

    NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &num) {
        *this = *this + num;
        return *this;
    }

    NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &num) {
        *this = *this - num;
        return *this;
    }

    NumberWithUnits operator*(const NumberWithUnits &num, const double val) {
        return NumberWithUnits(num.unit_val * val, num.unit_str);
    }

    NumberWithUnits operator*(const double val, const NumberWithUnits &num) {
        return NumberWithUnits(num.unit_val * val, num.unit_str);
    }

    NumberWithUnits &NumberWithUnits::operator*=(const double val) {
        this->unit_val *= val;
        return *this;
    }
/*********************************************************************************************************/













    /***************** OverLoading Incrementation&Decrementation Operators Such As : {++a,a++,--a,a--} *******/

    NumberWithUnits &NumberWithUnits::operator++() {
        ++(this->unit_val);
        return *this;
    }

    NumberWithUnits &NumberWithUnits::operator--() {
        --(this->unit_val);
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator++(int) {
        return NumberWithUnits((this->unit_val)++, this->unit_str);
    }

    NumberWithUnits NumberWithUnits::operator--(int) {
        return NumberWithUnits((this->unit_val)--, this->unit_str);
    }
    /*********************************************************************************************************/








    /****************  OverLoading Comparison Operators Such As : {<,<=,>,>=,==,!=}  *************************/


    int comparison(const NumberWithUnits& num1, const NumberWithUnits& num2)
    {
        double val = num1. unit_val - connect(num2.unit_val,num2.unit_str,num1.unit_str);
        int answer = 0;

        if (val > EPSI)
        {
            answer = 1;
        }
        else if(-val > EPSI)
        {
            answer = -1;
        }
        return answer;
    }




    bool operator>(const NumberWithUnits &num1, const NumberWithUnits &num2)
    {
        return comparison(num1,num2) > 0;
    }

     bool operator>=(const NumberWithUnits &num1, const NumberWithUnits& num2)
     {
         return comparison(num1,num2) >= 0;
     }

     bool operator<(const NumberWithUnits& num1, const NumberWithUnits& num2)
     {
         return comparison(num1,num2) < 0;
     }
     bool operator<=(const NumberWithUnits& num1, const NumberWithUnits& num2)
     {
         return comparison(num1,num2) <= 0;
     }
     bool operator==(const NumberWithUnits& num1, const NumberWithUnits& num2)
     {
         return comparison(num1,num2) == 0;
     }
     bool operator!=(const NumberWithUnits& num1, const NumberWithUnits& num2)
     {
         return comparison(num1,num2) != 0;
     }
    /*********************************************************************************************************/








    void NumberWithUnits::print()
    {
        uint a = 0;
        for(auto& i : units_map)
        {
            uint length = i.second.size();
            a = std::max(a, length);
        }
        string str(a*20/2, '-');

        cout << str << "Units Map" << str << endl;

        for(auto& i :units_map)
        {
            cout << "1 " << i.first << "\t:=";
            for(auto& j : units_map[i.first])
            {
                string temp = to_string(j.second) + "[" + j.first + "]";
                cout << right << std::setw(20) << temp;
            }
            cout << endl;
        }
        cout << str << ******* THE END  ******* " << str << endl;
    }






}
