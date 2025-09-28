#include<iostream>
#include<string>
#include<time.h>
#include<cstdlib>
#include<ctime>
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
        cout << day << "-" << mon << "-" << year;
    }
};

struct student
{
private:
dateType date_of_birth;
string *name;
int *roll_num;
int *marks;
char *grade;

public:

    student()
    {
        name = new string;
        *name = "0";
        roll_num = new int;
        *roll_num = 1;
        marks = new int;
        *marks = 0;
        grade = new char;
        *grade = 'Z';
        
    }
    void set_date(dateType date1)
    {
        date_of_birth = date1;
    }
    void set_name(string name2)
    {
        *name = name2;
    }
    void set_rollNum(int roll2)
    {
        *roll_num = roll2;
    }
    void set_marks(int mark2)
    {
        *marks = mark2;
    }
    void set_grade(char grade2)
    {
        *grade = grade2;
    }
    string get_name()
    {
        return *name;
    }
    int get_rollNum()
    {
        return *roll_num;
    }
    int get_marks()
    {
        return *marks;
    }
    char get_grade()
    {
        return *grade;
    }
    char grade_calculation()
    {
        int mark1;
        char grade1;
        
        mark1 = get_marks();
        if (mark1 > 89)
        {
            grade1 = 'Z';
        }
        else if (mark1 > 79 && mark1 <= 89)
        {
            grade1 = 'A';
        }
        else if (mark1 > 69 && mark1 <= 79)
        {
            grade1 = 'B';
        }
        else if (mark1 > 59 && mark1 <= 69)
        {
            grade1 = 'C';
        }
        else if (mark1 > 49 && mark1 <= 59)
        {
            grade1 = 'D';
        }
        else
        {
            grade1 = 'F';
        }
        set_grade(grade1);
        return get_grade();
    }
    void print_onedetail()
    {
        if (get_grade() == 'Z')
        {
            cout << "Student " << get_rollNum() << " has date of birth ";
            date_of_birth.printDate();
             cout << " and got " << get_marks() << " Marks and his Grade is A+" << endl;
        }
        else
        {
            cout << "Student " << get_rollNum() << " has date of birth ";
            date_of_birth.printDate();
            cout << " and got "<<get_marks() << " Marks and his grade is " << get_grade() << endl;
        }
    }
    void print_details(student details[10])
    {
        for (int i = 0; i <10; i++)
        {
            details[i].grade_calculation();
            if (details[i].get_grade() == 'Z')
            {
                cout << "Student " << details[i].get_rollNum() << " has " << details[i].get_marks() << " Marks and got A+ Grade" << endl;

            }
            else
            {
            cout << "Student " << details[i].get_rollNum() << " has " << details[i].get_marks() << " Marks and got " << details[i].get_grade() << " Grade" << endl;
            }
        }
        cout << endl;
    }
    void random_rollNum(student arr[10])
    {
        int arr1[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
        for(int i = 0; i < 10; i++)
        {
            do{
                int r = 0;
                r = (rand()% 20) + 1;
                int check = arr1[r-1];
                if (check == r)
                {
                    arr[i].set_rollNum(r);
                    arr1[r-1] = 0;
                    break;
                }
                else if (check != r)
                {
                    continue;
                }
            } while (true);
        }
    }
    int random_marks()
    {
       int a = 20;
        int b = 95;
        int random_num;
        random_num = rand()% (b - a + 1) + a;
        set_marks(random_num);
        return get_marks();
    }
    void desired_student(student arr[10], int *num)
    {
        int counter = 1;
        for (int i = 0; i < 10; i++)
        {
            if (arr[i].get_rollNum() == *num)
            {
                cout << "The student with the roll number " << *num << " is " << arr[i].get_name() << endl;
                cout << endl;
            }
            else if (arr[i].get_rollNum() != *num)
            {
                counter ++;
            }
        }
        if (counter == 11)
        {
            cout << "None of the students has the entered roll number." << endl;
            cout << endl;
        }
    }

    void highest_score(student arr[10])
    {
        int max = 0;
        for ( int i = 0; i < 10 ; i++)
        {
            if (arr[i].get_marks() > max)
            {
                max = arr[i].get_marks();
            }
        }
        for ( int i = 0; i < 10 ; i++)
              {
                  if (arr[i].get_marks() == max)
                  {
                      arr[i].print_onedetail();
                  }
              }
        cout << endl;
    }
    double average_result(student arr[10])
    {
        double average;
        int sum = 0;
        for ( int i = 0; i < 10 ; i++)
            {
                    sum = sum + arr[i].get_marks();
            }
        average = sum / 10;
        return average;
    }
    void set_dateob(student arr[10])
    {
        string name;
        int d,m,y;
        cout << "The name of the students is as follows :" << endl;
        for (int i = 0; i < 10; i++)
        {
        cout << arr[i].get_name() << endl;
        }
        cout << endl;
        cout << "Enter the name of the student whose date of birth you would like to change :";
        cin >>name;
        cout << endl;
        for (int i = 0; i < 10; i++)
        {
            if (arr[i].get_name()==name)
            {
                cout << "Enter the new date of birth" << endl;
                cout << "Day: ";
                cin>>d;
                cout << "Month: ";
                cin >>m;
                cout << "Year: ";
                cin >>y;
                cout<<endl;
                arr[i].date_of_birth.setDate(d,m,y);
                arr[i].date_of_birth.printDate();
                cout << endl;
                cout << endl;
                break;
            }
        }
    }
};

int main_function()
{
    int command;
    cout << "Press 1 To view the name of the student with a certain roll number." << endl;
    cout << "Press 2 To view the details of the students with the highest score." << endl;
    cout << "Press 3 to view the mean average of the class." << endl;
    cout << "Press 4 to change the date of birth of a student." << endl;
    cout << "Press 5 to view details of all the students." << endl;
    cout << "Press 0 to exit." << endl;
    cin >> command;
    cout << endl;
    return command;
}

int main()
{
    srand(static_cast<unsigned int>(time(NULL)));

    student s_arr[10];
    student *ptr1 = &s_arr[0];
    student *ptr2 = &s_arr[1];
    student *ptr3 = &s_arr[2];
    student *ptr4 = &s_arr[3];
    student *ptr5 = &s_arr[4];
    student *ptr6 = &s_arr[5];
    student *ptr7 = &s_arr[6];
    student *ptr8 = &s_arr[7];
    student *ptr9 = &s_arr[8];
    student *ptr10 = &s_arr[9];
    s_arr[10].random_rollNum(s_arr);

    dateType a;
    a.setDate(1, 12, 1998);
    ptr1->set_date(a);
    ptr1->set_name("Daniyal");
    ptr1->random_marks();

    dateType b;
    b.setDate(2, 1, 1998);
    ptr2->set_date(b);
    ptr2->set_name("Bilal");
    ptr2->random_marks();

    dateType c;
    c.setDate(3, 2, 1998);
    ptr3->set_date(c);
    ptr3->set_name("Ali");
    ptr3->random_marks();

    dateType d;
    d.setDate(4, 3, 1998);
    ptr4->set_date(d);
    ptr4->set_name("Dansih");
    ptr4->random_marks();

    dateType e;
    e.setDate(5, 4, 1998);
    ptr5->set_date(e);
    ptr5->set_name("Minahil");
    ptr5->random_marks();

    dateType f;
    f.setDate(6, 5, 1998);
    ptr6->set_date(f);
    ptr6->set_name("Zahra");
    ptr6->random_marks();

    dateType g;
    g.setDate(7, 6, 1998);
    ptr7->set_date(g);
    ptr7->set_name("Tanveer");
    ptr7->random_marks();

    dateType h;
    h.setDate(8, 7, 1998);
    ptr8->set_date(h);
    ptr8->set_name("Sakina");
    ptr8->random_marks();

    dateType i;
    i.setDate(9, 8, 1998);
    ptr9->set_date(i);
    ptr9->set_name("Aimen");
    ptr9->random_marks();

    dateType j;
    j.setDate(10, 9, 1998);
    ptr10->set_date(j);
    ptr10->set_name("Fatimah");
    ptr10->random_marks();
    
   
    int decision;
    do {
        decision = main_function();
        if (decision == 1)
        {
            int rollNum;
            cout << "Enter roll number" << endl;
            cin >> rollNum;
            s_arr[10].desired_student(s_arr,&rollNum);
        }
        else if (decision == 2)
        {
            s_arr[10].highest_score(s_arr);
        }
        else if (decision == 3)
        {
            cout << "The mean of the class is " << s_arr[10].average_result(s_arr) << "." << endl;
            cout << endl;
        }
        else if (decision == 4)
        {
            s_arr[10].set_dateob(s_arr);
        }
        else if (decision == 5)
        {
            s_arr[10].print_details(s_arr);
        }
        } while (decision != 0);
    
    return 0;
}

