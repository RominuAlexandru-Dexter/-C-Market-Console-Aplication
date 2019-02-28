#include <iostream>

#include "interface.h"
#include "auth.h"
#include "shop.h"

using namespace std;

int main()
{
    SetWindow(170,50);
    initDatabaseUsers();
    initDatabaseProduct();
    authManager();
    return 0;
}
