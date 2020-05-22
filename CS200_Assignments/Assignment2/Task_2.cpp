#include <iostream>

using namespace std;

class set
{
private:
    int size;
    int *p;
    
public:
    set()
    {
        size = 0;
        p = new int [size];
        for (int i = 0; i < size; i++)
        {
            p[i] = 0;
        }
    }
    set(int s, int *arr)
    {
        size = s;
        p = new int [size];
        for (int i = 0; i < size; i++)
        {
            p[i] = arr[i];
        }
        
    }
    set (const set& obj)
    {
        size = obj.size;
        for (int i = 0; i < obj.size; i++)
        {
            p[i] = obj.p[i];
        }
        
    }
    void set_size(int a)
    {
        size = a;
    }
    int get_size()
    {
        return size;
    }
    void set_p(int *arr)
    {
        for (int i=0; i < size; i++)
        {
            p[i] = arr[i];

        }
    }
    int get_p()
    {
        return *p;
    }
    friend istream& operator >> (istream& input, set& obj)
    {
        cout << "Enter the size of set" << endl;
        input >> obj.size;
        for (int i = 0; i < obj.size; i++)
        {
            cout << "Enter element number " << i+1 << " : ";
            input >> obj.p[i];
        }
        return input;
    }
    friend ostream& operator << (ostream& output, set& obj)
    {
        output << "The set is as follows: " << endl;
        output << "[";
        for (int i = 0; i < obj.size; i++)
        {
            output << obj.p[i] << " ";
        }
        output << "]" << endl;
        return output;
    }
    
    void operator = (set obj)
    {
        size = obj.size;
        for (int i = 0; i < size; i++)
        {
            p[i] = obj.p[i];
        }
    }
 
    set operator + (set& obj)
    {
        set res;
        res.size = size + obj.size;
        for (int i = 0; i < size; i++)
        {
            res.p[i] = p[i];
        }
        for (int i = 0; i < obj.size; i++)
        {
            res.p[size+i] = obj.p[i];
        }
        int a = res.size;
        sort(res.p, res.p+res.size);
        int * temp_arr = new int [res.size];
        int b = 0;
        for (int i = 0; i < a; i++)
        {
            if (res.p[i] != res.p[i+1])
            {
                temp_arr[b] = res.p[i];
                b++;
            }
            else
            {
                res.size--;
            }
        }

        temp_arr[b+1] = res.p[a-1];

        for (int i = 0; i < (b+1); i++)
        {
            res.p[i] = temp_arr[i];
        }
        delete []temp_arr;

        return res;
 
    }
    set operator - (set& obj)
    {
       set res;
            int k = 0;
            for (int i = 0; i < size; i++)
            {
                for (int n = 0; n < obj.size; n++ )
                {
                    if (p[i] == obj.p[n])
                    {
                        res.p[k] = p[i];
                        k++;
                    }
                }
            }
       res.size = k;
       sort(res.p, res.p+k);
       int * temp_arr = new int [res.size];
       int b = 0;
       for (int i = 0; i < k; i++)
       {
           if (res.p[i] != res.p[i+1])
           {
               temp_arr[b] = res.p[i];
               b++;
           }
           else
           {
               res.size--;
           }
       }

       temp_arr[b+1] = res.p[k-1];

       for (int i = 0; i < (b+1); i++)
       {
           res.p[i] = temp_arr[i];
       }

       delete []temp_arr;
       return res;

    }
    ~set()
    {
        delete [] p;
    }
  
};

int main ()
{
    set s1,s2,s3;
    cout << "Enter the first set" << endl;
    cout << endl;
    cin >> s1;
    cout << endl;
    cout << s1;
    cout << endl;
   
    cout << "Enter the second set" << endl;
    cout << endl;
    cin >> s2;
    cout << endl;
    cout << s2;
    cout << endl;
    
    cout << "Finding the union of both sets" << endl;
    s3 = s1 + s2;
    cout << endl;
    cout << s3;
    cout << endl;

    cout << "Finding the intersection of both sets" << endl;
    s3 = s1 - s2;
    cout << endl;
    cout << s3;
    cout << endl;
    cout << endl;
    
    return 0;
}
