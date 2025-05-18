#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>  // rand(), srand()
#include <time.h>    // time()

using namespace std;

// Console ke liye color codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"

// Constants define kiye hain
const int MAX = 100;
const int MAX_VISITORS = 5;

// Prisoner ka data store karne ke liye arrays
char names[MAX][50];
int ages[MAX];
char crimes[MAX][50];
int sentences[MAX];
int prisonerIDs[MAX];
char gender[MAX][10];
char maritalStatus[MAX][20];
char visitors[MAX][MAX_VISITORS][50];
int visitorCounts[MAX];

int prisonerCount = 0;

// Random 2-digit ID generate karne ka function
int generatePrisonerID() {
    return rand() % 90 + 10;
}

// Naya prisoner add karne ka function
void addPrisoner() {
    if (prisonerCount >= MAX) {
        cout << RED << "Cannot add more prisoners.\n" << RESET;
        return;
    }

    cout << CYAN << "\nEnter Prisoner Name: " << RESET;
    cin >> names[prisonerCount];

    prisonerIDs[prisonerCount] = generatePrisonerID();
    cout << YELLOW << "Generated Prisoner ID: " << prisonerIDs[prisonerCount] << RESET << "\n";

    cout << CYAN << "Enter Gender (Male/Female): " << RESET;
    cin >> gender[prisonerCount];

    cout << CYAN << "Enter Marital Status (unmarried/married): " << RESET;
    cin >> maritalStatus[prisonerCount];

    cout << CYAN << "Enter Age: " << RESET;
    cin >> ages[prisonerCount];

    cout << CYAN << "Enter Crime: " << RESET;
    cin >> crimes[prisonerCount];

    cout << CYAN << "Enter Sentence in years: " << RESET;
    cin >> sentences[prisonerCount];

    cout << CYAN << "How many visitors (max 5)? " << RESET;
    cin >> visitorCounts[prisonerCount];
    if (visitorCounts[prisonerCount] > MAX_VISITORS) {
        visitorCounts[prisonerCount] = MAX_VISITORS;
    }

    for (int i = 0; i < visitorCounts[prisonerCount]; i++) {
        cout << CYAN << "Enter name of visitor " << (i + 1) << ": " << RESET;
        cin >> visitors[prisonerCount][i];
    }

    cout << GREEN << "Prisoner added successfully.\n" << RESET;
    prisonerCount++;
}

// Sentence reduce karne ka function
void reduceSentence() {
    int index;
    double years;

    cout << BLUE << "\nAvailable Prisoners:\n" << RESET;
    for (int i = 0; i < prisonerCount; i++) {
        cout << YELLOW << (i + 1) << ". " << names[i] << " (ID: " << prisonerIDs[i] << ")\n" << RESET;
    }

    cout << CYAN << "\nEnter prisoner number to reduce sentence (1 to " << prisonerCount << "): " << RESET;
    cin >> index;

    if (index < 1 || index > prisonerCount) {
        cout << RED << "Invalid number.\n" << RESET;
        return;
    }

    cout << CYAN << "Enter years to reduce: " << RESET;
    cin >> years;

    if (years >= sentences[index - 1]) {
        sentences[index - 1] = 0;
    }
    else {
        sentences[index - 1] -= years;
    }

    cout << GREEN << "Sentence reduced. New sentence: " << sentences[index - 1] << " years.\n" << RESET;
}

// Data ko file mein save karne ka function
void saveToFile() {
    ofstream file("prisoners.txt");

    for (int i = 0; i < prisonerCount; i++) {
        file << "Prisoner " << (i + 1) << "\n";
        file << "ID: " << prisonerIDs[i] << "\n";
        file << "Name: " << names[i] << "\n";
        file << "Gender: " << gender[i] << "\n";
        file << "Marital Status: " << maritalStatus[i] << "\n";
        file << "Age: " << ages[i] << "\n";
        file << "Crime: " << crimes[i] << "\n";
        file << "Sentence: " << sentences[i] << " years\n";

        file << "Visitors: ";
        for (int j = 0; j < visitorCounts[i]; j++) {
            file << visitors[i][j];
            if (j < visitorCounts[i] - 1) file << ", ";
        }
        file << "\n\n";
    }

    file.close();
    cout << GREEN << "Data saved to 'prisoners.txt'.\n" << RESET;
}

// ID ke zariye prisoner dhoondhne ka function
void searchByID() {
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
            cout << "Marital Status: " << maritalStatus[i] << "\n";
            cout << "Visitors: ";
            for (int j = 0; j < visitorCounts[i]; j++) {
                cout << visitors[i][j];
                if (j < visitorCounts[i] - 1) cout << ", ";
            }
            cout << "\n";
            break;
        }
    }

    if (!found) {
        cout << RED << "No prisoner with this ID found.\n" << RESET;
    }
}

// Naya function jo prisoner record update karta hai
void updatePrisoner() {
    int id;
    cout << CYAN << "Enter prisoner ID to update: " << RESET;
    cin >> id;

    bool found = false;

    for (int i = 0; i < prisonerCount; i++) {
        if (prisonerIDs[i] == id) {
            found = true;
            cout << YELLOW << "Updating details for " << names[i] << " (ID: " << id << ")\n" << RESET;

            cout << CYAN << "Enter new Name: " << RESET;
            cin >> names[i];

            cout << CYAN << "Enter new Gender (Male/Female): " << RESET;
            cin >> gender[i];

            cout << CYAN << "Enter new Marital Status (unmarried/married): " << RESET;
            cin >> maritalStatus[i];

            cout << CYAN << "Enter new Age: " << RESET;
            cin >> ages[i];

            cout << CYAN << "Enter new Crime: " << RESET;
            cin >> crimes[i];

            cout << CYAN << "Enter new Sentence in years: " << RESET;
            cin >> sentences[i];

            cout << CYAN << "Enter number of visitors (max 5): " << RESET;
            cin >> visitorCounts[i];
            if (visitorCounts[i] > MAX_VISITORS) visitorCounts[i] = MAX_VISITORS;

            for (int j = 0; j < visitorCounts[i]; j++) {
                cout << CYAN << "Enter visitor " << (j + 1) << " name: " << RESET;
                cin >> visitors[i][j];
            }

            cout << GREEN << "Prisoner record updated successfully.\n" << RESET;
            break;
        }
    }

    if (!found) {
        cout << RED << "No prisoner with this ID found.\n" << RESET;
    }
}

// Naya function jo prisoner record delete karta hai
void deletePrisoner() {
    int id;
    cout << CYAN << "Enter prisoner ID to delete: " << RESET;
    cin >> id;

    bool found = false;

    for (int i = 0; i < prisonerCount; i++) {
        if (prisonerIDs[i] == id) {
            found = true;

            for (int j = i; j < prisonerCount - 1; j++) {
                for (int k = 0; k < 50; k++) names[j][k] = names[j + 1][k];
                ages[j] = ages[j + 1];
                for (int k = 0; k < 50; k++) crimes[j][k] = crimes[j + 1][k];
                sentences[j] = sentences[j + 1];
                prisonerIDs[j] = prisonerIDs[j + 1];
                for (int k = 0; k < 10; k++) gender[j][k] = gender[j + 1][k];
                for (int k = 0; k < 20; k++) maritalStatus[j][k] = maritalStatus[j + 1][k];
                visitorCounts[j] = visitorCounts[j + 1];

                for (int v = 0; v < MAX_VISITORS; v++) {
                    for (int k = 0; k < 50; k++) {
                        visitors[j][v][k] = visitors[j + 1][v][k];
                    }
                }
            }

            prisonerCount--;
            cout << GREEN << "Prisoner deleted successfully.\n" << RESET;
            break;
        }
    }

    if (!found) {
        cout << RED << "No prisoner with this ID found.\n" << RESET;
    }
}

// Menu jo options show karta hai
void menu() {
    int choice;

    while (true) {
        cout << BLUE << "\n--- Prisoner Management Menu ---\n" << RESET;
        cout << YELLOW << "1. Add Prisoner\n";
        cout << "2. Reduce Sentence\n";
        cout << "3. Save to File\n";
        cout << "4. Search Prisoner by ID\n";
        cout << "5. Update Prisoner Record\n";
        cout << "6. Delete Prisoner Record\n";
        cout << "7. Exit\n" << RESET;

        cout << CYAN << "Enter your choice: " << RESET;
        cin >> choice;

        if (choice == 1) {
            addPrisoner();
        }
        else if (choice == 2) {
            reduceSentence();
        }
        else if (choice == 3) {
            saveToFile();
        }
        else if (choice == 4) {
            searchByID();
        }
        else if (choice == 5) {
            updatePrisoner();
        }
        else if (choice == 6) {
            deletePrisoner();
        }
        else if (choice == 7) {
            cout << GREEN << "Exiting program.\n" << RESET;
            break;
        }
        else {
            cout << RED << "Invalid choice. Try again.\n" << RESET;
        }
    }
}

// Program ka entry point
int main() {
    srand(time(0));
    cout << GREEN << "-------PRISON MANAGEMENT SYSTEM---------------\n\n\n";
    string username, password;
    cout << CYAN << "Enter username: " << RESET;
    cin >> username;
    cout << CYAN << "Enter password: " << RESET;
    cin >> password;

    if ((username == "farrukh" && password == "033") || (username=="imran" && password == "123")) {
        cout << GREEN << "Login successful.\n" << RESET;
        menu();
    }
    else {
        cout << RED << "Invalid login credentials.\n" << RESET;
    }

    return 0;
}