#pragma once

#include <iostream>
#include <map>
#include <string>



namespace ariel {

    class NumberWithUnits {

    private:
        double unit_val;
        std::string unit_str;


    public:

        NumberWithUnits(double value, const std::string &unit);

        static void read_units(std::ifstream &units_file);
        static void print();
        static void assist(std::string st1, std::string st2);
        friend int comparison(const NumberWithUnits& num1, const NumberWithUnits& num2);


        /****************************  OverLoading Input&Output Operators ****************************************/

        friend std::ostream& operator<<(std::ostream& out, const NumberWithUnits &num);

        friend std::istream& operator>>(std::istream& in,NumberWithUnits &num);
        /*********************************************************************************************************/





        /***************** OverLoading Arithmetic Operators Such As : {+,+=,-,-=,*,*=}  **************************/

        NumberWithUnits operator+(const NumberWithUnits& num);

        NumberWithUnits operator-(const NumberWithUnits& num);

        NumberWithUnits operator+();

        NumberWithUnits operator-();

        NumberWithUnits& operator+=(const NumberWithUnits& num);

        NumberWithUnits& operator-=(const NumberWithUnits& num);

        friend NumberWithUnits operator*(const NumberWithUnits& num, const double val);

        friend NumberWithUnits operator*(const double val, const NumberWithUnits& num);

        NumberWithUnits& operator*=(const double val);
        /*********************************************************************************************************/


        /***************** OverLoading Incrementation&Decrementation Operators Such As : {++a,a++,--a,a--} *******/

         NumberWithUnits& operator++();
         NumberWithUnits& operator--();
         NumberWithUnits operator++(int);
         NumberWithUnits operator--(int);
        /*********************************************************************************************************/





        /****************  OverLoading Comparison Operators Such As : {<,<=,>,>=,==,!=}  *************************/

        friend bool operator>(const NumberWithUnits& num1, const NumberWithUnits& num2);

        friend bool operator>=(const NumberWithUnits &num1, const NumberWithUnits& num2);

        friend bool operator<(const NumberWithUnits& num1, const NumberWithUnits& num2);

        friend bool operator<=(const NumberWithUnits& num1, const NumberWithUnits& num2);

        friend bool operator==(const NumberWithUnits& num1, const NumberWithUnits& num2);

        friend bool operator!=(const NumberWithUnits& num1, const NumberWithUnits& num2);
        /*********************************************************************************************************/
    };
}

