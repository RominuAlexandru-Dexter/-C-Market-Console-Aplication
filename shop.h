#ifndef SHOP_H_INCLUDED
#define SHOP_H_INCLUDED

#include <iostream>
#include <fstream>
#include <map>
#include <string>

#include "interface.h"
#include "auth.h"
#include "database.h"

using namespace std;




void initDatabaseProduct();
void updateDatabaseProduct();
void yourProducts(string);
void viewYourProducts(string);

void initDatabaseProduct(){
    ifstream f("dbProduct.txt");
    string username;

    infoProduct ProductData;

    while(!f.eof() && f >> username && f >> ProductData.name && f >> ProductData.price && f >> ProductData.amount && f >> ProductData.city && f >> ProductData.expirationDate)
    {
        DatabaseProduct.insert({username, ProductData});
    }

    string dbMessage = "Database Product Initialized.";
    goToXY( 85 - dbMessage.size()/2, 26);
    cout << dbMessage;
    Sleep(1500);
    system("cls");
}

void updateDatabaseProduct()
{
    ofstream g("dbProduct.txt");

    for ( auto &it : DatabaseProduct )
        g << it.first << " " << it.second.price << " " << it.second.amount << " " << it.second.city << " " << it.second.expirationDate << endl;
}

void yourProducts(string currentUser ){

    string welcomeMessage = "Your Shop ";
    goToXY(85 - (currentUser.size()/2 + welcomeMessage.size()/2), 3);
    cout << welcomeMessage << currentUser;

    string balanceMessage = "Your balance is: ";
    goToXY(150 - (balanceMessage.size()/2 ),4);
    cout << balanceMessage << DatabaseUsers[currentUser].balance << "$";

    string fastAction = "Select number to do an action: ";
    string viewAction = "1)View your products";
    string addProductAction = "2) Add a new product for sell list";
    string removeProductAction = "3) Remove a product from your sell list.";

    int row = 15;
    int decision;
    goToXY(85 - viewAction.size()/2, row++);
    cout << viewAction;
    goToXY(85 - addProductAction.size()/2 , row++);
    cout << addProductAction;
    goToXY(85 - removeProductAction.size()/2 , row++);
    cout << removeProductAction;
    goToXY(85 - fastAction.size()/2 , row++);
    cout << fastAction;
    cin >> decision;

    if ( decision == 1 )
    {
        system("cls");
        viewYourProducts(currentUser);
    }
    else if ( decision == 2 )
        {
            system("cls");

            /// To make a form for adding products
        }
        else if ( decision == 3)
            {
                system("cls");

                /// To make a form for removing products
            }
            else
            {
                string errorMessage = "Invalid number. Press Enter to try again...";
                goToXY(85 - errorMessage.size()/2 , ++row);
                cout << errorMessage;
                cin.ignore();
                cin.get();
                system("cls");
                yourProducts(currentUser);
            }

}

void viewYourProducts(string currentUser){
    int row = 10;
    string separator = "----------------------------------------------";
    string productNameMessage = "Denumirea produsului: ";
    string productPriceMessage = "Pretul produsului: ";
    string productAmountMessage = "Cantitatea ramasa: ";
    string productCityMessage = "Orasul de unde se poate ridica produsul: ";
    string productExpireMessage = "Ofera valabila pana: ";

    for ( auto &it : DatabaseProduct )
    {
        if( it.first == currentUser )
        {
            goToXY(85 - separator.size()/2 , row++);
            cout << separator;
            goToXY(85 - (productNameMessage.size()/2 + it.second.name.size()/2), ++row);
            cout << productNameMessage << it.second.name;
            goToXY(84 - productPriceMessage.size()/2 , ++row);
            cout << productPriceMessage << it.second.price << "$";
            goToXY(85 - productAmountMessage.size()/2 , ++row);
            cout << productAmountMessage << it.second.amount;
            goToXY(85 - (productCityMessage.size()/2 + it.second.city.size()/2), ++row);
            cout << productCityMessage << it.second.city;
            goToXY(85 - (productExpireMessage.size()/2 + it.second.expirationDate.size()/2), ++row);
            cout << productExpireMessage<< it.second.expirationDate;
            row++;
            goToXY(85 - separator.size()/2 , ++row);
            cout << separator;
        }
           row += 3;
    }

        cin.ignore();
        cin.get();
        system("cls");
        yourProducts(currentUser);
}
#endif // SHOP_H_INCLUDED
