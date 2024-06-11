#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
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
    }

    void withdraw(baltype amount)
    {
        this->balance -= amount;
        updateBalance(this->username, this->balance);
        system("cls");
        cout << "Withdraw successful" << endl;
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

    void transfer(string user, double amount)
    {
        ifstream balances;
        double nowbalance;
        balances.open("Data/Balance/" + user + ".txt");
        balances >> nowbalance;
        balances.close();

        nowbalance += amount;
        updateBalance(user, nowbalance);

        balances.open("Data/Balance/" + this->getUsername() + ".txt");
        balances >> nowbalance;
        balances.close();
        this->balance -= amount;
        updateBalance(this->username, this->balance);
        system("cls");
        cout << "Transfer Successed" << endl;
    }

    void updateTransaction(double amount, string to)
    {
        ofstream transFile;
        transFile.open("Data/Transaction/" + this->username + ".txt", ios::app);
        if (to == "Deposit")
        {
            transFile << to << "          +" << amount << endl;
            transFile.close();
        }
        else if (to == "Withdraw")
        {
            transFile << to << "         -" << amount << endl;
            transFile.close();
        }
        else
        {
            transFile << "Transfer to " << to << "      -" << amount << endl;
            transFile.close();

            transFile.open("Data/Transaction/" + to + ".txt", ios::app);
            transFile << "Transfer from " << this->username << "      +" << amount << endl;
            transFile.close();
        }
    }

    void displayTransaction()
    {
        system("cls");
        ifstream transFile;
        stack<string> list;
        string history;

        transFile.open("Data/Transaction/" + this->username + ".txt");
        while (getline(transFile, history))
        {
            list.push(history);
        }

        transFile.close();
        if (list.empty())
        {
            cout << "You have't made a transaction yet" << endl;
        }
        while (!list.empty())
        {
            cout << list.top() << endl;
            list.pop();
        }
        char choice;
        cout << "_____________________" << endl;
        cout << "Do you want to exit ?(Y/N): ";

        cin >> choice;
        if (choice == 'Y' || choice == 'y')
        {
            system("cls");
            MenuBank(this->username, this->pin, this->balance);
        }
        else
        {
            displayTransaction();
        }
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
    bool exist;
    string transfername;
    vector<string> usernames;
    ifstream balFile;
    string users;
    cout << "Hello " << user->getUsername() << "!!!" << endl
         << endl;
    cout << "Your balance is : " << user->getBalance() << endl;
    cout << "what do you want to do?" << endl;
    cout << "1. Deposit" << endl;
    cout << "2. Withdraw" << endl;
    cout << "3. Transfer" << endl;
    cout << "4. Transaction History" << endl;
    cout << "5. Quit" << endl;
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
                user->updateTransaction(amount, "Deposit");
                MenuBank(user->getUsername(), user->getPin(), user->getBalance());
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
                user->updateTransaction(amount, "Withdraw");
                MenuBank(user->getUsername(), user->getPin(), user->getBalance());
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
                balFile.open("Data/ListUsers.txt");
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
                user->updateTransaction(amount, transfername);
                MenuBank(user->getUsername(), user->getPin(), user->getBalance());

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

    case 4:
        user->displayTransaction();
        break;
    case 5:
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
