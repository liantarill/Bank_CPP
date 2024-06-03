#include <iostream>
#include <fstream>
using namespace std;

void Menu();
void Login();
void Registration();
void MenuBank(string, double);

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

void Registration()
{
    ofstream myFile;
    string userReg, passReg, pinReg;

    system("cls");
    cout << "Create your new account!" << endl;
    cout << "Enter username : ";
    cin >> userReg;
    cout << "Enter password : ";
    cin >> passReg;
    cout << "Enter PIN : ";
    cin >> pinReg;

    myFile.open("UserAccount.txt", ios::app);
    myFile << userReg << " " << passReg << endl;
    myFile.close();

    myFile.open("UserPIN.txt", ios::app);
    myFile << userReg << " " << pinReg << endl;
    myFile.close();

    myFile.open("Balance/" + userReg + ".txt");
    myFile << 0;
    myFile.close();

    system("cls");
    cout << "Registration successfull" << endl;

    Menu();
}

void Login()
{
    ifstream myFile;
    string userLog, passLog;
    string userData, passData;
    double balance;

    bool exist = false;

    cout << "--------------------------------------" << endl;
    cout << "Enter your username and your password!" << endl;
    cout << "--------------------------------------" << endl;
    cout << "username : ";
    cin >> userLog;
    cout << "password : ";
    cin >> passLog;

    myFile.open("UserAccount.txt");
    while (myFile >> userData >> passData)
    {
        if (userData == userLog && passData == passLog)
        {
            exist = true;
        }
    }
    myFile.close();

    if (exist == true)
    {
        system("cls");
        // cout << "Hello " << userLog << "!!!" << endl;

        myFile.open("Balance/" + userLog + ".txt");
        myFile >> balance;
        // cout << "Your balance is : " << balance << endl;
        MenuBank(userLog, balance);
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
    system("color 9");
    cout << "ooooooooooooo oooo                              oooo             oooooo   oooo                      " << endl;
    cout << "8'   888   `8 `888                              `888              `888.   .8'                       " << endl;
    cout << "     888       888 .oo.    .oooo.   ooo. .oo.    888  oooo         `888. .8'    .ooooo.  oooo  oooo " << endl;
    cout << "     888       888P`Y88b  `P  )88b  `888P`Y88b   888 .8P'           `888.8'    d88' `88b `888  `888 " << endl;
    cout << "     888       888   888   .oP`888   888   888   888888.             `888'     888   888  888   888 " << endl;
    cout << "     888       888   888  d8(  888   888   888   888 `88b.            888      888   888  888   888 " << endl;
    cout << "    o888o     o888o o888o `Y888``8o o888o o888o o888o o888o          o888o     `Y8bod8P'  `V88V`V8P'" << endl;
}