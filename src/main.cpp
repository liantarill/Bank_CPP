#include <iostream>
#include <fstream>
#include <vector>
#include "login.hpp"
using namespace std;

template <class usstype, class pintype, class baltype>
class Bank
{
private:
    usstype username;
    pintype pin;
    baltype balance;

public:
    Bank(usstype username, pintype pin, baltype balance)
    {
        this->username = username;
        this->pin = pin;
        this->balance = balance;
    }

    usstype getUsername() { return this->username; }
    // abc getPassword() { return this->password; }
    pintype getPin() { return this->pin; }
    baltype getBalance() { return this->balance; }

    void deposit(baltype amount)
    {
        this->balance += amount;
        updateBalance();

        system("cls");
        cout << "Deposit successful" << endl;
        MenuBank(this->username, this->pin, this->balance);
    }

    void withdraw(baltype amount)
    {
        this->balance -= amount;
        updateBalance();
        system("cls");
        cout << "Withdraw successful" << endl;
        MenuBank(this->username, this->pin, this->balance);
    }

    void updateBalance()
    {
        ofstream balances;
        balances.open("Data/Balance/" + this->username + ".txt");
        balances << this->balance << endl;
        balances.close();
    }
};

void MenuBank(string username, string pin, double balance)
{
    Bank<string, string, double> *user = new Bank<string, string, double>(username, pin, balance);
    int choice;
    int inpin;
    char again;

    double amount;
    string inputPin;
    cout << "Hello " << user->getUsername() << "!!!" << endl
         << endl;
    cout << "Your balance is : " << user->getBalance() << endl;
    cout << "what do you want to do?" << endl;
    cout << "1. Deposit" << endl;
    cout << "2. Withdraw" << endl;
    cout << "3. Quit" << endl;
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
            if (amount < 0)
            {
                cout << "error,amount can't be minus" << endl;
                while (true)
                {
                    cout << "Do you wan't to try again ? (Y/N)";
                    cin >> again;

                    if (again == 'N' || again == 'n')
                    {
                        system("cls");
                        MenuBank(username, pin, balance);
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
            else if (!(int)amount)
            {
                cout << "Error!!" << endl;
                exit(0);
            }
            else
            {
                break;
            }
        }

        inpin = 1;
        while (true)
        {
            cout << "Enter your PIN : ";
            cin >> inputPin;
            if (inputPin == pin)
            {
                user->deposit(amount);
                break;
            }
            else
            {
                if (inpin == 3)
                {
                    ofstream pinFile;
                    pinFile.open("Data/PIN/" + user->getUsername() + ".txt");
                    pinFile << "BLOCKED" << endl;
                    pinFile.close();

                    system("cls");
                    cout << "BLOCKED" << endl;
                    break;
                }

                cout << endl
                     << "Please check again your PIN" << endl;
                inpin++;
            }
        }

        break;

    case 2:
        system("cls");
        while (true)
        {
            cout << "Enter withdraw amount : ";
            cin >> amount;
            if (amount < 0)
            {
                cout << "error,amount can't be minus" << endl;
                while (true)
                {
                    cout << "Do you wan't to try again ? (Y/N)";
                    cin >> again;

                    if (again == 'N' || again == 'n')
                    {
                        system("cls");
                        MenuBank(username, pin, balance);
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
            else if (amount > user->getBalance())
            {
                cout << "Error, balance not enough" << endl;
                while (true)
                {
                    cout << "Do you wan't to try again ? (Y/N)";
                    cin >> again;

                    if (again == 'N' || again == 'n')
                    {
                        system("cls");
                        MenuBank(username, pin, balance);
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
            else if (!(int)amount)
            {
                cout << "Error!!" << endl;
                exit(0);
            }
            else
            {
                break;
            }
        }

        inpin = 1;
        while (true)
        {
            cout << "Enter your PIN : ";
            cin >> inputPin;
            if (inputPin == pin)
            {
                user->withdraw(amount);
                break;
            }
            else
            {
                if (inpin == 3)
                {
                    ofstream pinFile;
                    pinFile.open("Data/PIN/" + user->getUsername() + ".txt");
                    pinFile << "BLOCKED" << endl;
                    pinFile.close();

                    system("cls");
                    cout << "BLOCKED" << endl;
                    break;
                }

                cout << endl
                     << "Please check again your PIN" << endl;
                inpin++;
            }
        }
        break;
    case 3:
        Quit();
        exit(0);
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
