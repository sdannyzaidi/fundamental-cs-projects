#include<iostream>
using namespace std;

class lumsVehicle
{
private:
    string color;
    int regNo;
    
public:
    lumsVehicle()
    {
        color = "";
        regNo = 0;
    }
    void set_color(string a)
    {
        color = a;
    }
    void set_regNo(int b)
    {
        regNo = b;
    }
    string get_color()
    {
        return color;
    }
    int get_regNo()
    {
        return regNo;
    }
    void print_details ()
    {
        cout << "Color of vehicle: " << get_color() << endl;
        cout << "RegNo of vehicle: " << get_regNo() << endl;
    }
    
};

class vans : public lumsVehicle
{
public:
    void print_van()
    {
        cout << "Van Details" << endl << endl;
        print_details();
        cout << endl;
    }
};

class lifters : public lumsVehicle
{
private:
    int cap;
public:
    lifters()
    {
        cap = 0;
    }
    void set_cap(int c)
    {
        cap = c;
    }
    int get_cap()
    {
        return cap;
    }
    void print_lifters()
    {
        cout << "Lifter Details" << endl << endl;
        print_details();
        cout << "Capacity of Lifters: " << get_cap() << endl;
        cout << endl;
    }
};

class bikes : public lumsVehicle
{
private:
     string bikeT;
public:
    bikes()
    {
        bikeT = "";
    }
    void set_bikeT(string d)
    {
        bikeT = d;
    }
    string get_bikeT()
    {
        return bikeT;
    }
    void print_b()
    {
        cout << "Bike Details" << endl << endl;
        print_details();
        cout << "Type of bike: " << get_bikeT() << endl;
         cout << endl;
    }
};

int main()
{
    cout << "LUMS VEHICLE DETAILS"<<endl;
    cout << endl;
    string color,type;
    int num, cap;
        vans v_1;
        cout << "Enter color of van: ";
        cin >> color;
        v_1.set_color(color);
        cout << "Enter registration number of van: ";
        cin >> num;
        v_1.set_regNo(num);
        cout << endl;
        v_1.print_van();
    
        lifters l_1;
        cout << "Enter color of lifter: ";
        cin >> color;
        l_1.set_color(color);
        cout << "Enter registration number of lifter: ";
        cin >> num;
        l_1.set_regNo(num);
        cout << "Enter capacity of lifter: ";
        cin >> cap;
        l_1.set_cap(cap);
        cout << endl;
        l_1.print_lifters();
    
        bikes b_1;
        cout << "Enter color of bike: ";
        cin >> color;
        b_1.set_color(color);
        cout << "Enter registration number of bike: ";
        cin >> num;
        b_1.set_regNo(num);
        cout << "Enter type of bike: ";
        cin >> type;
        b_1.set_bikeT(type);
        cout << endl;
        b_1.print_b();
    return 0;
}
