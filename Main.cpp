#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    string file = "agaricus-lepiota.data";
    ifstream infile(file);

    char arg1 = 'u', arg2;
    string line;
    vector<pair<char, int>> args;

    if (!infile.is_open())
    {
        cout << "Error opening file";
        return 0;
    }
    else
    {
        while (!infile.eof())
        {
            getline(infile, line);
            line += '\n';
            // cout << line << endl;
            while (line.length() != 0)
            {
                arg1 = line[0];
                line = line.substr(1);
                if (arg1 == '\n')
                {
                    break;
                }

                if (line.length() > 0)
                {
                    arg2 = line[0];
                    line = line.substr(1);
                }

                // while (infile >> arg1 >> arg2)
                // {
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
    }

    ////Reading into vector and counting

    int n = args.size();
    for (int i = 1; i < n; i++)
    {
        int key = args[i].second;
        int j = i - 1;

        while (j >= 0 && args[j].second < key)
        {
            args[j + 1].second = args[j].second;
            j = j - 1;
        }

        args[j + 1].second = key;
    }

    ////Sorting vector by frequency

    // Testing
    for (const auto &p : args)
    {
        cout << "Char: " << p.first << ", Amount: " << p.second << endl;
    }

    return 0;
}
