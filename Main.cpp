#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

class Leaf // Tree node to hold each argument
{
private:
    friend class TreeList;
    char elem; // Specific argument transaction value
    int count; // Count for how many times the Leaf comes up in the tree

public:
    std::vector<Leaf *> children; // Vector to hold up to n number of children

    Leaf(char e) // Allows for a public access to private data for TreeList class
    {
        elem = e;
        count = 0;
    }
};

class TreeList // Linked List class for the tree
{
public:
    TreeList();                                    // Constructor, creates root with null pointer
    void addChild(Leaf *parent, char elem);        // Add new child with arguement to given parent, doesn't move from parent
    bool checkChild(Leaf *parent, char elem);      // Chekcks if the parent has a child with given argument returns true if yes, incremeants
    Leaf *recursiveMover(Leaf *parent, char elem); // Looks for child of parent that has the same arguemnt and moves there, else returns parent
    void printTree(Leaf *node, int depth);         // Prints out tree to output withsome fromatting
    Leaf *root;                                    // Makes root public
};

TreeList::TreeList()
{
    root = nullptr;
}

void TreeList::addChild(Leaf *parent, char elem)
{
    Leaf *p = new Leaf(elem);      // Create a new leaf with inputed arguement
    parent->children.push_back(p); // push into vector of childern
}

bool TreeList::checkChild(Leaf *parent, char elem)
{
    bool found = false; // Bool to check if child is found

    for (int i = 0; i < parent->children.size(); i++)
    {
        if (parent->children[i]->elem == elem) // Check if child and argument is found
        {
            parent->children[i]->count++; // Increaments number number of times transaction occured
            found = true;
        }
    }
    return found;
}

Leaf *TreeList::recursiveMover(Leaf *parent, char elem)
{
    Leaf *result = nullptr; // Dummy leaf to copy location over
    bool found = false;     // Bool to check if chils is found

    for (int i = 0; i < parent->children.size(); i++)
    {
        if (parent->children[i]->elem == elem) // Check if child and arguemnt is found
        {
            result = parent->children[i]; // Copies over the location of child into result
            found = true;                 // Found flag is set
        }
    }
    if (!found) // If child wasn't found return parent instead
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

    cout << string(depth * 2, ' ') << "Element: " << node->elem << ", Count: " << node->count << endl;

    for (Leaf *child : node->children)
    {
        printTree(child, depth + 1);
    }
}

class StringNode
{
private:
    Leaf *leaf;
    StringNode *next;

    friend class StringLinkedList;
};

class StringLinkedList
{
public:
    StringLinkedList();             // constructor
    ~StringLinkedList();            // destructor
    void addFront(const string &e); // adds new element on the front
    void removeFront();             // removes front element
    bool empty() const;             // true of list is empty
private:
    StringNode *head;
};

StringLinkedList ::StringLinkedList()
{

    head = NULL;
}

bool StringLinkedList ::empty() const
{
    return (head == NULL);
}

StringLinkedList ::~StringLinkedList()
{

    while (!empty())
        removeFront();
}

void StringLinkedList ::addFront(const string &e)
{
    StringNode *p;

    p = new StringNode;
    // p->elem = e;

    p->next = head;
    head = p;
}

void StringLinkedList ::removeFront()
{
    StringNode *p;

    if (head != NULL)
    {
        p = head;
        head = p->next;
        delete p;
    }
    else
        cout << "Warning: attempt to remove from an empty list" << endl;
}

int main()
{
    TreeList tree; // Initialize tree
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
        while (getline(infile, line))
        {
            line += '\n';

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

    string file2 = "out.data";
    ofstream oufile(file2);
    int count = 0;

    if (!oufile.is_open())
    {
        cout << "Error opening file";
        return 0;
    }

    infile.open(file);

    if (!infile.is_open())
    {
        cout << "Error opening file";
        return 0;
    }
    else
    {
        while (getline(infile, line))
        {
            line += '\n';

            for (int i = 0; i < args.size(); i++)
            {
                for (int j = 0; j < line.length(); j++)
                {
                    if (args[i].first == line[j])
                    {
                        oufile << args[i].first;

                        if (count != ((line.length() / 2) - 1))
                        {
                            count++;

                            oufile << ",";
                        }
                        // cout << count << " " << line.length() << " ";
                    }
                }
            }
            count = 0;
            oufile << endl;
        }
    }

    infile.close();
    oufile.close();
    ifstream infile2(file2);

    // infile2.open(file2);

    if (!infile2.is_open())
    {
        cout << "Error opening file";
        return 0;
    }
    else
    {
        while (getline(infile2, line))
        {
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

                current = tree.recursiveMover(current, arg1);
            }
        }
    }

    infile2.close();

    cout << "Printing Tree" << endl;
    tree.printTree(tree.root, 0);

    // vector<StringLinkedList> Header;

    for (int i = 0; i < args.size(); i++)
    {
        // StringLinkedList args[i];
    }

    cout << "Breadth-First Search:" << endl;

    // Initialize a queue for BFS
    queue<Leaf *> bfsQueue;

    // Start with the root node
    bfsQueue.push(tree.root);

    while (!bfsQueue.empty())
    {
        Leaf *current = bfsQueue.front();
        bfsQueue.pop();

        // Process the current node
        // cout << "Element: " << current->elem << ", Count: " << current->count << endl;

        // Add all children to the queue
        for (Leaf *child : current->children)
        {
            bfsQueue.push(child);
        }
    }

    // Fill in header vector go through array with all arguements
    // connect them to all instances of same thing wiht pointers breath frist search?

    return 0;
}
