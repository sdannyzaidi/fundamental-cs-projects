#include<iostream>
using namespace std;


struct dateType
{
private:
int day;
int month;
int year;
string mon;
    
public:
    
    dateType()
    {
        day = 1;
        month = 1;
        year = 1;
        mon = "";
    }
    dateType(int day1)
    {
        day = day1;
        month = 1;
        year = 1;
    }
    dateType(int day1, int month1)
    {
        day = day1;
        month = month1;
        year = 1;
    }
    dateType(int day1, int month1, int year1)
    {
        day = day1;
        month = month1;
        year = year1;
    }
    void setDate(int a, int b, int c)
    {
            day = a;
            month = b;
            year = c;
    }
    int getDate()
    {
        int new_date;
        new_date = (day*1000000) + (month*10000) + year;
        return new_date;
    }
    int IncrementDay()
    {
        day++;
        if (day <= 30)
        {
            return day;
        }
        else if (day > 30)
        {
            day = day - 30;
            month ++;
            if (month > 12)
            {
                month = month - 12;
                year++;
            }
        }
        return getDate();
    }
    int IncrementMonth()
    {
        month ++;
        if (month > 12)
        {
            month = month - 12;
            year++;
        }
        return getDate();
    }
    int IncrementYear()
    {
        year++;
        return year;
    }
    void isEqualDate(dateType a, dateType b)
    {
        int compDate1 = a.getDate();
        int compDate2 = b.getDate();
        if (compDate1 == compDate2)
        {
            cout << "Both dates are equal" << endl;
        }
        else
        {
            cout << "Dates are not equal" << endl;
        }
    }
    int IncrementByCertainNumber(int num)
    {
        if (num < 30)
        {
        day = day + num;
            if (day <= 30)
            {
                return day;
            }
            else if (day > 30)
            {
                day = day - 30;
                month ++;
                if (month > 12)
                {
                    month = month - 12;
                    year++;
                }
            }
        }
        else if (num > 30)
        {
            int counter = 0;
            while (num > 30)
            {
                num = num - 30;
                counter ++;
            }
            day = day + num;
            month = month + counter;
            if (day > 30)
            {
                day = day - 30;
                month ++;

                if (month > 12)
                {
                    month = month - 12;
                    year++;
                }
            }
            }
        return getDate();
        }
    
    void printDate()
    {
        int date_print;
        date_print = getDate();
        year = date_print % 10000;
        date_print = date_print / 10000;
        month = date_print % 100;
        date_print = date_print / 100;
        day = date_print;
        switch (month) {
            case 1: mon = "January"; break;
            case 2: mon = "February"; break;
            case 3: mon = "March"; break;
            case 4: mon = "April"; break;
            case 5: mon = "May"; break;
            case 6: mon = "June"; break;
            case 7: mon = "July"; break;
            case 8: mon = "August"; break;
            case 9: mon = "September"; break;
            case 10: mon = "October"; break;
            case 11: mon = "November"; break;
            case 12: mon = "December"; break;
            default: mon = ""; break;
        }
        cout << "Date is: " << day << "-" << mon << "-" << year << endl;
    }
};


int main()
{
    dateType D;
    dateType C;
    int d,y,m;
    
    cout<<"Enter date"<<endl;
    cout << "Day: ";
    cin>>d;
    cout << "Month: ";
    cin>>m;
    cout << "Year: ";
    cin>>y;
    cout<<endl;
    D.setDate(d,m,y);
    D.printDate();
    cout<<endl;
    
    cout<<"********************"<<endl;
    d=31;
    m=9;
    y=1995;
    cout<<"Set date:"<<d<<"-"<<m<<"-"<<y<<endl;
    D.setDate(d,m,y);
    cout<<endl;
    D.printDate();
    cout<<endl;
    cout<<"********************"<<endl;
    
    d=30;
    m=12;
    y=1998;
    cout<<"Set date:"<<d<<"-"<<m<<"-"<<y<<endl;
    D.setDate(d,m,y);
    D.printDate();
    cout<<endl;
    cout<<"********************"<<endl;
    
    cout<<"AFTER INCREMENTING BY 1 DAY"<<endl;
    D.IncrementDay();
    D.printDate();
    cout<<endl;
    cout<<"********************"<<endl;
    cout<<"If "<<endl;
    D.setDate(30,12,2007);
    D.printDate();
    cout<<endl;
    cout<<"AFTER INCREMENTING BY 1 MONTH"<<endl;
    
    D.IncrementMonth();
    D.printDate();
    cout<<endl;
    cout<<"********************"<<endl;
    cout<<"AFTER INCREMENTING BY 1 YEAR"<<endl;
    
    D.IncrementYear();
    D.printDate();
    cout<<endl;
    cout<<"********************"<<endl;
    
    C.setDate(30,1,2009);
    cout<<"New object created:"<<endl;
    cout<<"DATE1:"<<endl;
    C.printDate();
    cout<<"DATE2:"<<endl;
    D.printDate();
    cout<<endl;
    D.isEqualDate(D,C);

    cout<<"********************************"<<endl;
    cout<<"If ";
    D.printDate();
    cout<<endl;
    cout<<"Date after 120 days will be"<<endl;
    D.IncrementByCertainNumber(120);
    D.printDate();
    return 0;
}
