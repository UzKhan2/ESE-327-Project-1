#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    string file = "agaricus-lepiota.data";
    ifstream infile(file);

    char arg1, arg2;
    vector<pair<char, int>> args;

    if (!infile.is_open())
    {
        cout << "Error opening file";
        return 0;
    }
    else
    {
        while (infile >> arg1 >> arg2)
        {
            bool found = false;

            for (auto &p : args)
            {
                if (p.first == arg1)
                {
                    p.second++;
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                args.push_back({arg1, 1});
            }
        }
    }

    // testing
    for (const auto &p : args)
    {
        cout << "Char: " << p.first << ", Int: " << p.second << endl;
    }

    return 0;
}
