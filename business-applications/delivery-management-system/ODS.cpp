/*
 PROJECT #3
 ONLINE DEPARTMENTAL STORE
 PROJECT MADE BY:
 1. HAREEM RAZA                 22100277
 2. TAHA ASIM                   22100264
 3. SYED MUHAMMAD DANIYAL ZAIDI 22100238
 */
#include <iostream>               // For Input/Output
#include <string>              // For string functions
#include <fstream>             // For file reading
#include <vector>              // For functions related to vectors
#include <time.h>               // For time function (For Random Number Seeding)
#include <stdlib.h>               // For Rand Generation
#include <cstdio>               // For Remove and other file related functions

using namespace std;

// Person class with a single member (Name of the person)
// This class serves as a parent (base) class for 3 more classes defined below
class Person
{
private:
    string name;

public:
    // Default Constructor
    Person()
    {
        name = "";
    }
    // Parametrized    Constructor
    Person(string n)
    {
        name = n;
    }
    // Setter
    void setName(string n)
    {
        name = n;
    }
    // Getter
    string getName()
    {
        return name;
    }
    // Print function
    void Printperson()
    {
        cout << "Name: " << name << endl;
    }
};

// Customers class which inherits publically from person class
class  Customers :public Person
{
private:
    string password;
    string dateofarrival;

public:
    // Default Constructor
    Customers()
    {
        password = "";
        dateofarrival = "";
    }
    // Parametrized Constructor
    Customers(string pass, string doa)
    {
        password = pass;
        dateofarrival = doa;
    }
    // Setter
    void setPassword(string pass)
    {
        password = pass;
    }
    // Getter
    string getPassword()
    {
        return password;
    }
    void setdateofarrival(string DOA)
    {
        dateofarrival = DOA;
    }
    string getdateofarrival()
    {
        return dateofarrival;
    }
    // Print function
    void Printcustomer()
    {
        cout << "Type: Customer" << endl;
        Printperson();
        cout << "Password: " << password << endl;
        cout << "Date of arrival: " << dateofarrival << endl;
    }
};

// Dispatchers class which also inherits publically from person class
// Contains addDispatcherfunction
class Dispatchers :public Person
{
private:
    int id;
    string vehicleNumber;

public:
    // Default Constructor
    vector<Dispatchers>D;

    Dispatchers()
    {
        vehicleNumber = "";
    }
    // Parametrized Constructor
    Dispatchers(string n)
    {
        vehicleNumber = n;
    }
    // Setter
    void setId(int a)
    {
        id = a;
    }
    int getId()
    {
        return id;
    }
    void setVehicleNumber(string n)
    {
        vehicleNumber = n;
    }
    // Getter
    string getVehicleNumber()
    {
        return vehicleNumber;
    }

    // Print function
    void Printdispatchers()
    {
        cout << "Dispatcher";
        Printperson();
        cout << vehicleNumber << endl;
    }
};


class Items
{
private:
    string description;
    int price;
    string type;

public:
    // Default Constructor
    Items()
    {
        description = " ";
        price = 0;
        type = " ";
    }
    // Parametrized Constructor
    Items(string a, int b, string c)
    {
        description = a;
        price = b;
        type = c;
    }
    // Setter
    void setDescription(string a)
    {
        description = a;
    }
    void setPrice(int b)
    {
        price = b;
    }
    void setType(string c)
    {
        type = c;
    }
    // Getter
    string getDescription()
    {
        return description;
    }
    int getPrice()
    {
        return price;
    }
    string getType()
    {
        return type;
    }
    // Print function
    void printItems()
    {
        cout << "Description: " << description << endl;
        cout << "Price: " << price << endl;
        cout << "Type: " << type << endl;
    }
};

// Grocery class which inherits publically from Items class
class Grocery :public Items
{
private:
    string expiryDate;
    string size;

public:
    // Default Constructor
    Grocery* next;

    Grocery()
    {
        expiryDate = " ";
        size = "0";
    }
    // Parametrized Constructor
    Grocery(string a, string b)
    {
        expiryDate = a;
        size = b;
    }
    // Setter
    void setExpiryDate(string a)
    {
        expiryDate = a;
    }
    void setSize(string b)
    {
        size = b;
    }
    // Getter
    string getExpiryDate()
    {
        return expiryDate;
    }
    string getSize()
    {
        return size;
    }
    // Print function
    void printGrocery()
    {
        printItems();
        cout << "Expiry Date: " << expiryDate << endl;
        cout << "Size: " << size << endl;
    }
};

// Crockery class which inherits publically from Items class
class Crockery : public Items
{
private:
    string color;
    string material;

public:
    Crockery* next;
    // Default Constructor
    Crockery()
    {
        color = " ";
        material = " ";
    }
    // Paramterized Constructor
    Crockery(string a, string b)
    {
        color = a;
        material = b;
    }
    // Setters
    void setColor(string a)
    {
        color = a;
    }
    void setMaterial(string b)
    {
        material = b;
    }
    // Getters
    string getColor()
    {
        return color;
    }
    string getMaterial()
    {
        return material;
    }
    // Print function
    void printCrockery()
    {
        printItems();
        cout << "Color: " << color << endl;
        cout << "Material: " << material << endl;
    }
};
// Medicine class which inherits publically from Items class
class Medicine :public Items
{
private:
    string expiryDate;
    string potency;

public:
    Medicine* next;
    // Default Constructor
    Medicine()
    {
        expiryDate = " ";
        potency = "0";
    }
    // Paramterized Constructor
    Medicine(string a, string b)
    {
        expiryDate = a;
        potency = b;
    }
    // Setter
    void setExpiryDate(string a)
    {
        expiryDate = a;
    }
    void setPotency(string b)
    {
        potency = b;
    }
    // Getters
    string getExpiryDate()
    {
        return expiryDate;
    }
    string getPotency()
    {
        return potency;
    }
    // Print function
    void printMedicine()
    {
        printItems();
        cout << "Expiry Date: " << expiryDate << endl;
        cout << "Potency: " << potency << " mg" << endl;
    }
};

class listGrocery
{
private:
    Grocery* head;
public:
    listGrocery()
    {
        //set the head pointer to null
        head = NULL;
    }

    void print()
    {
        Grocery* temp = head;
        int counter = 1;
        while (temp != NULL)
        {
            cout << counter << " Item Grocery " << temp->getType() << " " << temp->getExpiryDate() << " " << temp->getSize() << endl;
            temp = temp->next;
            counter++;
        }
        cout << endl;
    }

    ~listGrocery()
    {
        //Destructor that deletes every element in the list and then removes head also
        if (head == NULL)
            return;
        Grocery* curr = head;
        Grocery* prev = NULL;
        while (curr != NULL)
        {
            prev = curr;
            curr = curr->next;
            delete prev;
        }
        head = NULL;
    }

    void Insert(int counter)
    {
        string expDate;
        string siz;
        string name;
        int p;

        cout << "Enter Grocery Name: ";
        cin >> name;
        cout << "Enter Expiry Date: ";
        cin >> expDate;
        cout << "Enter Size: ";
        cin >> siz;
        cout << "Enter price: ";
        cin >> p;

        if (head == NULL)
        {
            head = new Grocery;
            head->next = NULL;
            head->setType(name);
            head->setExpiryDate(expDate);
            head->setSize(siz);
            head->setPrice(p);

            // File handling (Inserting in file)
            fstream hfile("Store.txt", fstream::app);
            hfile << counter << " Item " << name << " Grocery " << expDate << " " << siz << " " << p << endl;
            hfile.close();
        }

        else
        {
            Grocery* temp = new Grocery;
            temp = head;

            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = new Grocery;
            temp->next->setExpiryDate(expDate);
            temp->next->setSize(siz);
            temp->next->setType(name);
            temp->next->setPrice(p);
            temp->next->next = NULL;

            // File handling (Inserting in file)
            fstream hfile("Store.txt", fstream::app);
            hfile << counter << " Item " << name << " Grocery " << expDate << " " << siz << " " << p << endl;
            hfile.close();
        }
    }

    void Insert(string s1)
    {
        fstream hfile;
        hfile.open(s1);
        string s;
        while (getline(hfile, s))
        {
            for (int i = 0; i < s.length(); i++)
            {
                if (s.substr(i, 2) == "Gr")
                {
                    string expDate;
                    string siz;
                    string name;
                    int p = 0;

                    int sub = 0;
                    int sub2 = 0;
                    int sub3 = 0;
                    int sub4 = 0;
                    for (int j = 7; j < s.length(); j++)
                    {
                        if (s[j] == ' ')
                        {
                            sub = j;
                            break;
                        }
                    }
                    name = s.substr(7, sub - 7);

                    int counterDate = 0;
                    int newSub = i + 8;
                    for (newSub; newSub < s.length(); newSub++)
                    {
                        if (s[newSub] == ' ')
                        {
                            sub2 = newSub;
                            break;
                        }
                        counterDate++;
                    }
                    expDate = s.substr(newSub - counterDate, counterDate);

                    int c = 0;
                    int newSub2 = newSub + 1;
                    for (newSub2; newSub2 < s.length(); newSub2++)
                    {
                        if (s[newSub2] == ' ')
                        {
                            sub3 = newSub2;
                            break;
                        }
                        c++;
                    }
                    siz = s.substr(newSub2 - c, c);

                    int newSub3 = newSub2 + 1;

                    p = stoi(s.substr(newSub3));

                    if (head == NULL)
                    {
                        head = new Grocery;
                        head->next = NULL;
                        head->setType(name);
                        head->setExpiryDate(expDate);
                        head->setSize(siz);
                        head->setPrice(p);
                    }

                    else
                    {
                        Grocery* temp = new Grocery;
                        temp = head;

                        while (temp->next != NULL)
                        {
                            temp = temp->next;
                        }
                        temp->next = new Grocery;
                        temp->next->setExpiryDate(expDate);
                        temp->next->setSize(siz);
                        temp->next->setType(name);
                        temp->next->setPrice(p);
                        temp->next->next = NULL;
                    }
                }
            }
        }
        hfile.close();
    }

    void deleteNode(string s)
    {
        Grocery* ptr = NULL;
        Grocery* temp = head;

        while (temp)
        {
            if (temp->getType() == s)
            {
                ptr = temp;
                break;
            }
            else
            {
                temp = temp->next;
            }
        }

        if (ptr == NULL)
        {
            cout << "not found ... " << endl;
        }
        else
        {
            if (ptr == head) { // first node is to be deleted
                head = head->next;
                delete ptr;
            }
            else { // node to deleted is an intermediate or last node
                Grocery* ptr1 = head;
                while (ptr1->next != ptr) {
                    ptr1 = ptr1->next;
                }
                ptr1->next = ptr->next;
                delete ptr;
            }
        }

        fstream tempf;
        tempf.open("Temp.txt", fstream::app);
        fstream hfile;
        hfile.open("Store.txt");
        string s1;
        while (getline(hfile, s1))
        {
            int counter = 0;
            for (int i = 0; i < s1.length(); i++)
            {
                if ((s1.substr(i, 2) == "It") && (s1.substr(i + 5, 2) == s.substr(0, 2)))
                {
                    counter++;
                    break;
                }
            }
            if (counter == 0)
            {
                tempf << s1 << endl;
            }
        }
        tempf.close();
        hfile.close();
        remove("Store.txt");

        hfile.open("Store.txt", fstream::out | fstream::trunc);
        tempf.open("Temp.txt");
        string s2;
        while (getline(tempf, s2))
        {
            hfile << s2 << endl;
        }
        hfile.close();
        tempf.close();
        remove("Temp.txt");
    }

    Grocery* getHead()
    {
        return head;
    }

};

class listCrockery
{
private:
    Crockery* head;
public:
    listCrockery()
    {
        //set the head pointer to null
        head = NULL;
    }

    void print()
    {
        Crockery* temp = head;
        int counter = 1;
        while (temp != NULL)
        {
            cout << counter << " Item Crockery " << temp->getType() << " " << temp->getMaterial() << " " << temp->getColor() << endl;
            temp = temp->next;
            counter++;
        }
        cout << endl;
    }

    ~listCrockery()
    {
        //Destructor that deletes every element in the list and then removes head also
        if (head == NULL)
            return;
        Crockery* curr = head;
        Crockery* prev = NULL;
        while (curr != NULL)
        {
            prev = curr;
            curr = curr->next;
            delete prev;
        }
        head = NULL;
    }

    void Insert(int counter)
    {
        string col;
        string mat;
        string name;
        int p;

        cout << "Enter Crockery Name: ";
        cin >> name;
        cout << "Enter Material: ";
        cin >> mat;
        cout << "Enter the color: ";
        cin >> col;
        cout << "Enter price: ";
        cin >> p;

        if (head == NULL)
        {
            head = new Crockery;
            head->next = NULL;
            head->setMaterial(mat);
            head->setColor(col);
            head->setType(name);
            head->setPrice(p);

            // File handling (Inserting in file)
            fstream hfile("Store.txt", fstream::app);
            hfile << counter << " Item " << name << " Crockery " << mat << " " << col << " " << p << endl;
            hfile.close();
        }

        else
        {
            Crockery* temp = head;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = new Crockery;
            temp->next->setMaterial(mat);
            temp->next->setColor(col);
            temp->next->setType(name);
            temp->next->next = NULL;

            // File handling (Inserting in file)
            fstream hfile("Store.txt", fstream::app);
            hfile << counter << " Item " << name << " Crockery " << mat << " " << col << " " << p << endl;
            hfile.close();
        }
    }

    void Insert(string s1)
    {
        fstream hfile;
        hfile.open(s1);
        string s;
        while (getline(hfile, s))
        {
            for (int i = 0; i < s.length(); i++)
            {
                if (s.substr(i, 3) == "Cro")
                {
                    string col;
                    string mat;
                    string name;
                    int p = 0;
                    int sub = 0;
                    int sub2 = 0;
                    int sub3 = 0;
                    int sub4 = 0;

                    for (int j = 7; j < s.length(); j++)
                    {
                        if (s[j] == ' ')
                        {
                            sub = j;
                            break;
                        }
                    }
                    name = s.substr(7, sub - 7);

                    int newSub = i + 9;
                    int d = 0;
                    for (newSub; newSub < s.length(); newSub++)
                    {
                        if (s[newSub] == ' ')
                        {
                            sub2 = newSub;
                            break;
                        }
                        d++;
                    }
                    mat = s.substr(newSub - d, d);
                    int c = 0;
                    int newSub2 = newSub + 1;
                    for (newSub2; newSub2 < s.length(); newSub2++)
                    {
                        if (s[newSub2] == ' ')
                        {
                            sub3 = newSub2;
                            break;
                        }
                        c++;
                    }
                    col = s.substr(newSub2 - c, c);

                    if (head == NULL)
                    {
                        head = new Crockery;
                        head->next = NULL;
                        head->setMaterial(mat);
                        head->setColor(col);
                        head->setType(name);
                        head->setPrice(p);
                    }

                    else
                    {
                        Crockery* temp = head;
                        while (temp->next != NULL)
                        {
                            temp = temp->next;
                        }
                        temp->next = new Crockery;
                        temp->next->setMaterial(mat);
                        temp->next->setColor(col);
                        temp->next->setType(name);
                        temp->next->setPrice(p);
                        temp->next->next = NULL;
                    }
                }
            }
        }
    }

    void deleteNode(string s)
    {

        Crockery* ptr = NULL;
        Crockery* temp = head;

        while (temp)
        {
            if (temp->getType() == s)
            {
                ptr = temp;
                break;
            }
            else
            {
                temp = temp->next;
            }
        }

        if (ptr == NULL)
        {
        }
        else
        {
            if (ptr == head) {
                head = head->next;
                delete ptr;
            }
            else {
                Crockery* ptr1 = head;
                while (ptr1->next != ptr) {
                    ptr1 = ptr1->next;
                }
                ptr1->next = ptr->next;
                delete ptr;
            }
        }

        fstream tempf;
        tempf.open("Temp.txt", fstream::app);
        fstream hfile;
        hfile.open("Store.txt");
        string s1;
        while (getline(hfile, s1))
        {
            int counter = 0;
            for (int i = 0; i < s1.length(); i++)
            {
                if ((s1.substr(i, 2) == "It" && s1.substr(i + 5, 2) == s.substr(0, 2)))
                {
                    counter++;
                }
            }
            if (counter == 0)
            {
                tempf << s1 << endl;
            }
        }
        tempf.close();
        hfile.close();
        remove("Store.txt");

        hfile.open("Store.txt", fstream::out | fstream::trunc);
        tempf.open("Temp.txt");
        string s2;
        while (getline(tempf, s2))
        {
            hfile << s2 << endl;
        }
        hfile.close();
        tempf.close();
        remove("Temp.txt");
    }
};

class listMedicine
{

private:
    Medicine* head;
public:
    listMedicine()
    {
        //set the head pointer to null
        head = NULL;
    }

    void print()
    {
        Medicine* temp = head;
        int counter = 1;
        while (temp != NULL)
        {
            cout << counter << " Item Medicine " << temp->getType() << " " << temp->getExpiryDate() << " " << temp->getPotency() << " " << temp->getPrice() << endl;
            temp = temp->next;
            counter++;
        }
        cout << endl;
    }

    ~listMedicine()
    {
        //Destructor that deletes every element in the list and then removes head also
        if (head == NULL)
            return;
        Medicine* curr = head;
        Medicine* prev = NULL;
        while (curr != NULL)
        {
            prev = curr;
            curr = curr->next;
            delete prev;
        }
        head = NULL;
    }

    void Insert(int counter)
    {
        string expDate;
        string pot;
        string name;
        int p;

        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter the potency: ";
        cin >> pot;
        cout << "Enter the expiry date: ";
        cin >> expDate;
        cout << "Enter Price: ";
        cin >> p;

        if (head == NULL)
        {
            head = new Medicine;
            head->next = NULL;
            head->setPotency(pot);
            head->setExpiryDate(expDate);
            head->setType(name);
            head->setPrice(p);

            // File handling (Inserting in file)
            fstream hfile("Store.txt", fstream::app);
            hfile << counter << " Item " << name << " Medicine " << expDate << " " << pot << " " << p << endl;
            hfile.close();
        }
        else
        {
            Medicine* temp = head;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = new Medicine;
            temp->next->setPotency(pot);
            temp->next->setExpiryDate(expDate);
            temp->next->setType(name);
            temp->next->setPrice(p);
            temp->next->next = NULL;

            // File handling (Inserting in file)
            fstream hfile("Store.txt", fstream::app);
            hfile << counter << " Item " << name << " Medicine " << expDate << " " << pot << " " << p << endl;
            hfile.close();
        }
    }

    void Insert(string s)
    {
        fstream hfile;
        hfile.open(s);
        while (getline(hfile, s))
        {
            for (int i = 0; i < s.length(); i++)
            {
                if (s.substr(i, 4) == "Medi")
                {
                    string expDate;
                    string pot = "0";
                    string name;
                    int p = 0;

                    int sub = 0;
                    int sub2 = 0;
                    int sub3 = 0;
                    int sub4 = 0;

                    for (int j = 7; j < s.length(); j++)
                    {
                        if (s[j] == ' ')
                        {
                            sub = j;
                            break;
                        }
                    }
                    name = s.substr(7, sub - 7);

                    int newSub = i + 9;
                    int count1 = 0;
                    for (newSub; newSub < s.length(); newSub++)
                    {
                        if (s[newSub] == ' ')
                        {
                            sub2 = newSub;
                            break;
                        }
                        count1++;
                    }
                    expDate = s.substr(newSub - count1, count1);

                    int count2 = 0;
                    int newSub2 = newSub + 1;
                    for (newSub2; newSub2 < s.length(); newSub2++)
                    {
                        if (s[newSub2] == ' ')
                        {
                            sub3 = newSub2;
                            break;
                        }
                        count2++;
                    }
                    pot = s.substr(newSub2 - count2, count2);

                    int count3 = 0;
                    int newSub3 = newSub2 + 1;
                    for (newSub3; newSub3 < s.length(); newSub3++)
                    {
                        if (s[newSub3] == ' ')
                        {
                            sub4 = newSub3;
                            break;
                        }
                        count3++;
                    }

                    p = stoi(s.substr(newSub3 - count3));

                    if (head == NULL)
                    {
                        head = new Medicine;
                        head->next = NULL;
                        head->setPotency(pot);
                        head->setExpiryDate(expDate);
                        head->setType(name);
                        head->setPrice(p);
                    }
                    else
                    {
                        Medicine* temp = head;
                        while (temp->next != NULL)
                        {
                            temp = temp->next;
                        }
                        temp->next = new Medicine;
                        temp->next->setPotency(pot);
                        temp->next->setExpiryDate(expDate);
                        temp->next->setType(name);
                        temp->next->setPrice(p);
                        temp->next->next = NULL;
                    }
                }
            }
        }
    }

    void deleteNode(string s)
    {
        Medicine* ptr = NULL;
        Medicine* temp = head;

        while (temp)
        {
            if (temp->getType() == s)
            {
                ptr = temp;
                break;
            }
            else
            {
                temp = temp->next;
            }
        }

        if (ptr == NULL)
        {
        }
        else
        {
            if (ptr == head) { // first node is to be deleted
                head = head->next;
                delete ptr;
            }
            else { // node to deleted is an intermediate or last node
                Medicine* ptr1 = head;
                while (ptr1->next != ptr) {
                    ptr1 = ptr1->next;
                }
                ptr1->next = ptr->next;
                delete ptr;
            }
        }

        fstream tempf;
        tempf.open("Temp.txt", fstream::app);
        fstream hfile;
        hfile.open("Store.txt");
        string s1;
        while (getline(hfile, s1))
        {
            int counter = 0;
            for (int i = 0; i < s1.length(); i++)
            {
                if ((s1.substr(i, 2) == "It" && s1.substr(i + 5, 2) == s.substr(0, 2)))
                {
                    counter++;
                }
            }
            if (counter == 0)
            {
                tempf << s1 << endl;
            }
        }
        tempf.close();
        hfile.close();
        remove("Store.txt");

        hfile.open("Store.txt", fstream::out | fstream::trunc);
        tempf.open("Temp.txt");
        string s2;
        while (getline(tempf, s2))
        {
            hfile << s2 << endl;
        }
        hfile.close();
        tempf.close();
        remove("Temp.txt");
    }

};

class Orders
{
private:
    int customerid;
    int dispatcherid;
    vector<int>items;
    string orderdate;

public:
    // Default Constructor
    Orders()
    {
        customerid = 0;
        dispatcherid = 0;
        items.clear();
        orderdate = "";
    }
    // Parametrized Constructor
    Orders(int a, int b, string c)
    {
        customerid = a;
        dispatcherid = b;
        orderdate = c;
    }
    // Setters
    void setCustomerid(int a)
    {
        customerid = a;
    }
    void setDispatcherid(int b)
    {
        dispatcherid = b;
    }
    void setOrderdate(string c)
    {
        orderdate = c;
    }
    void setItems(vector<int>x)
    {
        items = x;
    }
    // Getters
    int getCustomer_id()
    {
        return customerid;
    }
    int getDispatcher_id()
    {
        return dispatcherid;
    }
    string getOrderdate()
    {
        return orderdate;
    }
    vector<int> getItems()
    {
        return items;
    }
    void printo()
    {
        vector<int>temp = getItems();
        cout << "Order " << getCustomer_id() << " " << getDispatcher_id() << " " << getOrderdate() << " ";
        for (int i = 0; i < getItems().size(); i++)
        {
            cout << temp[i] << " ";
        }
        temp.clear();
    }
};

// Main Class for onlinedepartalstore
class Onlinedepartmentalstore
{
private:
    // Pointer to person, order, items class
    Person* ptrperson;
    Orders* ptrorders;
    Items* ptritems;

public:
    // Constructor
    Onlinedepartmentalstore()
    {
        ptrperson = new Person;
        ptrorders = new Orders;
        ptritems = new Items;
    }

    // Destructor
    ~Onlinedepartmentalstore()
    {
        delete ptrperson;
        delete ptrorders;
        delete ptritems;
    }
};

// A bool function to compare date of grocery to  current date and check if expired
// Isexpired (EXPIRY DATE, CURRENT DATE)
bool isExpired(string date, string d)
{
    // Extracting days and months from string (No need for year) and converting to int
    int old_day = stoi(date.substr(0, 2));
    int old_month = stoi(date.substr(3, 2));
    int curr_day = stoi(d.substr(0, 2));
    int curr_month = stoi(d.substr(3, 2));

    if (old_month < curr_month)
    {
        // Expired
        return true;
    }

    if (old_day <= curr_day && old_month == curr_month)
    {
        // Expired
        return true;
    }
    // Not expired
    return false;
}

class customerqueue
{
private:
    vector<Customers>arr;            // Vector of type Customer
    int capacity;                    // Customer Capacity of Store
public:
    // Default Constructor
    customerqueue()
    {
        capacity = 100;
        arr.clear();
    }
    // Parametrized Constructor
    customerqueue(int size)
    {
        arr.resize(size);
        capacity = size;
    }
    // Destructor
    ~customerqueue()
    {
        // Clearing the queue
        arr.clear();
    }
    // Remove Customer (First in First out)
    Customers dequeue()
    {
        Customers curr_cus = arr[0];
        //Remove the first element from the vector
        arr.erase(arr.begin());
        return curr_cus;
    }
    void dequeueFile()
    {
        string s;
        s = arr[0].getName();
        string s2;
        fstream hfile;
        hfile.open("Store.txt");
        fstream tempf;
        tempf.open("Temp.txt", fstream::app);
        while (getline(hfile, s2))
        {
            int counter = 0;
            for (int i = 0; i < s2.length(); i++)
            {
                if ((s2.substr(i, 2) == s.substr(0, 2)))
                {
                    counter++;
                    break;
                }
            }
            if (counter == 0)
            {
                tempf << s2 << endl;
            }
        }
        tempf.close();
        hfile.close();
        remove("Store.txt");

        hfile.open("Store.txt", fstream::out | fstream::trunc);
        tempf.open("Temp.txt");
        string s3;
        while (getline(tempf, s3))
        {
            hfile << s3 << endl;
        }
        hfile.close();
        tempf.close();
        remove("Temp.txt");
    }

    // Add Customer to queue
    void enqueue(Customers cu)
    {
        // Inserting customer in queue
        arr.push_back(cu);
        // Inserting customer in file
    }
    void enqueuefile(Customers cu)
    {
        fstream hfile;
        hfile.open("Store.txt", fstream::app);
        hfile << arr.size() << " Customer " << cu.getName() << " " << cu.getPassword() << " " << cu.getdateofarrival() << endl;
        hfile.close();
    }
    int size()
    {
        return arr.size();
    }
    bool isEmpty()
    {
        return (size() == 0);
    }
    bool isFull()
    {
        return (size() == capacity);
    }
    string search(string s)
    {
        for (int i = 0; i < arr.size(); i++)
        {
            if (arr[i].getName() == s)
            {
                return arr[i].getPassword();
            }
            else
            {
                break;
            }
        }                return "0";

    }
};

// Admin class which also inherits publically from person class
// BONUS: Admin class implemented in Singleton pattern (So that only 1 admin exists)
class Admin :public Person
{
private:
    static Admin* obj;
    string password;
    Admin()
    {
        password = "";
    }
    ~Admin()
    {
        delete obj;
    }
public:
    // Only one thread can execute this at a time
    static Admin* getObj()
    {
        if (obj == NULL)
            obj = new Admin();
        return obj;
    }
    // Setter
    void setPassword(string pass)
    {
        password = pass;
    }
    // Getter
    string getPassword()
    {
        return password;
    }
    // Print Function
    void Printadmin()
    {
        cout << "Type: Admin" << endl;
        Printperson();
        cout << "Password: " << password << endl;
    }

    // Admin Signup. (Signupcheck -> Username password input -> Password Check -> Storing Info In File)
    void signup()
    {
        fstream hfile;
        hfile.open("Store.txt", fstream::app);
        cout << "Enter Admin Name: " << endl;
        string s1, s2;
        getline(cin, s1);
        cout << endl;
        cout << "PASSWORD REQUIRMENTS: " << endl;
        cout << "1. Password should not have less than eight characters." << endl;
        cout << "2. Password should be Alphanumeric i.e it should have atleast one Digit, one Uppercase and one Lowercase letter." << endl;
        cout << endl;
        do
        {
            cout << "Enter Admin Password: " << endl;
            getline(cin, s2);
        } while (!checkPassword(s2));
        cout << "Sign Up Successful" << endl;
        string s;
        hfile << "Admin " << s1 << " " << s2 << endl;
        hfile.close();

        //string s;
        hfile.open("Store.txt");
        while (getline(hfile, s))
        {
            int sub = 0;
            {
                if (s.substr(0, 5) == "Admin")
                {
                    for (int i = 6; i < s.length(); i++)
                    {
                        if (s[i] == ' ')
                        {
                            sub = i;
                            i = s.length();
                        }
                    }
                    setName(s.substr(6, sub - 6));
                    setPassword(s.substr(sub + 1, s.length() - sub));
                }
            }
        }
        hfile.close();
    }

    // Loading Admin From File If Present
    // 1: Admin Found
    // 0: Indication For Sign Up
    bool checksignin()
    {
        string s;
        fstream hfile;
        hfile.open("Store.txt");
        int count = 0;
        while (getline(hfile, s))
        {
            int sub = 0;
            {
                if (s.substr(0, 5) == "Admin")
                {
                    for (int i = 6; i < s.length(); i++)
                    {
                        if (s[i] == ' ')
                        {
                            sub = i;
                            i = s.length();
                        }
                    }
                    setName(s.substr(6, sub - 6));
                    setPassword(s.substr(sub + 1, s.length() - sub));
                    count++;
                }
            }
        }
        hfile.close();
        return count;
    }

    // Password Check Required For User And Admin Signup
    bool checkPassword(string s)
    {
        bool check1 = false;
        bool check2 = false;
        bool check3 = false;
        int len = s.length();
        if (len < 8)
        {
            cout << "Password requirements not met." << endl;
            return false;
        }
        for (int i = 0; i < len; i++)
        {
            for (int num = 48; num <= 57; num++)
            {
                if (s[i] == num)
                {
                    check1 = true;
                    break;
                }
            }
            for (int caps = 65; caps <= 90; caps++)
            {
                if (s[i] == caps)
                {
                    check2 = true;
                    break;
                }
            }
            for (int caps = 97; caps <= 122; caps++)
            {
                if (s[i] == caps)
                {
                    check3 = true;
                    break;
                }
            }
        }
        if (check1 && check2 && check3)
        {
            return true;
        }
        else
        {
            cout << "Password requirements not met." << endl;
        }
        return false;
    }

    // Instances of Lists and Queues
    listCrockery lc;
    listGrocery lg;
    listMedicine lm;
    Dispatchers Disp;
    customerqueue customerq;
    vector<Orders>order;

    void insertOrder(string s)
    {
        fstream hfile;
        hfile.open(s);
        string s1;
        while (getline(hfile, s1))
        {
            int a, b;
            string c;
            vector<int>d;
            Orders tempo;
            for (int i = 0; i < s1.length(); i++)
            {
                if (s1.substr(i, 2) == "Or")
                {
                    a = s1[8] - 48;
                    b = s1[10] - 48;
                    c = s1.substr(12, 8);
                    for (int j = 21; j < s1.length(); j++)
                    {
                        if (s1[j] != ' ')
                        {
                            int temp = s1[j] - 48;
                            d.push_back(temp);
                        }
                    }
                    tempo.setCustomerid(a);
                    tempo.setDispatcherid(b);
                    tempo.setOrderdate(c);
                    tempo.setItems(d);
                    order.push_back(tempo);
                    break;
                }
            }
        }
        hfile.close();
    }

    void viewOrders()
    {
        for (int i = 0; i < order.size(); i++)
        {
            order[i].printo();
            cout << endl;
        }
    }

    // Inserting Items to store (By insertion in respective list)
    void insertItems()
    {
        int counter = 0;
        string itemType;
        cout << "What Do You Want To Add? (Grocery/Crockery/Medicine)" << endl;
        cin >> itemType;
        string s;
        fstream hfile;
        hfile.open("Store.txt");
        while (getline(hfile, s))
        {
            for (int i = 0; i < s.length(); i++)
            {
                if (s.substr(i, 4) == "Item")
                {
                    counter = stoi(s.substr(0, 1));
                }
            }
        }
        if (itemType == "Grocery" || itemType == "grocery")
        {
            counter++;
            cout << "INSERTING GROCERY" << endl;
            lg.Insert(counter);
        }
        else if (itemType == "Crockery" || itemType == "crockery")
        {
            counter++;
            cout << "INSERTING CROCKERY" << endl;
            lc.Insert(counter);
        }
        else if (itemType == "Medicine" || itemType == "medicine")
        {
            counter++;
            cout << "INSERTING MEDICINE" << endl;
            lm.Insert(counter);
        }
        else
        {
            cout << "Item Does Not Exist In The Store" << endl;
        }
        hfile.close();
    }

    // Loading Dispatcher Info from file.
    void Insert(string s)
    {
        string id;
        fstream hfile;
        hfile.open(s);
        string s1;
        while (getline(hfile, s1))
        {
            Dispatchers temp;
            for (int i = 0; i < s1.length(); i++)
            {
                if (s1.substr(i, 2) == "Di")
                {
                    int sub = 0;
                    for (int i = 13; i < s1.length(); i++)
                    {
                        if (s1[i] == ' ')
                        {
                            sub = i;
                            i = s1.length();
                        }
                    }
                    temp.setName(s1.substr(13, sub - 13));
                    temp.setVehicleNumber(s1.substr(sub + 1));
                    id = s1.substr(0, 1);
                    Disp.D.push_back(temp);
                }
            }
        }
        hfile.close();
    }

    // Adding Dispatchers Using Vectors
    void addDispatcher()
    {
        vector<string>d1;
        vector<string>d2;
        fstream hfile;
        hfile.open("Store.txt");
        string s1;

        while (getline(hfile, s1))
        {
            for (int i = 0; i < s1.length(); i++)
            {
                if (s1.substr(i, 3) == "Dis")
                {
                    int sub = 0;
                    for (int j = 13; j < s1.length(); j++)
                    {
                        if (s1[j] == ' ')
                        {
                            sub = j;
                            j = s1.length();
                        }
                    }
                    d1.push_back(s1.substr(13, sub - 13));
                    d2.push_back(s1.substr(sub + 1));
                }
            }
        }
        hfile.close();
        hfile.open("Store.txt", fstream::app);
        Dispatchers temp;
        cout << "Enter Dispatcher Name: ";
        string dname;
        cin >> dname;
        d1.push_back(dname);
        temp.setName(dname);

        cout << "Enter Dispatcher Vehicle Number: ";
        string dvnum;
        cin >> dvnum;
        d2.push_back(dvnum);
        temp.setVehicleNumber(dvnum);

        Disp.D.push_back(temp);
        hfile << d1.size() << " Dispatcher" << " " << dname << " " << dvnum << endl;
        hfile.close();
        d1.clear();
        d2.clear();
    }

    // Loading the Customer information from file.
    void Insertq(string s)
    {
        fstream hfile;
        hfile.open(s);
        while (getline(hfile, s))
        {
            string a, b, c;
            int sub = 0;
            int sub2 = 0;
            for (int i = 0; i < s.length(); i++)
            {
                if (s.substr(i, 4) == "Cust")
                {
                    for (int i = 11; i < s.length(); i++)
                    {
                        if (s[i] == ' ')
                        {
                            sub = i;
                            i = s.length();
                        }
                    }
                    a = s.substr(11, sub - 11);
                    for (int i = sub + 1; i < s.length(); i++)
                    {
                        if (s[i] == ' ')
                        {
                            sub2 = i;
                            i = s.length();
                        }
                    }
                    b = s.substr(sub + 1, sub2 - sub - 1);
                    c = s.substr(sub2);
                    Customers temp;
                    temp.setName(a);
                    temp.setPassword(b);
                    temp.setdateofarrival(c);
                    customerq.enqueue(temp);
                }
            }
        }
        hfile.close();
    }

    // Removing expired grocery based on today's date
    void removeExpired()
    {
        Grocery* temp = lg.getHead();
        cout << "Please insert today's date (dd-mm-yy) ";
        string d;
        cin >> d;

        while (temp != NULL)
        {
            if (isExpired(temp->getExpiryDate(), d))
            {
                lg.deleteNode(temp->getType());
                return;
            }
            temp = temp->next;
        }
        delete temp;
    }

    // Printing Store Items
    void printItems()
    {
        cout << "--- ITEMS IN OUR STORE ---" << endl;
        string s;
        fstream hfile;
        hfile.open("Store.txt");
        while (getline(hfile, s))
        {
            for (int i = 0; i < s.length(); i++)
            {
                if (s.substr(i, 2) == "It")
                {
                    cout << s << endl;
                }
            }
        }
        hfile.close();
    }

    // Random Date Generator
    string randDate()
    {
        string s = "";
        int n;
        srand(time(NULL));
        for (int i = 0; i < 3; i++)
        {
            if (i == 0)
            {
                n = rand() % 30 + 1;
                if (n < 10)
                {
                    s = s + '0';
                }
                s = s + to_string(n) + '-';
            }
            else if (i == 1)
            {
                n = rand() % 12 + 1;
                if (n < 10)
                {
                    s = s + '0';
                }
                s = s + to_string(n) + '-';
            }
            else
            {
                s = s + "19";
            }
        }
        return s;
    }

    int bill = 0;

    int randDispatcher()
    {
        fstream hfile;
        hfile.open("Store.txt");
        string s;
        int counter = 0;
        // Counting Dispatchers
        while (getline(hfile, s))
        {
            for (int i = 0; i < s.length(); i++)
            {
                if (s.substr(i, 2) == "Di")
                {
                    counter++;
                }
            }
        }
        // Seeding for random number
        srand(time(0));
        int n = 0;
        if (counter != 0)
        {
            n = (rand() % counter);
        }
        return (n + 1);
    }

    // Adding Customers (Customer SignUp)
    void addCustomers()
    {
        cout << "Enter username: " << endl;
        string name;
        cin >> name;
        cout << "Enter Password: " << endl;
        string pass;
        cin >> pass;
        // PassWird Check (Minimum 8 letters and alphanumeric)
        while (!checkPassword(pass))
        {
            cout << "Invalid Password. Enter again: " << endl;
            cin >> pass;
        }
        // Enqueue the signed up user.
        Customers temp;
        temp.setName(name);
        temp.setPassword(pass);
        temp.setdateofarrival(randDate());
        customerq.enqueue(temp);
        customerq.enqueuefile(temp);
        cout << "Sign Up Successful!" << endl;
    }
    int id = 0;
    void attendCustomers1()
    {
        int counter;
        Customers c = customerq.dequeue();
        id++;
        cout << "Attending Customer " << c.getName() << endl;
        string s;
        cout << "Enter Password: ";
        cin >> s;
        int bill1 = 0;
        vector<int>it;
        if (c.getPassword() == s)
        {
            string date = randDate();
            int dis = randDispatcher();
            while (1)
            {
                fstream hfile;
                hfile.open("Store.txt");
                int x;
                printItems();
                counter = 0;
                cout << "What Do You Want To Purchase?" << endl;
                int n;
                cin >> n;
                string s;
                while (getline(hfile, s))
                {
                    int sub = 0;
                    x = s[0] - 48;
                    if ((x == n) && s.substr(2, 2) == "It")
                    {
                        it.push_back(x);
                        counter++;
                        for (int i = 7; i < s.length(); i++)
                        {
                            if (s[i] == ' ')
                            {
                                sub = i;
                                break;
                            }
                        }
                        string item = s.substr(7, sub - 7);
                        int position;
                        for (int i = s.length() - 1; i > 0; i--)
                        {
                            if (s[i] == ' ')
                            {
                                position = i + 1;
                                break;
                            }
                        }
                        string sub = s.substr(position);
                        int sale = stoi(sub);

                        for (int i = 0; i < s.length(); i++)
                        {
                            if (s.substr(i, 2) == "Gr")
                            {
                                lg.deleteNode(item);
                            }
                            else if (s.substr(i, 2) == "Cr")
                            {
                                lc.deleteNode(item);
                            }
                            else if (s.substr(i, 2) == "Me")
                            {
                                lm.deleteNode(item);
                            }
                        }
                        bill1 = bill1 + sale;
                        bill = bill + sale;
                        hfile.close();
                    }
                }
                if (!counter)
                {
                    cout << "Cannot Purchase Item" << endl;
                }
                else
                {
                    cout << "Purchase Successful!" << endl;
                }
                cout << "Do you want to purchase anything else? (Y/N)" << endl;
                string dec;
                cin >> dec;
                if (dec == "n" || dec == "N")
                {
                    cout << "THANKS FOR SHOPPING. YOUR ORDER HAS SUCCESSFULLY BEEN PLACED!" << endl;
                    cout << "YOUR TOTAL BILL: " << bill1 << endl;
                    cout << "ITEMS PURCHASED (ID): ";
                    for (int k = 0; k < it.size(); k++)
                    {
                        cout << it[k] << " ";
                    }
                    cout << endl << "ORDER ID: " << order.size() + 1 << endl;
                    cout << "DISPATCHER ASSIGNED: " << dis << endl;
                    cout << "DATE OF ARRIVAL: " << date << endl;
                    cout << "--------------------------------------------" << endl;
                    bill1 = 0;
                    Orders temp;

                    temp.setCustomerid(id);
                    temp.setDispatcherid(dis);
                    temp.setOrderdate(date);
                    temp.setItems(it);
                    order.push_back(temp);

                    fstream hfile("Store.txt", fstream::app);
                    hfile << order.size() << " Order " << temp.getCustomer_id() << " " << temp.getDispatcher_id() << " " << temp.getOrderdate() << " ";
                    for (int k = 0; k < it.size(); k++)
                    {
                        hfile << it[k] << " ";
                    }
                    hfile << endl;
                    hfile.close();
                    it.clear();
                    //customerq.dequeueFile();
                    break;
                }
            }
        }
        else
        {
            cout << "Cannot log you in" << endl;
        }
    }

    void attendCustomer()
    {
        int x = customerq.size();
        for (int i = 0; i < x; i++)
        {
            attendCustomers1();
        }
    }
    void viewSale()
    {
        cout << "SALES BEFORE THE DAY: 0" << endl;
        cout << "SALES AFTER THE DAY: " << bill << endl;
    }
};
Admin* Admin::obj = 0;
// Singleton Class Successfully Made

// BONUS: A separate login class. (For admin and customer)
// Function Overloading
class Login
{
private:
    string name;
    string password;
public:
    Login()
    {
        name = "0";
        password = "0";
    }
    Login(Admin* ad)
    {
        name = ad->getName();
        password = ad->getPassword();
    }
    Login(Customers cu)
    {
        name = cu.getName();
        password = cu.getPassword();
    }
    bool login()
    {
        string s1, s2;
        cout << "Enter Username: ";
        cin >> s1;
        cout << "Enter Password: ";
        cin >> s2;
        if (name == s1 && password == s2)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
};

// Loading the already present data onto our linked lists and queues
void loadfile(Admin* ad)
{
    // File to be loaded
    string s = "Store.txt";
    // Loading Grocery List
    ad->lg.Insert(s);
    // Loading Medicine List
    ad->lm.Insert(s);
    // Loading Crockery List
    ad->lc.Insert(s);
    // Laoding Dispatcher
    ad->Insert(s);
    // Loading Customer Queue
    ad->Insertq(s);
    // Loading Orders
    ad->insertOrder(s);
}

// Function declaration of admin menu;
void adminMenu(Admin* ad);

int main()
{
    // Declaring an instance of singleton class in this way
    Admin* admin = admin->getObj();
    // Checking if admin is present in the already existing file
    if (admin->checksignin())
    {
        cout << "Please Login. Enter your credentials." << endl;
    }
    else
    {
        cout << "Dear Admin, Please Signup.  Enter Your credentials." << endl;
        admin->signup();
        system("CLS");
        cout << "Now, Please Sign In." << endl;
    }
    // Using login class to sign in admin
    Login L1(admin);
    // A bool login function in Login class
    if (L1.login())
    {
        loadfile(admin);
        system("CLS");
        //system("color 80");
        cout << "Signin Succesful!" << " Welcome to Online Departmental Store" << endl;
        adminMenu(admin);
    }
    else
    {
        cout << "Signin Failed!" << " Invalid Username/Password" << endl;
    }

}

// Admin Menu which consists of a switch to deal with various cases (Of Admin Class)
void adminMenu(Admin* ad)
{
    cout << "\nADMIN MENU \n" << endl;
    cout << "Press 1 To Insert Items." << endl;
    cout << "Press 2 To Remove Expired Item." << endl;
    cout << "Press 3 To View Store Items." << endl;
    cout << "Press 4 To View Total Sales." << endl;
    cout << "Press 5 To View All Orders made." << endl;
    cout << "Press 6 To Add Customers Details." << endl;
    cout << "Press 7 To Add Dispatchers Details." << endl;
    cout << "Press 8 To Attend Customers." << endl;
    cout << "Press 9 TO Signout" << endl << endl;

    int option;

    cin >> option;
    while (cin.fail())
    {
        cout << endl << "Invalid option " << endl;
        cin.clear();
        string dummy;
        getline(cin, dummy);
        cout << "Enter option again: ";
        cin >> option;
    }
    switch (option)
    {
    case 1:
    {
        system("CLS");
        while (1)
        {
            ad->insertItems();
            cout << "Do you want to insert anything else? (Y/N)" << endl;
            string dec;
            cin >> dec;
            if (dec == "n" || dec == "N")
            {
                break;
            }
        }
    }
    break;
    case 2:
    {
        system("CLS");
        ad->printItems();
        cout << " --- REMOVING EXPIRED ITEMS --- " << endl;
        ad->removeExpired();
        cout << "Expired Items Have Been Removed!" << endl;
    }
    break;
    case 3:
    {
        ad->printItems();
    }
    break;
    case 4:
    {
        system("CLS");
        cout << "--- VIEWING SALE ---" << endl;
        ad->viewSale();
    }
    break;
    case 5:
    {
        system("CLS");
        cout << "--- VIEWING ORDERS ---" << endl;
        ad->viewOrders();
    }
    break;
    case 6:
    {
        system("CLS");
        while (1)
        {
            cout << "--- ADDING CUSTOMER ---" << endl;
            ad->addCustomers();
            cout << "Customer SignUp Successful" << endl;
            cout << "Do You Want To Add Another Customer? (Y/N)" << endl;
            string dec;
            cin >> dec;
            if (dec == "n" || dec == "N")
            {
                break;
            }
        }
    }
    break;
    case 7:
    {
        system("CLS");
        while (1)
        {
            cout << "--- ADDING DISPATCHER DETAILS ---" << endl;
            ad->addDispatcher();
            cout << "Dispatcher Added Successfully!" << endl;
            cout << "Do You Want To Add Another Dispatcher? (Y/N)" << endl;
            string dec;
            cin >> dec;
            if (dec == "n" || dec == "N")
            {
                break;
            }
        };
    }
    break;
    case 8:
    {
        system("CLS");
        cout << " --- ATTENDING CUSTOMERS --- " << endl;
        ad->attendCustomer();
    }
    break;
    case 9:
    {
        system("CLS");
        cout << "--- ADMIN LOGGED OUT SUCCESSFULLY ---" << endl;
        main();
    }
    break;
    default:
    {
        system("CLS");
        cout << "Enter valid option ";
    }
    }
    adminMenu(ad);
}
