#ifndef AUTH_H_INCLUDED
#define AUTH_H_INCLUDED

#include <iostream>
#include <fstream>
#include <map>
#include <string>

#include "interface.h"
#include "shop.h"
#include "database.h"
using namespace std;




void initDatabaseUsers();
void updateDatabaseUsers();
void signUp();
void logIn();
void loggedInMenu(string);
void authManager();
void separator();

void initDatabaseUsers(){
    ifstream f("dbUsers.txt");
    string username;

    userInfo UserData;
    while ( !f.eof() && f >> username && f >> UserData.password && f >> UserData.balance )
    {
        DatabaseUsers[username] = UserData;
    }

    string dbMessage = "Database Users Initialized.";
    goToXY( 85 - dbMessage.size()/2, 25);
    cout << dbMessage;
    Sleep(1500);
}

void updateDatabaseUsers(){
    ofstream g("dbUsers.txt");

    for ( auto &it : DatabaseUsers )
        g << it.first << " " << it.second.password << " " << it.second.balance << endl;

}

void signUp(){
    userInfo newUserData;
    string username;
    int row = 0;
    string usernameMessage = "Your new username: ";
    goToXY(85 - usernameMessage.size()/2 , 20 + row++);
    cout << usernameMessage;
    cin >> username;

    string passwordMessage = "Your parola: ";
    goToXY(85 - passwordMessage.size()/2 , 20 + row ++);
    cout << passwordMessage;
    cin >> newUserData.password;

    newUserData.balance = 0;

    if ( DatabaseUsers.count(username) )
    {
        string errorMessage = " already added.Press ENTER to retry.";
        goToXY(85 - (username.size()/2 + errorMessage.size()/2), 20 + ++row);
        cout << "User " << username << errorMessage;
        cin.ignore();
        cin.get();
        system("cls");
        signUp();
    }
    else if (newUserData.password.size() < 8)
        {
            string errorMessage = "Sorry but your password must contain 8 characters.Press ENTER to retry";
            goToXY(85 - errorMessage.size()/2, 20 + ++row);
            cout << errorMessage;
            cin.ignore();
            cin.get();
            system("cls");
            signUp();
        }
        else
        {
            DatabaseUsers[username] = newUserData;
            string succesMessage = " successfully added.Press ENTER for Menu.";
            goToXY( 85 - (username.size()/2 + succesMessage.size()/2) , ++row) ;
            updateDatabaseUsers();
            //cout << "Database Updated Succesfull";
            system("cls");
            authManager();
        }

}

void logIn(){
    string tryUsername, tryPassword;

    int row = 0;
    string usernameMessage = "Your username: ";
    goToXY(85 - usernameMessage.size()/2 , 20 + row++);
    cout << usernameMessage;
    cin >> tryUsername;

    string passwordMessage = "Your parola: ";
    goToXY(85 - passwordMessage.size()/2 , 20 + row ++);
    cout << passwordMessage;
    cin >> tryPassword;

    if( DatabaseUsers.count(tryUsername) )
    {
        if ( DatabaseUsers[tryUsername].password == tryPassword )
        {
            string succesMessage = " logged in successfully. Press ENTER to continue...";
            goToXY(85 - (tryUsername.size()/2 + succesMessage.size()/2), 20 + ++row );
            cout << "User "<< tryUsername << succesMessage ;
            cin.ignore();
            cin.get();
            system("cls");
            loggedInMenu(tryUsername);
        }
        else
        {
            string errorMessage = "Wrong username/password.";
            goToXY(85 - errorMessage.size()/2 , 20 + ++row );
            cout << errorMessage;
            cin.ignore();
            cin.get();
            system("cls");
            authManager();
        }
    }
    else
    {
            string errorMessage = "Wrong username/password.";
            goToXY(85 - errorMessage.size()/2, 20 + ++row);
            cout << errorMessage;
            cin.ignore();
            cin.get();
            system("cls");
            authManager();
    }
}

void loggedInMenu( string currentUser ){
    string welcomeMessage = "Welcome Back ";
    goToXY(85 - (currentUser.size()/2 + welcomeMessage.size()/2), 3);
    cout << welcomeMessage << currentUser;

    string balanceMessage = "Your balance is: ";
    goToXY(150 - (balanceMessage.size()/2 ),4);
    cout << balanceMessage << DatabaseUsers[currentUser].balance;

    string fastAction = "Select number to do an action: ";
    string logOutAction = "1) Logout";
    string changePassAction = "2) Change password";
    string seeAllProductAction = "3) Go to another page to see other people products ";
    string yourShopAction = "4) Go to your personal shop";
    int row = 15;
    int decision;

    goToXY(85 - logOutAction.size()/2 , row++);
    cout << logOutAction;
    goToXY(85 - changePassAction.size()/2 , row++);
    cout << changePassAction;
    goToXY(85 - seeAllProductAction.size()/2 , row++);
    cout << seeAllProductAction;
    goToXY(85 - yourShopAction.size()/2 , row++);
    cout << yourShopAction;
    goToXY(85 - fastAction.size()/2 , row++);
    cout << fastAction;
    cin >> decision;

    if( decision == 1 )
    {
        system("cls");
        authManager();
    }
    else if (decision == 2 )
        {
            string usernameMessage = "Your username: ";
            string oldPassMessage = "Old password: ";
            string newPassMessage = "New password: ";

            string goodUsername;
            string oldPassword;
            string newPassword;
            goToXY(85 - usernameMessage.size()/2 , 5 + row++);
            cout << usernameMessage, cin >> goodUsername;

            goToXY(85 - oldPassMessage.size()/2 , 5 + row++);
            cout << oldPassMessage, cin >> oldPassword;

            goToXY(85 - newPassMessage.size()/2, 5 + row++);
            cout << newPassMessage, cin >> newPassword;

            if ( goodUsername == currentUser && oldPassword == DatabaseUsers[currentUser].password )
            {
                DatabaseUsers[currentUser].password = newPassword;
                updateDatabaseUsers();
                string succesMessage = "Password changed. Press ENTER to continue... ";
                goToXY(85 - succesMessage.size()/2, 6 + row++);
                cout << succesMessage;
                cin.ignore();
                cin.get();
                system("cls");
                loggedInMenu(currentUser);
            }
        }
        else if ( decision == 3 )
            {
            ///allProducts();

            }
            else if ( decision == 4 )
                {
                    system("cls");
                    yourProducts(currentUser);

                }
                else
                {
                    string errorMessage = "Invalid number. Press Enter to try again...";
                    goToXY(85 - errorMessage.size()/2 , ++row);
                    cout << errorMessage;
                    cin.ignore();
                    cin.get();
                    system("cls");
                    loggedInMenu(currentUser);
                }




}

void authManager(){
    string welcomeMessage = "Welcome to Virtual Market";
    goToXY(85 - welcomeMessage.size()/2 , 20 );
    cout << welcomeMessage;
    int decision;
    string registerMessage = "1) To register an account";
    string loginMessage = "2) Login in your account";
    string fastAction = "Select number to do an action: ";

    int row = 22;

    goToXY(85-registerMessage.size()/2 , row++);
    cout << registerMessage;
    goToXY(85-loginMessage.size()/2 , row++);
    cout << loginMessage;
    goToXY(85-fastAction.size()/2 , row++);
    cout << fastAction;
    cin >> decision;

    if ( decision == 1 )
    {
        system("cls");
        signUp();
    }
    else if ( decision == 2 )
        {
            system("cls");
            logIn();
        }
        else
        {
            string errorMessage = "Invalid Number. Try Again.";
            goToXY(85 - errorMessage.size()/2 , ++row);
            Sleep(1000);
            system("cls");
            authManager();
        }
    logIn();

}

#endif // AUTH_H_INCLUDED
