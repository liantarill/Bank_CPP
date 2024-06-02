#include <iostream>
#include <fstream>
#include "login.hpp"
using namespace std;

class Bank
{
private:
    string account;
    string password;
    string pin;
    double balance;

public:
    void setAccount(string account) { this->account = account; }

    string getAccount() { return this->account; }
    string getPassword() { return this->password; }
    string getPin() { return this->pin; }
    double getBalance() { return this->balance; }

    void deposit(const string &username, double amount)
    {
        ifstream balance;
        double bal;
        balance.open("Balance/" + username + ".txt");
        balance >> bal;
        balance.close();

        bal += amount;

        ofstream balances;
        balances.open("Balance/" + username + ".txt");
        balances << bal << endl;
        balances.close();

        cout << "Deposit successful. New balance: " << bal << endl;
    }

    void withdraw(const string &username, double amount)
    {
        ifstream balance;
        double bal;
        balance.open("Balance/" + username + ".txt");
        balance >> bal;
        balance.close();

        bal -= amount;

        ofstream balances;
        balances.open("Balance/" + username + ".txt");
        balances << bal << endl;
        balances.close();

        cout << "Withdraw successful. New balance: " << bal << endl;
    }
};

void MenuBank(string username, double balance)
{
    Bank user;
    int choice;
    char again;
    double amount;

    cout << "what do you want to do?" << endl;
    cout << "1. Deposit" << endl;
    cout << "2. Withdraw" << endl;
    cout << "Enter your choice : ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        system("cls");
        while (true)
        {
            cout << "Enter deposit amount : ";
            cin >> amount;
            if (amount > 0)
            {
                user.deposit(username, amount);
                break;
            }
            else
            {
                cout << "error,amount can't be minus" << endl;
                while (true)
                {
                    cout << "Do you wan't to try again ? (Y/N)";
                    cin >> again;

                    if (again == 'N' || again == 'n')
                    {
                        system("cls");
                        MenuBank(username, balance);
                        break;
                    }
                    else if (again == 'Y' || again == 'y')
                    {
                        system("cls");
                        break;
                    }
                    else
                    {
                        system("cls");
                        cout << "wrong input" << endl;
                    }
                }
                break;
            }
        }
        break;

    case 2:
        system("cls");
        while (true)
        {
            cout << "Enter withdraw amount : ";
            cin >> amount;
            if (amount > 0 && amount <= balance)
            {
                user.withdraw(username, amount);
                break;
            }
            else if (amount < 0)
            {
                cout << "error,amount can't be minus" << endl;
                while (true)
                {
                    cout << "Do you wan't to try again ? (Y/N)";
                    cin >> again;

                    if (again == 'N' || again == 'n')
                    {
                        system("cls");
                        MenuBank(username, balance);
                        break;
                    }
                    else if (again == 'Y' || again == 'y')
                    {
                        system("cls");
                        break;
                    }
                    else
                    {
                        system("cls");
                        cout << "wrong input" << endl;
                    }
                }
            }
            else if (amount > balance)
            {
                cout << "error, balance not enough" << endl;
                while (true)
                {
                    cout << "Do you wan't to try again ? (Y/N)";
                    cin >> again;

                    if (again == 'N' || again == 'n')
                    {
                        system("cls");
                        MenuBank(username, balance);
                        break;
                    }
                    else if (again == 'Y' || again == 'y')
                    {
                        system("cls");
                        break;
                    }
                    else
                    {
                        system("cls");
                        cout << "wrong input" << endl;
                    }
                }
            }
            break;
        }
        break;
    default:
        break;
    }
}

int main()
{
    Menu();

    return 0;
}
