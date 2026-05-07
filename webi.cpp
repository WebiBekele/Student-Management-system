#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_STUDENTS = 100;
const string DATA_FILE = "students.txt";

struct Student {
    int id;
    string name;
    double gpa;
};

Student students[MAX_STUDENTS];
int totalStudents = 0;

void loadFromFile();
void saveToFile();
void addStudent();
void viewAllStudents();
void searchStudent();
void updateStudent();
void displayStudent(const Student& s);
int findIndexById(int id);
void printMenu();

int main() {
    loadFromFile();

    int choice;

    do {
        printMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewAllStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5:
                saveToFile();
                cout << "\nData saved. Goodbye!\n";
                break;
            default:
                cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 5);

    return 0;
}

void printMenu() {
    cout << "\n========================================\n";
    cout << "   Student Record Management System\n";
    cout << "========================================\n";
    cout << " 1. Add Student\n";
    cout << " 2. View All Students\n";
    cout << " 3. Search Student by ID\n";
    cout << " 4. Update Student Record\n";
    cout << " 5. Save & Exit\n";
    cout << "----------------------------------------\n";
}

void displayStudent(const Student& s) {
    cout << "  ID   : " << s.id << "\n";
    cout << "  Name : " << s.name << "\n";
    cout << "  GPA  : " << s.gpa << "\n";
    cout << "  ------\n";
}

int findIndexById(int id) {
    for (int i = 0; i < totalStudents; i++) {
        if (students[i].id == id) return i;
    }
    return -1;
}

void addStudent() {
    if (totalStudents >= MAX_STUDENTS) {
        cout << "\nStorage full! Cannot add more students.\n";
        return;
    }

    Student s;

    cout << "\n--- Add New Student ---\n";
    cout << "Enter Student ID  : ";
    cin >> s.id;
    cin.ignore();

    if (findIndexById(s.id) != -1) {
        cout << "A student with ID " << s.id << " already exists.\n";
        return;
    }

    cout << "Enter Student Name: ";
    getline(cin, s.name);

    cout << "Enter GPA (0.0 - 4.0): ";
    cin >> s.gpa;
    cin.ignore();

    students[totalStudents] = s;
    totalStudents++;

    cout << "\nStudent added successfully!\n";
}

void viewAllStudents() {
    cout << "\n--- All Student Records ---\n";

    if (totalStudents == 0) {
        cout << "No records found.\n";
        return;
    }

    for (int i = 0; i < totalStudents; i++) {
        displayStudent(students[i]);
    }
    cout << "Total students: " << totalStudents << "\n";
}

void searchStudent() {
    cout << "\n--- Search Student ---\n";
    cout << "Enter Student ID to search: ";

    int id;
    cin >> id;
    cin.ignore();

    int index = findIndexById(id);

    if (index == -1) {
        cout << "Student with ID " << id << " not found.\n";
    } else {
        cout << "\nRecord found:\n";
        displayStudent(students[index]);
    }
}

void updateStudent() {
    cout << "\n--- Update Student Record ---\n";
    cout << "Enter Student ID to update: ";

    int id;
    cin >> id;
    cin.ignore();

    int index = findIndexById(id);

    if (index == -1) {
        cout << "Student with ID " << id << " not found.\n";
        return;
    }

    cout << "\nCurrent record:\n";
    displayStudent(students[index]);

    cout << "Enter new Name (press Enter to keep \"" << students[index].name << "\"): ";
    string newName;
    getline(cin, newName);
    if (!newName.empty()) {
        students[index].name = newName;
    }

    cout << "Enter new GPA (enter -1 to keep " << students[index].gpa << "): ";
    double newGpa;
    cin >> newGpa;
    cin.ignore();
    if (newGpa >= 0.0) {
        students[index].gpa = newGpa;
    }

    cout << "\nRecord updated successfully!\n";
}

void saveToFile() {
    ofstream outFile(DATA_FILE);

    if (!outFile) {
        cout << "Error: Could not open file for writing.\n";
        return;
    }

    outFile << "========================================\n";
    outFile << "   Student Record Management System\n";
    outFile << "   Total Records: " << totalStudents << "\n";
    outFile << "========================================\n\n";

    for (int i = 0; i < totalStudents; i++) {
        outFile << "Record #" << (i + 1) << "\n";
        outFile << "  ID   : " << students[i].id << "\n";
        outFile << "  Name : " << students[i].name << "\n";
        outFile << "  GPA  : " << students[i].gpa << "\n";
        outFile << "----------------------------------------\n";
    }

    outFile.close();
    cout << "\n" << totalStudents << " record(s) saved to \"" << DATA_FILE << "\".\n";
}

void loadFromFile() {
    ifstream inFile(DATA_FILE);

    if (!inFile) {
        return;
    }

    string line;
    while (getline(inFile, line) && totalStudents < MAX_STUDENTS) {
        if (line.substr(0, 8) == "  ID   :") {
            Student s;
            s.id = stoi(line.substr(9));

            string nameLine, gpaLine;
            getline(inFile, nameLine);
            getline(inFile, gpaLine);

            s.name = nameLine.substr(9);
            s.gpa  = stod(gpaLine.substr(9));

            students[totalStudents] = s;
            totalStudents++;
        }
    }

    inFile.close();

    if (totalStudents > 0) {
        cout << totalStudents << " record(s) loaded from \"" << DATA_FILE << "\".\n";
    }
} 