#include<iostream>
#include<cmath>
using namespace std;

struct gameType
{
private:
    int game_num;
    int entry_end;
    int score;
    
public:
    
    gameType()
    {
        game_num = 0;
        entry_end = 0;
        score = 0;
    }
    gameType(int a, int b, int c)
    {
        game_num = a;
        entry_end = b;
        score = c;
    }
    void set_gameNum(int a)
    {
        game_num = a;
    }
    void set_entryEnd(int b)
    {
        entry_end = b;
    }
    void set_score(int c)
    {
        score = c;
    }
    int get_gameNum()
    {
        return game_num;
    }
    int get_entryEnd()
    {
        return entry_end;
    }
    int get_score()
    {
        return score;
    }
    void input_game_info(gameType arr[5])
    {
        int entry_end,score;
         for (int i =0; i < 5; i++)
         {
             arr[i].set_gameNum(i + 1);
             cout << "For game number " << i + 1 << " enter the time after which the entry for the game ends." << endl;
             cin >> entry_end;
             cout << endl;
             cout << "For game number " << i + 1 << " enter the score." << endl;
             cin >> score;
             cout << endl;
             arr[i].set_entryEnd(entry_end);
             arr[i].set_score(score);
         }
    }
    
    void print_sorted_array(gameType arr[5])
    {
        cout << "Printing sorted array" << endl;
        cout << endl;
        cout << "Score" << " " << "Entry Time" << " " << "Game number" << endl;
        for (int i = 0; i < 5; i++)
        {
            cout <<" " <<arr[i].get_score() << "       " << arr[i].get_entryEnd() << "         " << arr[i].get_gameNum() << endl;
            cout << endl;
        }

    }
    
    
    void max_score(gameType arr[5])
    {
       // int num1 = 0;
        gameType arr2[5];
        bool swapped;
        do{
            swapped = false;
        for (int i = 0; i < 4; i++)
        {
            if (arr[i].get_score() < arr[i+1].get_score())
            {
                swap(arr[i], arr[i+1]);
                swapped = true;
            }
        }
        }while(swapped);
        
        for (int i = 0; i < 4; i++)
        {
            if (arr[i].get_score()  == arr[i+1].get_score())
            {
                if (arr[i].get_entryEnd() > arr[i+1].get_entryEnd())
                swap(arr[i], arr[i+1]);
            }
        }
        arr[5].print_sorted_array(arr);
        for (int i = 0; i < 5; i++)
        {
            arr2[i].set_score(arr[i].get_score());
            arr2[i].set_gameNum(arr[i].get_gameNum());
            arr2[i].set_entryEnd(arr[i].get_entryEnd());
        }
        for (int i = 0; i < 4; i++)
        {
            if (i <= arr2[i].get_entryEnd())
            {
                cout << arr2[i].get_gameNum() << " ";
                int num = i+1;
                if ((num) > arr2[num].get_entryEnd())
                {
                    for (int j = num + 1; j < 5; j++)
                    {
                        arr2[j - 1] = arr2[j];
                    }
                }
            }
        }
    }
};

int main ()
{
    gameType g_arr[5];
    g_arr[5].input_game_info(g_arr);
    g_arr[5].max_score(g_arr);
    cout << endl;
    return 0;
}
