#include "header.hpp"


void Menu();
void Login();
void Registration();

void Welcome(){
    cout << "                                                                " <<endl;
    cout << "Y8b Y8b Y888P         888                                       " << endl;
    cout << " Y8b Y8b Y8P   ,e e,  888  e88'888  e88 88e  888 888 8e   ,e e, " << endl;
    cout << "  Y8b Y8b Y   d88 88b 888 d888  '8 d888 888b 888 888 88b d88 88b" << endl;
    cout << "   Y8b Y8b    888   , 888 Y888   , Y888 888P 888 888 888 888   ," << endl;
    cout << "    Y8P Y      'YeeP' 888  '88,e8'  '88 88'  888 888 888  'YeeP'" << endl;
    cout << endl;
    cout << endl;
}


void Registration(){
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

    system("cls");
    cout << "Registration successfull" << endl;

    Menu();
}

void Login(){
    ifstream myFile;
    string userLog, passLog;
    string userData, passData;
    bool exist = false;

    cout << "Enter your username and your password!" << endl;
    cout << "username : ";
    cin >> userLog;
    cout << "password : ";
    cin >> passLog;

    myFile.open("UserAccount.txt");
    while(myFile >> userData >> passData){
        if(userData==userLog && passData==passLog){
            exist=true;
        }
    }
    myFile.close();

    if(exist==true){
		system("cls");	
        cout << "Welcome " << userLog;
	}else{
		system("cls");
		cout << "LOGIN ERROR \nPlease check your username and password \n\n";
		Menu();
	}
}

void Menu(){
    int choice;

    Welcome();
    cout << "Please enter the number you : " << endl;
    cout << "1. Create accout" << endl;
    cout << "2. Login" << endl;

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

int main(){
    Menu();

}