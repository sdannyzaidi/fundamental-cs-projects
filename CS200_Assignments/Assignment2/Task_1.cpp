#include <iostream>
#include <string>

using namespace std;

void print_arr(char **darr, int rows, int arr[])
{
    cout << endl;
    cout << "Printing the 2D array" << endl;
    cout << endl;
    for (int i = 0; i< rows; i++)
    {
        cout << "[ ";
        for (int j = 0; j < arr[i]; j++)
        {
            cout << darr[i][j] << " ";
        }
        cout << "]"<<endl;
    }
}
void duplicate_rem(char **darr, int rows, int arr[])
{
    cout << "removing duplicates and replacing them with &" << endl;
    cout << endl;
    

    for (int i = 0; i < rows; i++)
    {
    for (int j = arr[i]; j > 0; j--)
        {
        if (darr[i][j] == darr[i][j - 1])
            {
                darr[i][j] = '&';
            }
        }
    }
}

void delete_elements(char **darr, int rows, int arr[])
{
        char **temp;
        temp = new char *[rows];
    
        for (int i = 0; i < rows; i++)
        {
            temp[i] = new char *arr[i];
        }
    
        for (int i = 0; i < rows; i++)
        {
            int counter = 0;
            for (int j = 0; j < arr[i]; j++)
            {
                if (darr[i][j] != '&' )
                {
                    temp[i][counter] = darr[i][j];
                    counter++;
                }
            }
            arr[i] = counter;
        }
     for (int i = 0; i < rows; i++)
     {
          for (int j = 0; j < arr[i]; j++)
          {
              darr[i][j] = temp[i][j];
          }
     }
    
    for (int i = 0; i < rows; i++)
    {
        delete [] temp[i];
    }
    delete [] temp;
}

int main()
{
    int rows;
    int cols;
    cout << "Enter the number of rows for the 2D array" << endl;
    cin >> rows;

    char ** arr = new char *[rows];
    int *arr_cols = new int [rows];
    for (int i = 0; i < rows; i++)
    {
        cout << "Enter the number of columns you want in row " << i+1 << endl;
        cin >> cols;
        arr_cols [i] = cols;
        arr[i] = new char [cols];
        for (int j = 0; j < cols; j++)
        {
            cout << "For row number " << i+1 << " and colunm number " << j+1 << " enter the alpabhet: ";
            cin >> arr[i][j];
        }
    }
    cout << endl;
    
    //Printing the Array
    print_arr(arr, rows, arr_cols);
    // turning the duplicate elements to &
    duplicate_rem(arr, rows, arr_cols);
    print_arr(arr, rows, arr_cols);

    // deleting the duplicate elements
    delete_elements(arr, rows, arr_cols);
    print_arr(arr, rows, arr_cols);

    for (int i = 0; i < rows; i++)
      {
          delete [] arr[i];
      }
      delete [] arr;
      delete [] arr_cols;
    

    return 0;
 }
