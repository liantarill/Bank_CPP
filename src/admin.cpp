#include <iostream>
#include <fstream>
#include <vector>
#include <conio.h>
using namespace std;

struct Account
{
    string name;
    double balance;
};

void merge(vector<Account> &accounts, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Account> leftArray(n1);
    vector<Account> rightArray(n2);

    for (int i = 0; i < n1; i++)
        leftArray[i] = accounts[left + i];
    for (int j = 0; j < n2; j++)
        rightArray[j] = accounts[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (leftArray[i].balance >= rightArray[j].balance)
        {
            accounts[k] = leftArray[i];
            i++;
        }
        else
        {
            accounts[k] = rightArray[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        accounts[k] = leftArray[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        accounts[k] = rightArray[j];
        j++;
        k++;
    }
}

void mergeSort(vector<Account> &accounts, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(accounts, left, mid);
        mergeSort(accounts, mid + 1, right);
        merge(accounts, left, mid, right);
    }
}

void printAccounts(const vector<Account> &accounts)
{
    for (const auto &account : accounts)
    {
        cout << "Username: " << account.name << ", Balance: " << account.balance << endl;
    }
}

void Menu();
void Login();
void Registration();

void showUser()
{
    system("cls");
    vector<Account> accounts;
    char choice;
    ifstream userlist;
    ifstream balFile;
    double bal;
    string user;

    userlist.open("Data/ListUsers.txt");
    while (userlist >> user)
    {
        Account newAccount;
        newAccount.name = user;

        balFile.open("Data/Balance/" + user + ".txt");
        balFile >> bal;
        newAccount.balance = bal;
        balFile.close();

        accounts.push_back(newAccount);
    }

    mergeSort(accounts, 0, accounts.size() - 1);
    printAccounts(accounts);
    cout << "1. Show sorted list" << endl;
    cout << "2. Exit" << endl;
    cout << "Enter your choice : ";
    cin >> choice;
    switch (choice)
    {
    case 1:

        printAccounts(accounts);
        break;
    case 2:

        break;
    default:
        break;
    }
}
void searchUser(string search)
{
    string username;
    ifstream userFile;

    bool exist = false;

    userFile.open("Data/ListUsers.txt");
    while (userFile >> username)
    {
        if (username == search)
        {
            exist = true;
        }
    }
    userFile.close();

    int choice;
    int newpin;
    ofstream pinFile, myFile;
    if (exist == true)
    {
        cout << "1. Block user" << endl;
        cout << "2. Reset user's pin" << endl;
        cout << "Enter your choice : ";
        cin >> choice;

        if (choice == 1)
        {
            pinFile.open("Data/PIN/" + search + ".txt");
            pinFile << "BLOCKED" << endl;
            pinFile.close();
        }

        else if (choice == 2)
        {
            cout << "input new pin : ";
            cin >> newpin;
            myFile.open("Data/PIN/" + search + ".txt");
            myFile << newpin << endl;
            myFile.close();
        }
    }
    else
    {
        system("cls");
        cout << "Wrong user";
        searchUser(search);
    }
}
void Menu()
{
    int choice;

    cout << "                                                                                         " << endl;
    cout << " oooooo   oooooo     oooo           oooo                                                 " << endl;
    cout << "  `888.    `888.     .8'            `888                                                 " << endl;
    cout << "   `888.   .8888.   .8'    .ooooo.   888   .ooooo.   .ooooo.  ooo. .oo.  .oo.    .ooooo. " << endl;
    cout << "    `888  .8'`888. .8'    d88' `88b  888  d88' `'Y8 d88' `88b `888P'Y88bP'Y88b  d88' `88b" << endl;
    cout << "     `888.8'  `888.8'     888ooo888  888  888       888   888  888   888   888  888ooo888" << endl;
    cout << "      `888'    `888'      888    .o  888  888   .o8 888   888  888   888   888  888    .o" << endl;
    cout << "       `8'      `8'       `Y8bod8P' o888o `Y8bod8P' `Y8bod8P' o888o o888o o888o `Y8bod8P'" << endl;
    cout << "                                                                                         " << endl;
    cout << "                                                                                         " << endl;
    cout << "                              Please enter the number you :                              " << endl;
    cout << "                                   1. Create accout                                      " << endl;
    cout << "                                       2. Login                                          " << endl;

    cout << "Please enter your choice : ";
    cin >> choice;
    switch (choice)
    {
    case 1:
        system("cls");
        Registration();
        break;

    case 2:
        system("cls");
        Login();
        break;

    default:
        system("cls");
        cout << "Wrong input, please input the option \n";
        Menu();
    }
}

string getMaskedInput()
{
    string input;
    char ch;
    while (true)
    {
        ch = _getch();
        if (ch == '\r')
        {
            break;
        }
        else if (ch == '\b')
        {
            if (!input.empty())
            {
                cout << "\b \b";
                input.pop_back();
            }
        }
        else
        {
            input.push_back(ch);
            cout << '*';
        }
    }
    cout << endl;
    return input;
}

void Registration()
{
    ofstream myFile;
    string userReg, passReg;

    system("cls");
    cout << "Create your new account!" << endl;
    cout << "Enter username : ";
    cin >> userReg;
    cout << "Enter password : ";
    char ch;
    ch = _getch();
    while (ch != 13)
    {
        if (ch == 8)
        {
            if (passReg.length() > 0)
            {
                cout << "\b \b";
                passReg.erase(passReg.length() - 1);
            }
        }
        else
        {
            passReg.push_back(ch);
            cout << '*';
        }
        ch = _getch();
    }
    cout << endl;

    myFile.open("Data/Admin/ListAdmin.txt", ios::app);
    myFile << userReg << endl;
    myFile.close();

    myFile.open("Data/Admin/AdminAccount.txt", ios::app);
    myFile << userReg << " " << passReg << endl;
    myFile.close();

    system("cls");
    cout << "Registration successfull" << endl;

    Menu();
}

void Login()
{
    ifstream accFile, balFile, pinFile;
    string userLog, passLog;
    string userData, passData;
    string pin;
    double balance;

    bool exist = false;

    cout << "--------------------------------------" << endl;
    cout << "Enter your username and your password!" << endl;
    cout << "--------------------------------------" << endl;
    cout << "username : ";
    cin >> userLog;
    cout << "password : ";
    char ch;
    ch = _getch();
    while (ch != 13)
    {
        if (ch == 8)
        {
            if (passLog.length() > 0)
            {
                cout << "\b \b";
                passLog.erase(passLog.length() - 1);
            }
        }
        else
        {
            passLog.push_back(ch);
            cout << '*';
        }
        ch = _getch();
    }
    cout << endl;

    accFile.open("Data/UserAccount.txt");
    while (accFile >> userData >> passData)
    {
        if (userData == userLog && passData == passLog)
        {
            exist = true;
        }
    }
    accFile.close();

    if (exist == true)
    {
        system("cls");
    }
    else
    {
        system("cls");
        cout << "---------------------------------------" << endl;
        cout << "             LOGIN ERROR               " << endl;
        cout << "Please check your username and password" << endl;
        cout << "---------------------------------------" << endl;
        Menu();
    }
}

void Quit()
{
    system("cls");
    cout << "ooooooooooooo oooo                              oooo             oooooo   oooo                      " << endl;
    cout << "8'   888   `8 `888                              `888              `888.   .8'                       " << endl;
    cout << "     888       888 .oo.    .oooo.   ooo. .oo.    888  oooo         `888. .8'    .ooooo.  oooo  oooo " << endl;
    cout << "     888       888P`Y88b  `P  )88b  `888P`Y88b   888 .8P'           `888.8'    d88' `88b `888  `888 " << endl;
    cout << "     888       888   888   .oP`888   888   888   888888.             `888'     888   888  888   888 " << endl;
    cout << "     888       888   888  d8(  888   888   888   888 `88b.            888      888   888  888   888 " << endl;
    cout << "    o888o     o888o o888o `Y888``8o o888o o888o o888o o888o          o888o     `Y8bod8P'  `V88V`V8P'" << endl;
}

int main()
{
    int choice;
    cout << "1. Show user list" << endl;
    cout << "2. Search user" << endl;
    cout << "3. Exit" << endl;
    cout << "Please enter your choice : ";
    cin >> choice;
    string search;

    switch (choice)
    {
    case 1:
        showUser();
        break;

    case 2:
        system("cls");
        cout << "enter username : ";
        cin >> search;
        searchUser(search);
        break;
    default:
        break;
    }
}