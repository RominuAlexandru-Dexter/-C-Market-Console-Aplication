#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED

#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

struct infoProduct{
    string name;
    float price;
    int amount;
    string city;
};
multimap < string , infoProduct > DatabaseProduct;

struct userInfo {
    string password;
    float balance;


    void buyGetBalance( float &balance , float pretProdus, unsigned int &cantitate ){
        if ( balance - pretProdus >= 0 )
        {
            balance -= pretProdus;
            --cantitate;
        }
        else
        {
            cout << " Nu ai destui bani ";
        }
    }

};

map < string , userInfo > DatabaseUsers;




#endif // DATABASE_H_INCLUDED
