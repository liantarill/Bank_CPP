#include <iostream>
#include <fstream>
using namespace std;

void Menu();
void Login();
void Registration();
void MenuBank(string, string, double);

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
    string userReg, passReg, pinReg;

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
    
    cout << "Enter PIN : ";

    char ch;
    ch = _getch();
    while (ch != 13)
    { 
        if (ch == 8)
        { 
            if (pinReg.length() > 0)
            {
                cout << "\b \b"; 
                pinReg.erase(pinReg.length() - 1);
            }
        }
        else
        {
            pinReg.push_back(ch);
            cout << '*';
        }
        ch = _getch();
    }

    myFile.open("Data/UserAccount.txt", ios::app);
    myFile << userReg << " " << passReg << endl;
    myFile.close();

    myFile.open("Data/PIN/" + userReg + ".txt", ios::app);
    myFile << pinReg << endl;
    myFile.close();

    myFile.open("Data/Balance/" + userReg + ".txt");
    myFile << 0;
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
        balFile.open("Data/Balance/" + userLog + ".txt");
        balFile >> balance;
        balFile.close();

        pinFile.open("Data/PIN/" + userLog + ".txt");
        pinFile >> pin;
        if (pin == "BLOCKED")
        {
            cout << "YOUR ACCOUNT BLOCKED" << endl;
            exit(0);
        }
        pinFile.close();

        MenuBank(userLog, pin, balance);
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
