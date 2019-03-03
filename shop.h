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

void updateDatabaseUsers();
void loggedInMenu(string);
void initDatabaseProduct();
void updateDatabaseProduct();
void yourShop(string);
void viewYourProducts(string);
void viewAllProducts(string);
void addProduct(string);
void removeProduct(string);
void buyProduct(string,int);

void initDatabaseProduct(){
    ifstream f("dbProduct.txt");
    string username;

    infoProduct ProductData;

    while(!f.eof() && f >> username && f >> ProductData.name && f >> ProductData.price && f >> ProductData.amount && f >> ProductData.city )
    {
        DatabaseProduct.insert({username, ProductData});
    }

    string dbMessage = "Database Product Initialized.";
    goToXY( 84 - dbMessage.size()/2, 26);
    cout << dbMessage;
    Sleep(1500);
    system("cls");
}

void updateDatabaseProduct()
{
    ofstream g("dbProduct.txt");

    for ( auto &it : DatabaseProduct )
        g  << it.first << " " << it.second.name << " " << it.second.price << " " << it.second.amount << " " << it.second.city << " " << endl;
}

void yourShop(string currentUser ){

    string welcomeMessage = "Your Shop ";
    goToXY(84 - (currentUser.size()/2 + welcomeMessage.size()/2), 3);
    cout << welcomeMessage << currentUser;

    string balanceMessage = "Your balance is: ";
    goToXY(150 - (balanceMessage.size()/2 ),4);
    cout << balanceMessage << DatabaseUsers[currentUser].balance << "$";

    string fastAction = "Select number to do an action: ";
    string viewAction = "1)View your products";
    string addProductAction = "2) Add a new product for sell list";
    string removeProductAction = "3) Remove a product from your sell list.";
    string undoAction = "4) Go to Menu.";

    int row = 15;
    int decision;
    goToXY(84 - viewAction.size()/2, row++);
    cout << viewAction;
    goToXY(84 - addProductAction.size()/2 , row++);
    cout << addProductAction;
    goToXY(84 - removeProductAction.size()/2 , row++);
    cout << removeProductAction;
    goToXY(84 - undoAction.size()/2, row++);
    cout << undoAction;
    goToXY(84 - fastAction.size()/2 , row++);
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
            addProduct(currentUser);
        }
        else if ( decision == 3)
            {
                system("cls");
                removeProduct(currentUser);
            }
            else if (decision == 4 )
                {
                    system("cls");
                    loggedInMenu(currentUser);
                }
            else
                {
                    string errorMessage = "Invalid number. Press Enter to try again...";
                    goToXY(84 - errorMessage.size()/2 , ++row);
                    cout << errorMessage;
                    cin.ignore();
                    cin.get();
                    system("cls");
                    yourShop(currentUser);
                }

}
void addProduct( string currentUser ){
    int row = 10;
    string productNameMessage = "Product Name: ";
    string productPriceMessage = "Price: ";
    string productAmountMessage = "Amount left: ";
    string productCityMessage = "Where to pick up: ";

    infoProduct newProductData;

    goToXY(84 - productNameMessage.size()/2, ++row);
    cout << productNameMessage;
    cin >> newProductData.name;
    newProductData.name[0] = toupper(newProductData.name[0]);

    goToXY(84 - productPriceMessage.size()/2 , ++row);
    cout << productPriceMessage;
    cin >> newProductData.price;

    goToXY(84 - productAmountMessage.size()/2 , ++row);
    cout << productAmountMessage;
    cin >> newProductData.amount;

    goToXY(84 - productCityMessage.size()/2 , ++row);
    cout << productCityMessage;
    cin >> newProductData.city;
    newProductData.city[0] = toupper(newProductData.city[0]);
    row++;
    if ( newProductData.name.size() < 3 )
    {
        string errorMessage = "Product Name must have at least 3 letters.Press ENTER to try again...";
        goToXY(84 - errorMessage.size()/2, ++row);
        cout << errorMessage;
        cin.ignore();
        cin.get();
        system("cls");
        addProduct(currentUser);
    }
    else
    {
        string succesMessage = "Product added!";
        goToXY(84 - succesMessage.size()/2 , ++row);
        DatabaseProduct.insert({currentUser, newProductData});
        updateDatabaseProduct();
        cout << succesMessage;
        Sleep(1500);
        system("cls");
        yourShop(currentUser);
    }
}

void removeProduct(string currentUser){
    int row = 10;
    string productNameMessageDelete = "Product Name to remove: ";
    goToXY(84 - productNameMessageDelete.size()/2, row++);
    cout << productNameMessageDelete;
    string toDelete;

    cin >> toDelete;
    toDelete[0] = toupper(toDelete[0]);

  for (multimap<string,infoProduct>::iterator it = DatabaseProduct.begin(); it != DatabaseProduct.end(); it++)
  {
    if (it->first == currentUser && it->second.name == toDelete)
        DatabaseProduct.erase(it);
  }

    updateDatabaseProduct();
    system("cls");
    yourShop(currentUser);

}
void viewYourProducts(string currentUser){
    SetWindow(168,700);
    int row = 9;
    string separator = "----------------------------------------------";
    string productNameMessage = "Product Name: ";
    string productPriceMessage = "Price: ";
    string productAmountMessage = "Amount left: ";
    string productCityMessage = "Where to pick up: ";



    for ( auto &it : DatabaseProduct )
    {
        if( it.first == currentUser )
        {
            goToXY(84 - separator.size()/2 , row++);
            cout << separator;
            goToXY(84 - (productNameMessage.size()/2 + it.second.name.size()/2), ++row);
            cout << productNameMessage << it.second.name;
            goToXY(84 - productPriceMessage.size()/2 , ++row);
            cout << productPriceMessage << it.second.price << "$";
            goToXY(84 - productAmountMessage.size()/2 , ++row);
            cout << productAmountMessage << it.second.amount;
            goToXY(84 - (productCityMessage.size()/2 + it.second.city.size()/2), ++row);
            cout << productCityMessage << it.second.city;
            row++;
            goToXY(84 - separator.size()/2 , ++row);
            cout << separator;
        }
           row += 3;
    }
    string previousPageMessage = "Press ENTER for menu...";
    goToXY(84 - previousPageMessage.size()/2 , ++row);
    cout << previousPageMessage;
    cin.ignore();
    cin.get();
    system("cls");
    SetWindow(168,50);
    yourShop(currentUser);
}


void viewAllProducts(string currentUser){
    SetWindow(168,700);
    int row = 9;
    string separator = "----------------------------------------------";
    string productNameMessage = "Product Name: ";
    string productPriceMessage = "Price: ";
    string productAmountMessage = "Amount left: ";
    string productCityMessage = "Where to pick up: ";
    string productSellerMessage = "Seller: ";

    for ( auto &it : DatabaseProduct )
    {
            goToXY(84 - separator.size()/2 , row++);
            cout << separator;
            goToXY(84 - (productNameMessage.size()/2 + it.second.name.size()/2), ++row);
            cout << productNameMessage << it.second.name;
            goToXY(84 - productPriceMessage.size()/2 , ++row);
            cout << productPriceMessage << it.second.price << "$";
            goToXY(84 - productAmountMessage.size()/2 , ++row);
            cout << productAmountMessage << it.second.amount;
            goToXY(84 - (productCityMessage.size()/2 + it.second.city.size()/2), ++row);
            cout << productCityMessage << it.second.city;
            goToXY(84 - (productSellerMessage.size()/2 + it.first.size()/2), ++row);
            cout << productSellerMessage << it.first;
            row++;
            goToXY(84 - separator.size()/2 , ++row);
            cout << separator;
            row += 3;
    }
    string buyMessage ="1)Buy a product";
    string previousPageMessage = "2)Return to Menu";
    string fastAction = "Select number to do an action: ";

    goToXY(84 - buyMessage.size()/2 , ++row);
    cout << buyMessage;

    goToXY(84 - previousPageMessage.size()/2 , ++row);
    cout << previousPageMessage;

    goToXY(84 - fastAction.size()/2 , ++row);
    cout << fastAction;
    row += 2;

    string decision;
    cin >> decision;

    if ( decision == "1" )
    {
        buyProduct(currentUser, row);
    }
    else if ( decision == "2")
        {
        system("cls");
        SetWindow(168,50);
        loggedInMenu(currentUser);
        }
        else
        {
            system("cls");
            viewAllProducts(currentUser);
        }
}

void buyProduct(string currentUser, int row){
    string productNameMessage ="Name of the product to buy: ";
    string productSellerMessage = "Name of the seller: ";
    string productAmountMessage = "Amount to buy: ";

    int amountToBuy;
    string productName, productSeller;
    goToXY(84 - productNameMessage.size()/2 , row++);
    cout << productNameMessage;
    cin >> productName;
    productName[0] = toupper(productName[0]);

    goToXY(84 - productSellerMessage.size()/2 , row++);
    cout << productSellerMessage;
    cin >> productSeller;

    productSeller[0] = toupper(productSeller[0]);

    goToXY(84 - productAmountMessage.size()/2, row++);
    cout << productAmountMessage;
    cin >> amountToBuy;
    bool isCorrectData = false;
        for (multimap<string,infoProduct>::iterator it = DatabaseProduct.begin(); it != DatabaseProduct.end(); it++)
        {

           if (it->first == productSeller && it->second.name == productName && it->second.amount - amountToBuy >= 0)
            {
               if (DatabaseUsers[currentUser].balance - it->second.price*amountToBuy >=0)
                {
                    DatabaseUsers[currentUser].balance -= it->second.price*amountToBuy;
                    DatabaseUsers[productSeller].balance += it->second.price*amountToBuy;

                    if (it->second.amount - amountToBuy > 0)
                        it->second.amount -= amountToBuy;
                    else
                        DatabaseProduct.erase(it);

                    updateDatabaseProduct();
                    updateDatabaseUsers();
                    isCorrectData = true;
                    string succesMessage = "The product was purchased!";
                    string continueMessage = "Press ENTER to try again...";

                    goToXY(84 - succesMessage.size()/2 , row++);
                    cout << succesMessage;
                    goToXY(84 - continueMessage.size()/2, row++);
                    cout << continueMessage;
                    cin.ignore();
                    cin.get();
                    system("cls");
                    viewAllProducts(currentUser);
                    }
                    else
                    {
                    string errorMessage = "Not enough money!";
                    string continueMessage = "Press ENTER to try again...";
                    goToXY(84 - errorMessage.size()/2 , row++);
                    cout << errorMessage;
                    goToXY(84 - continueMessage.size()/2, row++);
                    cout << continueMessage;
                    cin.ignore();
                    cin.get();
                    system("cls");
                    viewAllProducts(currentUser);
                    }
            }
            else
            {
                string errorMessage = "Invalid Name or Insufficient Amount!Press ENTER to try again...";
                goToXY(84- errorMessage.size()/2, row++);
                cout << errorMessage;
                cin.ignore();
                cin.get();
                system("cls");
                viewAllProducts(currentUser);
            }
        }

    if(isCorrectData)
    {
            string errorMessage = "Product doesn't exist";
            string continueMessage = "Press ENTER to try again...";

            goToXY(84 - errorMessage.size()/2 , row++);
            cout << errorMessage;
            goToXY(84 - continueMessage.size()/2, row++);
            cout << continueMessage;
            cin.ignore();
            cin.get();
            system("cls");
            viewAllProducts(currentUser);
    }

}
#endif // SHOP_H_INCLUDED
