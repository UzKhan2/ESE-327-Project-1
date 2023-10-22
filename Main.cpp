#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Leaf
{
private:
    std::vector<Leaf *> children;

    friend class TreeList;

public:
    char elem;
    int count;
    Leaf(char e)
    {
        elem = e;
        count = 0;
    }
};

class TreeList
{
public:
    TreeList();
    void addChild(Leaf *parent, char elem);
    bool checkChild(Leaf *parent, char elem);
    Leaf *recursiveCheckChild(Leaf *parent, char elem);
    void printTree(Leaf *node, int depth);

    Leaf *root; // Made root public for easier access
};

TreeList::TreeList()
{
    root = nullptr;
}

void TreeList::addChild(Leaf *parent, char elem)
{
    Leaf *p = new Leaf(elem);
    parent->children.push_back(p);
}

bool TreeList::checkChild(Leaf *parent, char elem)
{
    Leaf *result = nullptr;
    bool found = false;

    for (int i = 0; i < parent->children.size(); i++)
    {
        if (parent->children[i]->elem == elem)
        {
            parent->children[i]->count++;
            result = parent->children[i];
            found = true;
        }

        // Leaf *recursiveResult = recursiveCheckChild(parent->children[i], elem);

        // if (recursiveResult != nullptr)
        // {
        //     result = recursiveResult;
        // }
    }

    return found;
}

Leaf *TreeList::recursiveCheckChild(Leaf *parent, char elem)
{
    Leaf *result = nullptr;
    bool found = false;

    for (int i = 0; i < parent->children.size(); i++)
    {
        if (parent->children[i]->elem == elem)
        {
            // parent->children[i]->count++;
            result = parent->children[i];
            found = true;
        }

        // Leaf *recursiveResult = recursiveCheckChild(parent->children[i], elem);

        // if (recursiveResult != nullptr)
        // {
        //     result = recursiveResult;
        // }
    }
    if (!found)
    {
        result = parent;
    }

    return result;
}

void TreeList::printTree(Leaf *node, int depth)
{

    if (node == nullptr)
    {
        cout << "Empty Tree";
        return;
    }

    // Print the node's element and depth
    cout << string(depth * 2, ' ') << "Element: " << node->elem << ", Count: " << node->count << endl;

    // Recursively print children
    for (Leaf *child : node->children)
    {
        printTree(child, depth + 1);
    }
}

int main()
{
    TreeList tree;
    tree.root = new Leaf('U');

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

    infile.close();

    for (const auto &p : args)
    {
        cout << "Char: " << p.first << ", Amount: " << p.second << endl;
    }

    ////Sorting vector by frequency

    infile.open(file);

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

            Leaf *current = tree.root;

            arg1 = line[0];
            line = line.substr(1);

            if (line.length() > 0)
            {
                arg2 = line[0];
                line = line.substr(1);
            }

            if (!tree.checkChild(current, arg1))
            {
                tree.addChild(current, arg1);
            }

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

                if (!tree.checkChild(current, arg1))
                {
                    tree.addChild(current, arg1);
                }

                // while (tree.checkChild(current, arg1))
                // {
                //     Leaf *resultLeaf = tree.recursiveCheckChild(tree.root, arg1);
                //     if (!tree.checkChild(current, arg1))
                //     {
                //         tree.addChild(current, arg1);
                //         break;
                //     }
                // }
            }
        }
    }

    infile.close();
    // Testing

    tree.printTree(tree.root, 0);
    return 0;
}
