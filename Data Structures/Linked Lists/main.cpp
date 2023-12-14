// --------------------------------------------------------------------------------------
//Name                        Edwin Navarro
//Course                      CMPS 385, Spring 2022
//Assignment                  No.10/part 1
//Due date                    11/7/2022
//Purpose:                    Write a program to create a banking system using an orderd
//                            linked list
//---------------------------------------------------------------------------------------

#include<fstream>
#include<iostream>
#include<string>

using namespace std;

void ShowMenu();

class ORDERED
{
private:
    struct node
    {
        int accNo;
        string name;
        float balance;
        node *next;
    };
    node *list;
public:
    ORDERED()
    {
        list = NULL;
    }
    bool EmptyOrder()
    {
        if (list == NULL) return true;
        else return false;
    }
    void pushOrder(int AccNo, string Name, float Balance)
    {
        node *temp = new(node);
        temp->accNo = AccNo;
        temp->name = Name;
        temp->balance = Balance;
        temp->next = NULL;
        node *front = list;
        node *back = list;
        if (list == NULL)
        {
            list = temp;
        }
        while (front != NULL && AccNo > front->accNo)
        {
            back = front; front = front->next;
        }
        if (front == back)
        {
            temp->next = front; list = temp;
        }
        else
        {
            temp->next = front; back->next = temp;
        }
    }
    void displayOrder()
    {
        node *display = list;
        while (display != NULL)
        {
            cout << display->accNo << ", " << display->name << "-->"; display = display->next;
        }
        cout << "NULL\n";
    }
    void DepositOrder()
    {
        node *deposit = list;
        int AccNum;
        cout << "Enter your Account Number: "; cin >> AccNum;
        while (deposit != NULL && AccNum != deposit->accNo)
        {
            deposit = deposit->next;
        }
        float money = deposit->balance;
        float amount;
        cout << deposit->name << ", how much would you like to deposit? "; cin >> amount;
        money += amount;
        deposit->balance = money;
        cout << deposit->name << ", your new balance is: " << deposit->balance << endl;
    }
    void WithdrawOrder()
    {
        node *withdraw = list;
        int AccNum;
        cout << "Enter your Account Number: "; cin >> AccNum;
        while (withdraw != NULL && AccNum != withdraw->accNo)
        {
            withdraw = withdraw->next;
        }
        float money = withdraw->balance;
        float amount;
        cout << withdraw->name << ", how much would you like to withdraw? "; cin >> amount;
        money -= amount;
        withdraw->balance = money;
        cout << withdraw->name << ", your new balance is: " << withdraw->balance << endl;
    }
    void showBal()
    {
        node *bal = list;
        int AccNum;
        cout << "Enter your Account Number: "; cin >> AccNum;
        while (bal != NULL && AccNum != bal->accNo)
        {
            bal = bal->next;
        }
        float money = bal->balance;
        float amount;
        cout << bal->name << ", your balance is: " << bal->balance << endl;
    }
    void deleteAcc()
    {
        node *del = list;
        node *back = list;
        int AccNum;
        cout << "Enter your Account Number: "; cin >> AccNum;
        while (del != NULL && AccNum != del->accNo)
        {
            back = del; del = del->next;
        }
        back->next = del->next;
        cout << del->name << "We have deleted your account.\n";
        delete del;
    }
};

int main()
{
    int AccountNum;
    string AccountName;
    float AccountBal;
    ORDERED Accounts;
    fstream file;
    file.open("Text.txt");
    while (file >> AccountNum >> AccountName >> AccountBal)
    {
        Accounts.pushOrder(AccountNum, AccountName, AccountBal);
    }
    char Answer;
    int MenuChoice;
    ShowMenu();
    do
    {
        cout << "Please enter your choice (1-5): "; cin >> MenuChoice;
        switch (MenuChoice)
        {
            case 1:Accounts.showBal(); break;
            case 2:Accounts.DepositOrder(); break;
            case 3:Accounts.WithdrawOrder(); break;
            case 4:Accounts.displayOrder(); break;
            case 5:Accounts.deleteAcc(); break;
        }
        cout << "Continue?: "; cin >> Answer;
    } while (tolower(Answer) == 'y');
    system("pause");
    return 0;
}

void ShowMenu()
{
    cout << "-----------Menu-----------\n";
    cout << "1.Show my Balance\n";
    cout << "2.Deposit in my Account\n";
    cout << "3. Withdraw from my account\n";
    cout << "4. Show me all\n";
    cout << "5. Close my account\n";
}
