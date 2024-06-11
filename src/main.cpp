#include <iostream>
#include <fstream>
#include <vector>
#include <conio.h>
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
        updatePin();
    }

    usstype getUsername() { return this->username; }
    pintype getPin() { return this->pin; }
    baltype getBalance() { return this->balance; }

    void deposit(baltype amount)
    {
        this->balance += amount;
        updateBalance(this->username, this->balance);

        system("cls");
        cout << "Deposit successful" << endl;
        MenuBank(this->username, this->pin, this->balance);
    }

    void withdraw(baltype amount)
    {
        this->balance -= amount;
        updateBalance(this->username, this->balance);
        system("cls");
        cout << "Withdraw successful" << endl;
        MenuBank(this->username, this->pin, this->balance);
    }

    void updateBalance(string username, double balance)
    {
        ofstream balances;
        balances.open("Data/Balance/" + username + ".txt");
        balances << balance << endl;
        balances.close();
    }

    void updatePin()
    {
        ofstream pinFile;
        pinFile.open("Data/PIN/" + this->username + ".txt");
        pinFile << this->pin << endl;
        pinFile.close();
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
            inputPin = getMaskedInput();
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
                    exit(0);
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
            inputPin = getMaskedInput();
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
                    exit(0);
                }

                cout << endl
                     << "Please check again your PIN" << endl;
                inpin++;
            }
        }
        break;
    case 3:
        system("cls");
        while (true)
        {
            cout << "Username : ";
            cin >> transfername;
            if (transfername != user->getUsername())
            {
                // mengubah listuser menjadi vector
                balFile.open("Data/ListUser.txt");
                while (balFile >> users)
                {
                    usernames.push_back(users);
                }
                balFile.close();

                // check username dalam vector
                exist = false;
                for (auto name : usernames)
                {
                    if (transfername == name)
                        exist = true;
                }

                // jika ada input nilai  transfer
                if (exist == true)
                {
                    while (true)
                    {
                        cout << "Transfer amount : ";
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
                    break;
                }
                else
                {
                    system("cls");
                    cout << "User doesn't exist." << endl;

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
            }
            else
            {
                system("cls");
                cout << "Can't transfer to your own account" << endl;
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
        }

        inpin = 1;
        while (true)
        {
            cout << "Enter your PIN : ";
            cin >> inputPin;
            if (inputPin == pin)
            {
                user->transfer(transfername, amount);
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
                    exit(0);
                }

                cout << endl
                     << "Please check again your PIN" << endl;
                inpin++;
            }
        }
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
