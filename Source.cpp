#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"

const int maxi_mum = 100;// 100 prisoner ka data satore krnay k liay
const int max_visitors = 5;

string names[maxi_mum];//naam save krnay k liay 100 prisoners ka
int ages[maxi_mum];
string crimes[maxi_mum];
int sentences[maxi_mum];
int prisonerIDs[maxi_mum];
string gender[maxi_mum];
string maritalstatus[maxi_mum];
string visitors[maxi_mum][max_visitors];// har prisoner k visitor ka name store krnay kliay 
int visitorCounts[maxi_mum];
int prisonerCount = 0;

int generateprisonerID() {
    return rand() % 100 + 10;
}

void addprisoner() {
    // store krega prisoner data from index 0
    if (prisonerCount >= maxi_mum) {
        cout << RED << "cannot add more prisoners\n" << RESET;
        return;
    }
    cout << CYAN << "\nenter Prisoner Name: " << RESET;
    cin.ignore();
    getline(cin, names[prisonerCount]);
    prisonerIDs[prisonerCount] = generateprisonerID();
    cout << YELLOW << "generated Prisoner ID: " << prisonerIDs[prisonerCount] << RESET << "\n";
    cout << CYAN << "enter gender (M/F): \n" << RESET;
    cin >> gender[prisonerCount];
    cout << CYAN << "enter marital status (unmarried/married): \n" << RESET;
    cin >> maritalstatus[prisonerCount];
    cout << CYAN << "enter age: " << RESET;
    cin >> ages[prisonerCount];
    cout << CYAN << "enter crime: " << RESET;
    cin.ignore();
    getline(cin, crimes[prisonerCount]);
    cout << CYAN << "enter sentence in years: " << RESET;
    cin >> sentences[prisonerCount];
    cout << CYAN << "visitors in a day (max 5)? " << RESET;
    cin >> visitorCounts[prisonerCount];
    if (visitorCounts[prisonerCount] > max_visitors) {
        visitorCounts[prisonerCount] = max_visitors;
    }
    cin.ignore();
    for (int i = 0; i < visitorCounts[prisonerCount]; i++) {
        cout << CYAN << "enter name of visitor " << (i + 1) << ": " << RESET;
        getline(cin, visitors[prisonerCount][i]);
    }
    cout << GREEN << "prisoner added successfully\\n" << RESET;
    prisonerCount++;
}

void reducesentence() {
    int index;// index prisoner number k liay hai
    float years;
    cout << BLUE << "\n prisoners are \n" << RESET;// availability of prisoner btayega
    for (int i = 0; i < prisonerCount; i++) //prisoners mentin krta as a list taaky chose krskay
    {
        cout << YELLOW << (i + 1) << ": " << names[i] << " ID: " << prisonerIDs[i] << "\n" << RESET;
    }
    cout << CYAN << "\nenter prisoner number to reduce sentence " << RESET;
    cin >> index;
    if (index < 1 || index > prisonerCount) {
        cout << RED << "invalid number\n" << RESET;
        return;
    }
    cout << CYAN << "Enter years to reduce: " << RESET;
    cin >> years;
    if (years >= sentences[index - 1])//ka matlab hai us prisoner ki total saza jo user ne select kiya hai.
    {
        sentences[index - 1] = 0;//agr user sentence say ziada year enter krega to sentence 0 hojayegi
    }
    else {
        sentences[index - 1] -= years;//uski sentence meh say years minus krega
    }
    cout << GREEN << "sentence reduced and new sentence is: " << sentences[index - 1] << " years \n" << RESET;
}

void savetofile() {
    ofstream myfile("prisoners.txt");
    for (int i = 0; i < prisonerCount; i++) {
        myfile << "Prisoner " << (i + 1) << "\n";
        myfile << "ID: " << prisonerIDs[i] << "\n";
        myfile << "Name: " << names[i] << "\n";
        myfile << "Gender: " << gender[i] << "\n";
        myfile << "Marital Status: " << maritalstatus[i] << "\n";
        myfile << "Age: " << ages[i] << "\n";
        myfile << "Crime: " << crimes[i] << "\n";
        myfile << "Sentence: " << sentences[i] << " years\n";
        myfile << "Visitors: ";
        for (int j = 0; j < visitorCounts[i]; j++) //file meh sab visitors k name likhnay ka kaam kr rha hai
        {
            myfile << visitors[i][j] << ",";
        }
        myfile << "\n";
    }
    myfile.close();
    cout << GREEN << "Data saved to prisoners.txt \n" << RESET;
}

void searchbyID() {
    int id;
    cout << CYAN << "Enter prisoner ID to search: " << RESET;
    cin >> id;

    bool found = false;
    for (int i = 0; i < prisonerCount; i++) {
        if (prisonerIDs[i] == id) {
            found = true;
            cout << GREEN << "\nPrisoner found:\n" << RESET;
            cout << "Name: " << names[i] << "\n";
            cout << "Gender: " << gender[i] << "\n";
            cout << "Age: " << ages[i] << "\n";
            cout << "Crime: " << crimes[i] << "\n";
            cout << "Sentence: " << sentences[i] << " years\n";
            cout << "Marital Status: " << maritalstatus[i] << "\n";
            cout << "Visitors: ";
            for (int j = 0; j < visitorCounts[i]; j++) {
                cout << visitors[i][j] << ", ";
            }
            cout << "\n";
            break;
        }
    }
    if (!found) {
        cout << RED << "there is no prisoner with this ID\n" << RESET;
    }
}

void updateprisoner() {
    int id;
    cout << CYAN << "Enter prisoner ID to update: " << RESET;
    cin >> id;
    cin.ignore();

    bool found = false;

    for (int i = 0; i < prisonerCount; i++) {
        if (prisonerIDs[i] == id) {
            found = true;
            cout << YELLOW << "updating details for " << names[i] << " ID: " << id << "\n" << RESET;

            cout << CYAN << "enter new name: \n" << RESET;
            getline(cin, names[i]);

            cout << CYAN << "enter new gender (M/F): \n";
            cin >> gender[i];

            cout << CYAN << "enter new marital status (unmarried/married): \n";
            cin >> maritalstatus[i];

            cout << CYAN << "enter new age: \n";
            cin >> ages[i];

            cout << CYAN << "enter new crime: \n";
            cin.ignore();
            getline(cin, crimes[i]);

            cout << CYAN << "enter new sentence in years: \n";
            cin >> sentences[i];

            cout << GREEN << "prisoner record updated successfully\n" << RESET;
            break;
        }
    }
    if (!found) {
        cout << RED << "No prisoner with this ID found\n" << RESET;
    }
}

void deleteprisoner() {
    int id;
    cout << CYAN << "Enter prisoner ID to delete: " << RESET;
    cin >> id;
    bool found = false;
    for (int i = 0; i < prisonerCount; i++) {
        if (prisonerIDs[i] == id) {
            found = true;
            for (int j = i; j < prisonerCount - 1; j++)//Yeh loop aglay wale prisoner ka data upar wale index par copy karta hai mtlb Agar prisoner 1 ko delete karna hai to 2 ka data 1 par aayega
            {
                names[j] = names[j + 1];// yaha pay prisoner 2 ka data copy kia jarha overwrite basicalyy 1 numbee orisoner pay
                ages[j] = ages[j + 1];
                crimes[j] = crimes[j + 1];
                sentences[j] = sentences[j + 1];
                prisonerIDs[j] = prisonerIDs[j + 1];
                gender[j] = gender[j + 1];
                maritalstatus[j] = maritalstatus[j + 1];
                visitorCounts[j] = visitorCounts[j + 1];
                for (int v = 0; v < max_visitors; v++) {
                    visitors[j][v] = visitors[j + 1][v];
                }
            }
            prisonerCount--;
            cout << GREEN << "Prisoner deleted successfully\n" << RESET;
            break;
        }
    }
    if (!found) {
        cout << RED << "No prisoner with this ID found\n" << RESET;
    }
}

string role; // global becuase humnay isay use kia hai menu meh b
bool login() {
    string username, password;
    cout << CYAN << "Enter username: " << RESET;
    cin >> username;
    cout << CYAN << "Enter password: " << RESET;
    cin >> password;

    if (username == "farrukh" && password == "033") {
        role = "admin";
        cout << GREEN << "admin login successful\n" << RESET;
        return true;
    }
    else if (username == "imran" && password == "071") {
        role = "staff";
        cout << GREEN << "Staff login successful\n" << RESET;
        return true;
    }
    else {
        cout << RED << "please enter correct username/password\n" << RESET;
        return false;
    }
}

void menu() {
    int choice;
    while (true) {
        cout << BLUE << "\n----Prisoner Management System " << role << " ----\n" << RESET;
        cout << YELLOW << "1: Add Prisoner\n";
        cout << "2: Reduce Sentence\n";
        cout << "3: Save to File\n";
        cout << "4: Search Prisoner by ID\n";
        if (role == "admin") {
            cout << "5: Update Prisoner Record\n";
            cout << "6: Delete Prisoner Record\n";
        }
        cout << "7: Exit\n" << RESET;

        cout << CYAN << "Enter your choice: " << RESET;
        cin >> choice;

        if (choice == 1) {
            addprisoner();
        }
        else if (choice == 2) {
            reducesentence();
        }
        else if (choice == 3) {
            savetofile();
        }
        else if (choice == 4) {
            searchbyID();
        }
        else if (choice == 5 && role == "admin") {
            updateprisoner();
        }
        else if (choice == 6 && role == "admin") {
            deleteprisoner();
        }
        else if (choice == 7) {
            cout << GREEN << "exiting program\n" << RESET;
            break;
        }
        else {
            cout << RED << "invalid choice or no permission for this option\n" << RESET;
        }
    }
}


int main() {
    srand(time(0));
    cout << GREEN << " =====================================================\n\n";
    cout << CYAN << "                  PRISON MANAGEMENT SYSTEM         \n\n";
    cout << GREEN << " =====================================================\n";
    if (login()) {
        menu();
    }
    else {
        return 0;
    }
}
