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
    goToXY( 84 - dbMessage.size()/2, 25);
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
    goToXY(84 - usernameMessage.size()/2 , 20 + row++);
    cout << usernameMessage;
    cin >> username;

    string passwordMessage = "Your password: ";
    goToXY(84 - passwordMessage.size()/2 , 20 + row ++);
    cout << passwordMessage;
    cin >> newUserData.password;
    bool isGoodPass = false;
    for ( int i = 0 ; i <= newUserData.password.size() ; ++ i )
    {
        if ( isdigit(newUserData.password[i]) && ( newUserData.password[i] == '!' || newUserData.password[i] == '@' || newUserData.password[i] == '#' || newUserData.password[i] == '$' || newUserData.password[i] == '%' || newUserData.password[i] == '^' || newUserData.password[i] == '&' || newUserData.password[i] == '*'))
        isGoodPass = true;
    }
    newUserData.balance = 20;

    if ( DatabaseUsers.count(username) )
    {
        string errorMessage = " already added.Press ENTER to retry.";
        goToXY(84 - (username.size()/2 + errorMessage.size()/2), 20 + ++row);
        cout << "User " << username << errorMessage;
        cin.ignore();
        cin.get();
        system("cls");
        signUp();
    }
    else if (newUserData.password.size() < 8 && !isGoodPass )
        {
            string errorMessage = "Sorry but your password must contain 8 characters and contain one number and one special character.Press ENTER to retry...";
            goToXY(84 - errorMessage.size()/2, 20 + ++row);
            cout << errorMessage;
            cin.ignore();
            cin.get();
            system("cls");
            signUp();
        }
        else
        {
            DatabaseUsers[username] = newUserData;
            string succesMessage = " successfully added.";
            goToXY( 84 - (username.size()/2 + succesMessage.size()/2) , 20 + ++row) ;
            updateDatabaseUsers();
            cout << username << succesMessage;
            Sleep(1000);
            system("cls");
            authManager();
        }

}

void logIn(){
    string tryUsername, tryPassword;

    int row = 0;
    string usernameMessage = "Your username: ";
    goToXY(84 - usernameMessage.size()/2 , 20 + row++);
    cout << usernameMessage;
    cin >> tryUsername;
    string passwordMessage = "Your password: ";
    goToXY(84 - passwordMessage.size()/2 , 20 + row ++);
    cout << passwordMessage;
    cin >> tryPassword;

    if( DatabaseUsers.count(tryUsername) )
    {
        if ( DatabaseUsers[tryUsername].password == tryPassword )
        {
            string succesMessage = " logged in successfully.";
            goToXY(84 - (tryUsername.size()/2 + succesMessage.size()/2), 20 + ++row );
            cout << "User "<< tryUsername << succesMessage ;
            Sleep(500);
            system("cls");
            loggedInMenu(tryUsername);
        }
        else
        {
            string errorMessage = "Wrong username/password.";
            goToXY(84 - errorMessage.size()/2 , 20 + ++row );
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
            goToXY(84 - errorMessage.size()/2, 20 + ++row);
            cout << errorMessage;
            cin.ignore();
            cin.get();
            system("cls");
            authManager();
    }
}

void loggedInMenu( string currentUser ){
    string welcomeMessage = "Welcome Back ";
    goToXY(84 - (currentUser.size()/2 + welcomeMessage.size()/2), 3);
    cout << welcomeMessage << currentUser;

    string balanceMessage = "Your balance is: ";
    goToXY(150 - (balanceMessage.size()/2 ),4);
    cout << balanceMessage << DatabaseUsers[currentUser].balance << "$";

    string fastAction = "Select number to do an action: ";
    string logOutAction = "1) Logout";
    string changePassAction = "2) Change password";
    string seeAllProductAction = "3) All Products";
    string yourShopAction = "4) Go to your personal shop";
    int row = 15;
    string decision;

    goToXY(84 - logOutAction.size()/2 , row++);
    cout << logOutAction;
    goToXY(84 - changePassAction.size()/2 , row++);
    cout << changePassAction;
    goToXY(84 - seeAllProductAction.size()/2 , row++);
    cout << seeAllProductAction;
    goToXY(84 - yourShopAction.size()/2 , row++);
    cout << yourShopAction;
    goToXY(84 - fastAction.size()/2 , row++);
    cout << fastAction;
    cin >> decision;

    if( decision == "1" )
    {
        system("cls");
        authManager();
    }
    else if (decision == "2" )
        {
            string usernameMessage = "Your username: ";
            string oldPassMessage = "Old password: ";
            string newPassMessage = "New password: ";

            string goodUsername;
            string oldPassword;
            string newPassword;
            goToXY(84 - usernameMessage.size()/2 , 5 + row++);
            cout << usernameMessage, cin >> goodUsername;

            goToXY(84 - oldPassMessage.size()/2 , 5 + row++);
            cout << oldPassMessage, cin >> oldPassword;

            goToXY(84 - newPassMessage.size()/2, 5 + row++);
            cout << newPassMessage, cin >> newPassword;

            bool isGoodPass = false;
            for ( int i = 0 ; i <= newPassword.size() ; ++ i )
            {
                if ( newPassword[i] == '!' || newPassword[i] == '@' || newPassword[i] == '#' || newPassword[i] == '$' || newPassword[i] == '%' || newPassword[i] == '^' || newPassword[i] == '&' || newPassword[i] == '*')
                isGoodPass = true;
            }

            if ( newPassword.size() < 8 && !isGoodPass )
            {
                string errorMessage = "Sorry but your password must contain 8 characters.Press ENTER to retry...";
                goToXY(84 - errorMessage.size()/2 , 5 + row++);
                cout << errorMessage;
                cin.ignore();
                cin.get();
                system("cls");
                loggedInMenu(currentUser);
            }
            else if ( goodUsername == currentUser && oldPassword == DatabaseUsers[currentUser].password )
                {
                    DatabaseUsers[currentUser].password = newPassword;
                    updateDatabaseUsers();
                    string succesMessage = "Password changed. Press ENTER to continue... ";
                    goToXY(84 - succesMessage.size()/2, 6 + row++);
                    cout << succesMessage;
                    cin.ignore();
                    cin.get();
                    system("cls");
                    loggedInMenu(currentUser);
                }
        }
        else if ( decision == "3" )
            {
                system("cls");
                viewAllProducts(currentUser);
            }
            else if ( decision == "4" )
                {
                    system("cls");
                    yourShop(currentUser);

                }
                else
                {
                    string errorMessage = "Invalid number. Press Enter to try again...";
                    goToXY(84 - errorMessage.size()/2 , ++row);
                    cout << errorMessage;
                    cin.ignore();
                    cin.get();
                    system("cls");
                    loggedInMenu(currentUser);
                }

}

void authManager(){
    string welcomeMessage = "Welcome to Virtual Market";
    goToXY(84 - welcomeMessage.size()/2 , 20 );
    cout << welcomeMessage;
    string decision;
    string registerMessage = "1) To register an account";
    string loginMessage = "2) Login in your account";
    string fastAction = "Select number to do an action: ";

    int row = 22;

    goToXY(84-registerMessage.size()/2 , row++);
    cout << registerMessage;
    goToXY(84-loginMessage.size()/2 , row++);
    cout << loginMessage;
    goToXY(84-fastAction.size()/2 , row++);
    cout << fastAction;
    cin >> decision;

    if ( decision == "1" )
    {
        system("cls");
        signUp();
    }
    else if ( decision == "2" )
        {
            system("cls");
            logIn();
        }
        else
        {
            string errorMessage = "Invalid Number. Try Again.";
            goToXY(84 - errorMessage.size()/2 , ++row);
            Sleep(1000);
            system("cls");
            authManager();
        }
    logIn();

}

#endif // AUTH_H_INCLUDED
