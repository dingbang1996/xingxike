#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

#define WORD_SIZE   427452

bool dictFind(const string* dict, const string &find)
{
    int i;
    for (i = 0; i < WORD_SIZE; i++)
    {
        if (dict[i] == find)
        {
            return true;
        }
    }
    return false;
}

void segment(const string *dict, const string &input)
{
    vector<string> stack;
    int start = 0;
    int end = input.length();
    while (end > 2)
    {
        for (start = 0; start < end - 2; start += 2)
        {
            string substr = input.substr(start, end - start);
            if (dictFind(dict, substr))
            {
                end = start;
                stack.push_back(substr);
            }
        }
        if (end - start == 2)
        {
            stack.push_back(input.substr(start, 2));
            end = start;
        }
        else
        {
            end = start - 2;
        }
    }
    if (end > 0)
    {
        stack.push_back(input.substr(0, end));
    }
    while (!stack.empty())
    {
        cout << stack[stack.size() - 1] << " ";
        stack.pop_back();
    }
    cout << endl;
}

int main()
{
    string *dict;
    ifstream in("C:\\Users\\david\\Developing\\算法练习\\逆向最大长度匹配\\dic.txt", ios_base::in);
    int i;
    
    if (!in.good())
    {
        cout << "词典读取失败" << endl;
        return 0;
    }

    dict = new string[WORD_SIZE];

    for (i = 0; i < WORD_SIZE; i++)
    {
        in >> dict[i];
    }

    in.close();

    cout << "词典读取完成！" << endl;

    string input;
    while (true)
    {
        cin >> input;
        segment(dict, input);
    }

    delete[] dict;
}