#include <iostream>
#include <vector>
#include <map>
#include <iomanip>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAX_CITIES = 100;

vector<string> cities;
int roadMatrix[MAX_CITIES][MAX_CITIES] = {0};
float budgetMatrix[MAX_CITIES][MAX_CITIES] = {0.0};

int getCityIndex(const string& name) {
    for (int i = 0; i < cities.size(); i++) {
        if (cities[i] == name) return i;
    }
    return -1;
}

void addCities() {
    int n;
    cout << "Enter the number of cities to add: ";
    cin >> n;
    cin.ignore();
    for (int i = 0; i < n; i++) {
        string name;
        cout << "Enter name for city " << (cities.size() + 1) << ": ";
        getline(cin, name);
        if (getCityIndex(name) == -1) {
            cities.push_back(name);
        } else {
            cout << "City already exists. Skipping.\n";
        }
    }
}

void addRoad() {
    string c1, c2;
    cout << "Enter the name of the first city: ";
    cin >> ws; getline(cin, c1);
    cout << "Enter the name of the second city: ";
    getline(cin, c2);
    int i = getCityIndex(c1);
    int j = getCityIndex(c2);
    if (i != -1 && j != -1 && i != j) {
        roadMatrix[i][j] = roadMatrix[j][i] = 1;
        cout << "Road added between " << c1 << " and " << c2 << ".\n";
    } else {
        cout << "One or both cities are invalid.\n";
    }
}

void addBudget() {
    string c1, c2;
    float budget;
    cout << "Enter the name of the first city: ";
    cin >> ws; getline(cin, c1);
    cout << "Enter the name of the second city: ";
    getline(cin, c2);
    int i = getCityIndex(c1);
    int j = getCityIndex(c2);
    if (i != -1 && j != -1 && roadMatrix[i][j] == 1) {
        cout << "Enter the budget for the road: ";
        cin >> budget;
        budgetMatrix[i][j] = budgetMatrix[j][i] = budget;
        cout << "Budget added for the road between " << c1 << " and " << c2 << ".\n";
    } else {
        cout << "Road does not exist between the given cities.\n";
    }
}

void editCity() {
    int idx;
    cout << "Enter the index of the city to edit: ";
    cin >> idx;
    if (idx >= 1 && idx <= cities.size()) {
        string newName;
        cout << "Enter new name for city: ";
        cin >> ws; getline(cin, newName);
        cities[idx - 1] = newName;
        cout << "City updated successfully.\n";
    } else {
        cout << "Invalid index.\n";
    }
}

void searchCity() {
    int idx;
    cout << "Enter the index of the city: ";
    cin >> idx;
    if (idx >= 1 && idx <= cities.size()) {
        cout << "City " << idx << ": " << cities[idx - 1] << endl;
    } else {
        cout << "City not found.\n";
    }
}

void displayCities() {
    for (int i = 0; i < cities.size(); i++) {
        cout << (i + 1) << ": " << cities[i] << endl;
    }
}

void displayRoads() {
    cout << "Cities:\n";
    for (int i = 0; i < cities.size(); i++) {
        cout << (i + 1) << ": " << cities[i] << endl;
    }

    cout << "Roads Adjacency Matrix:\n";
    for (int i = 0; i < cities.size(); i++) {
        for (int j = 0; j < cities.size(); j++) {
            cout << roadMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

void displayAllData() {
    cout << "Cities:\n";
    displayCities();

    cout << "\nRoad adjacency matrix:\n";
    for (int i = 0; i < cities.size(); i++) {
        for (int j = 0; j < cities.size(); j++) {
            cout << roadMatrix[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nBudget adjacency matrix:\n";
    for (int i = 0; i < cities.size(); i++) {
        for (int j = 0; j < cities.size(); j++) {
            cout << fixed << setprecision(2) << budgetMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

void saveToFile() {
    ofstream citiesFile("cities.txt");
    citiesFile << "Index  City_Name\n";
    for (int i = 0; i < cities.size(); i++) {
        citiesFile << (i + 1) << "   " << cities[i] << "\n";
    }
    citiesFile.close();

    ofstream roadsFile("roads.txt");
    roadsFile << "Nbr Road            Budget\n";
    int count = 1;
    for (int i = 0; i < cities.size(); i++) {
        for (int j = i + 1; j < cities.size(); j++) {
            if (roadMatrix[i][j]) {
                roadsFile << count << ".  "
                          << cities[i] << "-" << cities[j]
                          << string(20 - (cities[i].length() + cities[j].length()), ' ')
                          << fixed << setprecision(2) << budgetMatrix[i][j] << "\n";
                count++;
            }
        }
    }
    roadsFile.close();
}


int main() {
    int choice;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add new city(ies)\n";
        cout << "2. Add roads between cities\n";
        cout << "3. Add the budget for roads\n";
        cout << "4. Edit city\n";
        cout << "5. Search for a city using its index\n";
        cout << "6. Display cities\n";
        cout << "7. Display roads\n";
        cout << "8. Display recorded data on console\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addCities(); break;
            case 2: addRoad(); break;
            case 3: addBudget(); break;
            case 4: editCity(); break;
            case 5: searchCity(); break;
            case 6: displayCities(); break;
            case 7: displayRoads(); break;
            case 8: displayAllData(); break;
            case 9: saveToFile(); cout << "Exiting program...\n"; return 0;
            default: cout << "Invalid choice!\n";
        }
    }

    return 0;
}
