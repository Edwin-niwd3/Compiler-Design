// --------------------------------------------------------------------------------------
//Name                        Edwin Navarro
//Course                      CMPS 385, Spring 2022
//Assignment                  No.12/part 1
//Due date                    11/28/2022
//Purpose:                    Write a program to create a Binary Search Tree with the
//                            given information
//---------------------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

template<class T>
class BST
{
private:
    struct node
    {
        T info;
        node *left;
        node *right;
    };
    node *root;
public:
    BST()
    { root = NULL; }
    void Insert(node* &r, T x)
    {
        node *p = new(node);
        p->info = x;
        p->left = p->right = NULL;
        if (r == NULL)
        {
            r = p;
        }
        else
        {
            if (x > r->info) Insert(r->right, x);
            if (x < r->info) Insert(r->left, x);
        }
    }
    void displayInOrder(node *r)
    {
        if (r != NULL)
        {
            //(LC)(P)(RC)
            displayInOrder(r->left);
            cout << r->info << " ";
            displayInOrder(r->right);
        }
    }
    void displayPreOrder(node *r)
    {
        if (r != NULL)
        {
            //(P)(LC)(RC)
            cout << r->info << " ";
            displayPreOrder(r->left);
            displayPreOrder(r->right);
        }
    }
    void displayPostOrder(node *r)
    {
        if (r != NULL)
        {
            //(LC)(RC)(P)
            displayPostOrder(r->left);
            displayPostOrder(r->right);
            cout << r->info << " ";
        }
    }
    void search(node *r, T x)
    {
        if (r == NULL)
        {
            cout << x << " does not exist!\n";
        }
        else if (r->info == x)
        {
            cout << x << " is found!\n";
        }
        else
        {
            if (x > r->info) search(r->right, x);
            if (x < r->info) search(r->left, x);
        }
    }
    void displayLeaves(node *r)
    {
        if (r->left == NULL && r->right == NULL)
        {
            cout << r->info << endl;
        }
        else
        {
            if (r->left != NULL) displayLeaves(r->left);
            if (r->right != NULL) displayLeaves(r->right);
        }
    }
    void DisplaySingleChild(node *r)
    {
        if (r->right != NULL && r->left == NULL)
        {
            cout << r->info << " ";
            DisplaySingleChild(r->right);
        }
        else if (r->right == NULL && r->left != NULL)
        {
            cout << r->info << " ";
            DisplaySingleChild(r->left);
        }
    }
    int TreeHeight(node *r)
    {
        if (r == NULL) return 1;
        else return (1 + max(TreeHeight(r->left), TreeHeight(r->right)));
    }
    int NumberOfNodes(node *r)
    {
        if (r == NULL) return 0;
        else return 1 + NumberOfNodes(r->left) + NumberOfNodes(r->right);
    }
    void tempInsert(T x)
    {
        Insert(root, x);
    }
    void tempsearch(T x)
    {
        search(root, x);
    }
    void tempInOrder()
    {
        displayInOrder(root);
    }
    void tempPostOrder()
    {
        displayPostOrder(root);
    }
    void tempPreOrder()
    {
        displayPreOrder(root);
    }
    void tempDisplayLeaves()
    {
        displayLeaves(root);
    }
    void tempSingleChild()
    {
        DisplaySingleChild(root);
    }
    int tempTreeHeight()
    {
        return TreeHeight(root);
    }
    int tempNodeNumbers()
    {
        return NumberOfNodes(root);
    }
};

int main()
{
    BST<string> DayTree;
    string Days[7] = {"MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};
    for (int x = 0; x < 7; x++)
    {
        DayTree.tempInsert(Days[x]);
    }
    string search;
    cout << "This is the In Order display: ";
    DayTree.tempInOrder();
    cout << endl;
    cout << "This is the Post Order display: ";
    DayTree.tempPostOrder();
    cout << endl;
    cout << "This is the Pre Order display: ";
    DayTree.tempPreOrder();
    cout << endl;
    DayTree.tempDisplayLeaves();
    cout << endl;
    DayTree.tempSingleChild();
    cout << endl;
    cout << "This is the height of the tree: " << DayTree.tempTreeHeight() << endl;
    cout << "What day would you like to search for? (write in all caps): "; cin >> search;
    DayTree.tempsearch(search);
    cout << "This is how many nodes there are: " << DayTree.tempNodeNumbers() << endl;

    system("pause");
    return 0;
}