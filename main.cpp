#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

ifstream f("dbUsers.txt");


map < string , string > DatabaseUsers;
/// De adaugat portofel electronic si editat peste tot.
struct user {
    string username;
    string password;
};

void initDatabaseUsers();
void signUp();
void logIn();
void loggedInMenu(string);
void menuManger();
void updateDatabaseUsers();
void separator();

/// Incarc Map-ul meu cu datele din baza de date.
void initDatabaseUsers(){
    user dbUser;
    while(!f.eof() && f >> dbUser.username && f >> dbUser.password )
    {
        DatabaseUsers[dbUser.username] = dbUser.password;
    }
    cout << "Database Initialized. Press ENTER to continue...";
    cin.get();
    system("cls");
}

/// Pagina la care esti redirectionat cand alegi din Meniul Principal sa te inregistrezi
void signUp(){
    user newUser;
    cout << "Introduceti Username: ";
    cin >> newUser.username;
    cout << "Introduceti Parola: ";
    cin >> newUser.password;

    if ( DatabaseUsers.count(newUser.username) )
    {
        cout << "User " << newUser.username << " already added. Press ENTER to SignUp again."<<endl;
        cin.ignore();
        cin.get();
        system("cls");
        signUp();
    }
    else
    {
        DatabaseUsers[newUser.username] = newUser.password;
        cout << "User " << newUser.username << " successfully added" << endl;
        updateDatabaseUsers();
        cout << "Database Updated Succesfull";

        cout << "Press ENTER for Menu.";
        cin.ignore();
        cin.get();
        system("cls");
        menuManger();
    }
}

/// Pagina la care esti redirectionat cand alegi din Meniul Principal sa te loghezi
void logIn(){
    user logInUser;
    cout << "Introduceti username: ";
    cin >> logInUser.username;
    cout << "Introduceti parola: ";
    cin >> logInUser.password;

    if ( DatabaseUsers.count(logInUser.username) )
    {
        if(DatabaseUsers[logInUser.username] == logInUser.password)
        {
            cout << "User "<< logInUser.username << " logged in successfully. Press ENTER to continue...";
            cin.ignore();
            cin.get();
            system("cls");
            loggedInMenu(logInUser.username);
        }
        else
        {
            cout << "Username/Password incorrect. Press ENTER to try again.";
            cin.ignore();
            cin.get();
            system("cls");
            menuManger();
        }
    }
    else
        {
            cout << "Username/Password incorrect. Press ENTER to try again.";
            cin.ignore();
            cin.get();
            system("cls");
            menuManger();
        }
}

/// Pagina la care esti redirectionat cand te loghezi
void loggedInMenu( string usernameLogged ){
    string decision;
    cout << "Welcome Back " << usernameLogged << endl;
    cout << endl;
    cout << "Pentru a schimba parola tasteaza : 'change'."<< endl;
    cout << "Pentru a da logOut tasteaza : 'leave' " << endl;
    separator();

    /**De continuat cu o pagina de produse pe care le vinde persoana respectiva
       Posibilitatea de a adauga noi produse spre vanzare/sterge/edita
       Posibilitatea de a vedea toate produsele de pe piata si sortarea lor
       Posibilitatea de a cumpara produsele altora.
    **/
    cin >> decision;

    if ( decision == "change" )
    {
        string userToChange, oldPassword, newPassword;
        cout << "Introduceti username: ";
        cin >> userToChange;
        cout << "Introduceti vechea parola: ";
        cin >> oldPassword;
        cout << "Introduceti noua parola: ";
        cin >> newPassword;

        if ( userToChange == usernameLogged && DatabaseUsers[usernameLogged] == oldPassword )
        {
            DatabaseUsers[usernameLogged] = newPassword;
            updateDatabaseUsers();
            cout << "Parola a fost schimbata cu succes. Noua parola este: " << DatabaseUsers[usernameLogged];
        }
        else
        {
            cout << "Wrong Username/Password. Press ENTER to continue...";
            cin.ignore();
            cin.get();
            system("cls");
            loggedInMenu(usernameLogged);
        }

    }
    else if ( decision == "leave" )
    {
        system("cls");
        menuManger();
    }
}

/// Updatez baza de date a utilizatorilor atunci cand cineva se inregistreaza
void updateDatabaseUsers(){
    ofstream g("dbUsers.txt");
    for ( auto &i: DatabaseUsers )
        g << i.first << " " << i.second << endl;
}

/// Meniul de alegere a ce doresti sa faci: Register/Login
void menuManger(){
    cout << "Daca doresti sa-ti faci un cont tasteaza: 'register'. " << endl << endl;
    cout << "Daca doresti sa intrii intr-un cont existent tasteaza: 'login'. " << endl << endl;
    separator();
    string decision;
    cin >> decision;

    if( decision == "register" )
    {
        system("cls");
        signUp();
    }
    else if ( decision == "login" )
        {
            system("cls");
            logIn();
        }

}

/// Un separator dragut;
void separator(){
    cout << endl;
    for ( int i = 0 ; i < 80 ; ++i )
        cout << "-";
    for ( int i = 0 ; i < 80 ; ++i )
        cout << "-";
    cout << endl;
}
int main()
{
    initDatabaseUsers();
    menuManger();
    return 0;
}
