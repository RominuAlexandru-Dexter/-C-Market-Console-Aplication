#include <iostream>

#include "interface.h"
#include "auth.h"
#include "shop.h"

using namespace std;

int main()
{
    SetWindow(168,50); /// In case there are too many elements of view AllProduct list , just increase height
    initDatabaseUsers();
    initDatabaseProduct();
    authManager();
    return 0;
}
